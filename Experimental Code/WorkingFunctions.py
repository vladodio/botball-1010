#!/usr/bin/python2.7
import os, sys
from wallaby import *
from time import time


current_left_power = 0
current_right_power = 0
max_left_power = 500
max_right_power = 500
current_theta = 0

bias = -0.9162
turnConstant = 4550

# nicknames for functions
def sec():
    return time()*1000 # this returns current time in miliseconds
def sleep(T):
    msleep(T) # sleeps for T miliseconds


def drive(Lpower, Rpower):
    global current_right_power, current_left_power
    current_right_power = Rpower
    current_left_power =  Lpower
    create_drive_direct(Lpower, Rpower)

def accelTo(Lpower, Rpower, numberOfSteps, deltaTime):
    global current_right_power, current_left_power

    delta_accel_left = (Lpower - current_left_power)/numberOfSteps
    delta_accel_right = (Rpower - current_right_power)/numberOfSteps

    counter = numberOfSteps

    while(counter > 0):
        current_left_power += delta_accel_left
        current_right_power += delta_accel_right
        drive(int(current_left_power),int(current_right_power))
        sleep(deltaTime)
        counter -= 1
    current_left_power = Lpower
    current_right_power = Rpower
    drive(Lpower,Rpower)

def move(Lpower, Rpower, time, decelerationOn=True, numberOfSteps= 5, deltaTime = 50):
    global current_right_power, current_left_power
    if(Lpower>max_left_power):
        Lpower = max_left_power
    if(Rpower>max_right_power):
        Rpower = max_right_power

    startTime = sec()
    endTime = startTime+time
    accelTo(Lpower, Rpower, numberOfSteps, deltaTime)
    if(decelerationOn):
        endTime -= (numberOfSteps*deltaTime)
        while(sec() < endTime):
            sleep(1) # maybe this value needs to be bigger
        accelTo(0,0,numberOfSteps,deltaTime)

def calibrate_gyro(cycles):
    i = 0
    avg = 0
    while(i < cycles):
        avg += gyro_z()
        msleep(2)
        i += 1
    bias = avg / float(cycles)
    print(bias)





# Time given in seconds
# speed given in 
def drive_with_gyro(speed, time):

    startTime = seconds()
    theta = 0
    while(seconds() - startTime < (time / 1000.0)):
        if(speed > 0):
            drive(int(speed + speed * (1.920137e-15 + 0.000004470956*theta - 7.399285e-28*(theta**2) - 2.054177e-18*(theta** 3) + 1.3145e-40*(theta** 4))) , int(speed - speed * (1.920137e-16 + 0.000004470956*theta - 7.399285e-28*(theta** 2) - 2.054177e-18*(theta** 3) + 1.3145e-40*(theta** 4))))
        else:
            drive(int(speed - speed * (1.920137e-15 + 0.000004470956*theta - 7.399285e-28*(theta**2) - 2.054177e-18**(theta** 3) + 1.3145e-40*(theta** 4))), int(speed + speed * (1.920137e-16 + 0.000004470956*theta - 7.399285e-28*(theta** 2) - 2.054177e-18*(theta** 3) + 1.3145e-40*(theta** 4))))
        msleep(10)
        theta += (gyro_z() - bias) * 10

def accelToGyro(Lpower, Rpower, numberOfSteps, deltaTime):
    global current_right_power, current_left_power, current_theta

    delta_accel_left = (Lpower - current_left_power)/numberOfSteps
    delta_accel_right = (Rpower - current_right_power)/numberOfSteps

    counter = numberOfSteps
    theta = 0

    while(counter > 0):
        current_left_power += delta_accel_left
        current_right_power += delta_accel_right
        drive(int(current_left_power),int(current_right_power))
        theta += abs(gyro_z() - bias) * deltaTime
        sleep(deltaTime)
        counter -= 1
    current_left_power = Lpower
    current_right_power = Rpower
    drive(Lpower,Rpower)


def turn_with_gyro(Lpower, Rpower, targetTheta, numberOfSteps=40, deltaTime=10):
    global current_theta
    current_theta = 0
    accelToGyro(Lpower,Rpower,numberOfSteps,deltaTime)
    while(current_theta < ((targetTheta*2)/3)):
        sleep(5)
        current_theta += abs(gyro_z() - bias) * 5
    if(Lpower > 0 and Rpower < 0):
        accelToGyro(30,-30,numberOfSteps,deltaTime)
    else:
        accelToGyro(-30,30,numberOfSteps,deltaTime)
    while(current_theta < targetTheta):
        sleep(5)
        current_theta += abs(gyro_z() - bias) * 5
    drive(0,0)
    sleep(100)



def main():
    create_connect()
    #calibrate_gyro(3000)
    #drive_with_gyro(300, 7000)
    cycles = 4
    for i in range(cycles):
        turn_with_gyro(200,-200,(360/cycles)*turnConstant)

if __name__== "__main__":
    sys.stdout = os.fdopen(sys.stdout.fileno(),"w",0)
    main();

