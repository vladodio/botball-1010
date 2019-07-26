# for driving motors and stuff
from wallaby import *

# Imports the logger function 
import logger

# Runs the config file
import createConfig

# To do list:

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
	log.write("ROOMBA CONNECTED")


def disconnect():
	disable_servos()
	create_stop()
	create_disconnect()
	log.write("ROOMBA DISCONNECTED")


# What side is gonna be right vs left????
def move(Lpower, Rpower, T):
	create_drive_direct(Lpower, Rpower)
	log.motor(Lpower, Rpower)
	msleep(T)


def stop(self, T):
	create_drive_direct(0, 0)
	log.stop(T)
	msleep(T)


def turn(degree, direction, power=200):
	log.write("Turning to the" + direction + " " + degree +" degrees")
	if( direction[0].lower() == "r"):
		method_to_turn_right()
	else:
		method_to_turn_left()


def wallfollow(direction, T):
	eTime = cTime() + T
	if(direction[0].lower() == "l" )
		while(eTime > cTime()):
			if(get_create_lbump() == 0):
				create_drive_direct(100, 200)
				msleep(5)
			else:
				create_drive_direct (200, 100)
				msleep(5)
			msleep(1)
	else:
		while(eTime > cTime()):
			if(get_create_lbump() == 0):
				create_drive_direct(200, 100)
				msleep(5)
			else:
				create_drive_direct (100, 200)
				msleep(5)
			msleep(1)
