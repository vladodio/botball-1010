#!/usr/bin/python2.7
import os, sys
from wallaby import *

degrees_to_ticks = 6100
gyroscope_bias = 2.2699

current_left_power = 0
current_right_power = 0 
current_theta = 0

def startRoomba():
	create_connect()

def move(Lpower, Rpower):
	global current_right_power,current_left_power
	current_left_power = Lpower
	current_right_power = Rpower
	create_drive_direct(Lpower,Rpower)

def sleep(sleepTime):
	msleep(sleepTime)

def getGyroReading():
	return(gyro_z())

def turn(targetDegrees, Lpower, Rpower, tickLength=10):
	global current_theta
	targetTheta = targetDegrees * degrees_to_ticks
	move(Lpower,Rpower)
	while(current_theta < targetTheta):
		sleep(tickLength)
		current_theta += abs(getGyroReading() - gyroscope_bias) * tickLength
	move(0,0)

def main():
	startRoomba()
	turn(360, -500, 500)

if(__name__ == '__main__'):
	main()