#!/usr/bin/env python2.7
#

# imports
from time import time
from time import sleep
# Constants to fine tune
#Kp = 1 
#Ki = 1
#Kd = 1

def pid(Kp,Ki,Kd):
	startingTemp = 23.0 
	wantedTemp = 100.0
	currentTemp = startingTemp
	startTime = float(int(time()*3)/3)

	accumulation_of_error = 0
	last_error = 0
	output = 0
	counter = 0
	delta_time = .2

	while(True):
		currentTemp += output
	# sleep between cycles
		sleep(delta_time)

	# error from wanted value 
		error = (wantedTemp - currentTemp)

	#
		accumulation_of_error += error * delta_time
		derivative_of_error = (error - last_error) / delta_time
		last_error = error

	#
		output = (error * Kp) + (accumulation_of_error * Ki) + (derivative_of_error * Kd)

		if(abs(error) < .5):
			counter+=1
		else:
			counter = 0
		if(counter > 10):
			return(float(int(time()*3)/3)-startTime)
		print("PID output: "+str(output) + "  temp: " + str(currentTemp))
