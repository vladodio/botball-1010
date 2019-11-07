#!/usr/bin/env python2.7

# First REAL attempt at a pid function of any kind
# bugs to be expected
# hopefully this works as a blueprint towards a better line follow
#

from random import randint
from time import sleep
from time import time

temp = 23.0

def setTemp(power):
	global temp
	temp += .1*power

def pid(wantedTemp, Kp, Ki, Kd):
	state = False
	last_error = 0
	delta_time = .25
	accumulation_of_error = 0
	output = 0
	counter = 0
	startTime = time()

	while(True):
		setTemp(output)
		error = (wantedTemp - temp)
		accumulation_of_error += error * delta_time
		derivative_of_error = (error - last_error) /delta_time
		last_error = error
		output = (error * Kp) + (accumulation_of_error * Ki) + (derivative_of_error * Kd)
		
		print(output)
		print("TEMP : "+str(temp))
		if(abs(temp - wantedTemp) < 1):
			counter += 1
		else:
			counter = 0
		if(counter > 10):
			print(str(time()-startTime))
			break
		sleep(delta_time)

pid(70, 1.7, 1, -.4)