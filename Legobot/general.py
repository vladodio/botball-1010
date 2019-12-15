#!/usr/bin/python2

# general purpose functions for Explorer Post 1010's botball team
# legobot variant

# imports
from wallaby import *

# constants
left_motor = 0
right_motor = 1
pulley = 2

toph_left = 0
toph_right = 1
toph_front = 2

claw = 0
opened = 100
closed = 2000

degrees_to_ticks = 6100
gyroscope_bias = .217625

# general function for moving
current_left_power = 0
current_right_power = 0 
current_theta = 0

def move(Lpower, Rpower):
    global current_right_power, current_left_power
    current_left_power = Lpower
    current_right_power = Rpower
    mav(left_motor, Lpower)
    mav(right_motor, Rpower)
    msleep(1)

def turn(targetDegrees, Lpower, Rpower, tickLength=10):
    global current_theta
    targetTheta = targetDegrees * degrees_to_ticks
    move(Lpower,Rpower)
    while(current_theta < targetTheta):
        msleep(tickLength)
        current_theta += abs(getGyroReading() - gyroscope_bias) * tickLength
    stop()
    current_theta = 0

def stop(sleepTime=0):
    move(0,0)
    try:
        msleep(sleepTime)
    except:
        pass

def pause(sleepTime):
    Lpower=current_left_power
    Rpower=current_right_power
    move(0,0)
    msleep(sleepTime)
    move(Lpower,Rpower)


def go_to_black(Lpower=1000, Rpower=1000):
    while(analog(toph_left) < 2000 or analog(toph_right) < 2000):
        move(Lpower, Rpower)
    stop()

def go_to_white(Lpower=1000, Rpower=1000):
    while(analog(toph_left) > 2000 or analog(toph_right) > 2000):
        move(Lpower, Rpower)
    stop()

# code specific to the scrim
def lower_pulley():
    set_servo_position(claw, open)
    msleep(500)
    mav(pulley, -1500)
    msleep(2300)
    mav(pulley, 0)
    
def raise_pulley():
    set_servo_position(claw, closed)
    msleep(500)
    mav(pulley, 1500)
    msleep(2400)
    mav(pulley, 0)

def wait():
    msleep(5000)

# planned functions
def turn_right_wheel(deg):
    pass
def turn_left_wheel(deg):
    pass
def pid_line_follow_for(baseLeftPower, baseRightPower, time):
    pass