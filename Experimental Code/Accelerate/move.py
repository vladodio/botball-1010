#!/usr/bin/python2.7
import os, sys
from wallaby import *
from time import time

current_left_power = 0
current_right_power = 0
max_left_power = 500
max_right_power = 500
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


def accelToExponential(Lpower, Rpower, numberOfSteps, deltaTime):
    global current_right_power, current_left_power

    delta_left = (Lpower - current_left_power)
    delta_right = (Rpower - current_right_power)

    base = 15
    delta_exponent = 1/numberOfSteps
    left_exponent_term = (base** delta_exponent)
    right_exponent_term = (base** delta_exponent)

    inital_left_power = current_left_power
    inital_right_power = current_right_power

    i_have_no_idea_what_to_call_this_left = (delta_left*(left_exponent_term))
    i_have_no_idea_what_to_call_this_right = (delta_right*(right_exponent_term))
    counter = 0

    while(counter < numberOfSteps):
        current_left_power =  inital_left_power + ((i_have_no_idea_what_to_call_this_left*(right_exponent_term**counter))/base)
        current_right_power = inital_right_power + ((i_have_no_idea_what_to_call_this_right*(left_exponent_term**counter))/base)
        drive(int(current_left_power),int(current_right_power))
        sleep(deltaTime)
        counter += 1
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