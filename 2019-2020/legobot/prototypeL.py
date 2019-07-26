# for driving motors and stuff
from wallaby import *

# imports the logger function
import logger

# runs the config file
import legobotConfig


# setup and other core functions
def init():
	pass


def disconnect():
	pass

# What side is gonna be right vs left????
def move(Lpower, Rpower, T):
	mav(Lmotor, Lpower)
	mav(Rmotor, Rpower)
	log.motor(Lpower, Rpower)
	msleep(T)


def stop(self, T):
	mav(Lmotor, 0)
	mav(Rmotor, 0)
	log.stop(T)
	msleep(T)


def turn(degree, direction, power=200):
	log.write("Turning to the" + direction + " " + degree +" degrees")
	if( direction[0].lower() == "r"):
		method_to_turn_right()
	else:
		method_to_turn_left()
