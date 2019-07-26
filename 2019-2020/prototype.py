# for driving motors and stuff
#from wallaby import *
from dummy import *
# for logging
from time import time as cTime
import sys


#import threading ??
# maybe i'll just build the threading into these funtions?
# good naming convention??
# moveWithThread?
#


# To do list:

# Do we actually need threading??
# if we do can we use decorators for REASONS??

# maybe the class approch was flawed
# in honestly theres not much it needs to be referenced
# only difficult part would be the logging
# decorators to the rescue??

# Figure out what the R&D department is gonna work on ^-^

# Dan-CV (Or alternatives)

# Optimization of the logger class is important
# The amount of times its going to be called...

# Gyro code?
# And by extention calibration programs

# Other



# fix the log function 


# setup and other core functions
def init():
	create_connect()
	enable_servos()
	log.write("ROOMBA OBJECT CREATED")

def disconnect():
	disable_servos()
	create_stop()
	create_disconnect()
	log.write("ROOMBA OBJECT DESTROYED")

# note to self cTime returns a time is seconds
# multiply by 100 for msleep
def timer(self, T, func):
	start = cTime()
	end = start + T
	while(end > cTime()):
		func()


# base movement functions
#figure out which side is left and which is right
def move(Lpower, Rpower, T):
	create_drive_direct(Lpower, Rpower)
	self.log.write("Moving with " + Lpower + " " + Rpower + "for " + T + "ms")
	msleep(T)


def stop(self, T):
	create_drive_direct(0, 0)
	self.log.write("Stopping for " + T + " ms")
	msleep(T)

def turn(self, degree, direction, power=200):
	self.log.write("Turning to the" + direction + " " + degree +" degrees")
	if( direction[0].lower() == "r"):
# fix this
		method_to_turn_right()
	else:
# fix this also
		method_to_turn_left()


def wallfollowL(self, T):

	while(True):
		if(get_create_lbump() == 0):
			create_drive_direct(100, 200)
			msleep(5)
		else:
			create_drive_direct (200, 100)
			msleep(5)
		msleep(1)







