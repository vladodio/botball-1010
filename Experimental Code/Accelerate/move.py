#!/usr/bin/python2.7
import os, sys
from wallaby import *
from time import time

current_left_power = 0
current_right_power = 0


def sec():
	return time()


def drive(Lpower, RPower):
	create_drive_direct(LPower, RPower)


def move(LPower, RPower, time, deltaAccel  = 50, deltaDecel = 50, deltaTime = 50):
	global current_right_power, current_left_power
	
	
	while((Lpower != current_left_power) and (Rpower != current_right_power)):
		drive(current_left_power+deltaAccel, current_right_power+deltaAccel)

	drive()