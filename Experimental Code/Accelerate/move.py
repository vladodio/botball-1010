#!/usr/bin/python2.7
import os, sys
from wallaby import *
from time import time

current_left_power = 0
current_right_power = 0

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


def move(Lpower, Rpower, time, decelerationOn=True, numberOfSteps= 5, deltaTime = 50):
	global current_right_power, current_left_power

	startTime = sec()
	endTime = startTime+time
	accelTo(Lpower, Rpower, numberOfSteps, deltaTime)
	if(decelerationOn):
		endTime -= (numberOfSteps*deltaTime)
		while(sec() < endTime):
			sleep(1) # maybe this value needs to be bigger
		accelTo(0,0,numberOfSteps,deltaTime)

	