#!/usr/bin/python2.7
import os, sys
from wallaby import *

# hand calculate for now
# ******* note to self: Build calibrate
degrees_to_ticks = 6100
gyroscope_bias = 2.2699

# global variables required for code to function
# maybe we should switch to classes *cough* *cough*
current_left_power = 0 
current_right_power = 0 
current_theta = 0

# more intuitive than create_connect()
def startRoomba():
	create_connect()

# standard move(no accelerate)
def move(Lpower, Rpower):
	global current_right_power,current_left_power
	current_left_power = Lpower
	current_right_power = Rpower
	create_drive_direct(Lpower,Rpower)

# just here to make code more portable for the time being 
# remove ASAP
def sleep(sleepTime):
	msleep(sleepTime)

# not needed, but i prefer looking at this over gyro_z()
def getGyroReading():
	return(gyro_z())

# gyro turn, more testing needed and optimization too
# tick length is time between checks of the gyroscopes value
def turn(targetDegrees, Lpower, Rpower, tickLength=10):
	global current_theta
	targetTheta = targetDegrees * degrees_to_ticks
	move(Lpower,Rpower)
	while(current_theta < targetTheta):
		sleep(tickLength)
		current_theta += abs(getGyroReading() - gyroscope_bias) * tickLength
	move(0,0)

# litle main function for testing
def main():
	startRoomba()
	turn(360, -500, 500)

if(__name__ == '__main__'):
	main()
