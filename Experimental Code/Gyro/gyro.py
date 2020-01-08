#!/usr/bin/python

# this file is more or less the C code converted point for point to python
# not much else to it

import os, sys
from wallaby import *

# for testing purposes
bias = -0.9162
turnConstant = 5500

def sec():
    return time()*1000 # this returns current time in miliseconds
def sleep(T):
    msleep(T) # sleeps for T miliseconds
def drive(Lpower, Rpower):
    current_right_power = Rpower
    current_left_power =  Lpower
    create_drive_direct(Lpower, Rpower)

def main():
    create_connect()
    #calibrate_gyro(3000)
    #drive_with_gyro(300, 7000)
    for i in range(4):
        turn_with_gyro(200,-200,90*turnConstant)

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

def turn_with_gyro(left_wheel_speed, right_wheel_speed, targetTheta):

    theta = 0
    acc(left_wheel_speed , right_wheel_speed)

    while(theta < targetTheta):
        sleep(10)
        theta += abs(gyro_z() - bias) * 10
    drive(0, 0)



if __name__== "__main__":
    sys.stdout = os.fdopen(sys.stdout.fileno(),"w",0)
    main();

