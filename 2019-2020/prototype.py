# for driving motors and stuff
from wallaby import * 

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



class create():

# setup and other core functions
	def __init__(self, logger):
		create_connect()
		enable_servos()
		self.log=logger
		self.log.write("ROOMBA OBJECT CREATED")

	def __del__(self):
		disable_servos()
		create_stop()
		create_disconnect()
		self.log.write("ROOMBA OBJECT DESTROYED")

# note to self cTime returns a time is seconds
# multiply by 100 for msleep
	def timer(self, T, func):
		start = cTime()
		end = start + T
		while(end > cTime()):
			func()


# base movement functions
#figure out which side is left and which is right
	def move(self, Lpower, Rpower, T):
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

		while()
			if(get_create_lbump() == 0):
				create_drive_direct(100, 200)
				msleep(5)
			else:
				create_drive_direct (200, 100)
				msleep(5)
			msleep(1)





"""

class legobot():


	def __init__(self, R, L, logger):
		self.Rmotor=R
		self.Lmotor=L
		enable_servos()

	def __del__(self):
		disable_servos()


	def move(self, Lpower, Rpower, time):
		mav()

	def stop(self, time=.005):
		mav()

"""


class logger():

		def __init__(self, folder="/home/alex/"):
			try:
				self.logFile = open(folder+"latest-run.log", "w")
			except:
				raise Exeception("Unable to open destination folder.")
			self.startTime = cTime()
			self.logFile.write("[ 0.000 ] Start of Log.\n")

		def __del__(self):
			self.write("End Of Log.")
			self.logFile.close

		def write(self, info):
			self.logFile.write( "[ " + ("%.3f" %(cTime() - self.startTime )) + " ] " + info + "\n")

		def writeNT(self, info):
			self.logFile.write(info+ "\n")

"""
		ok basically decorators are too big brain for me
		further research required
		def decorate(func):
			def inner():
				func()
			return inner
"""
		def sensor(self, sensorName, sensorValue):
			self.write(sensorName+ "'s current value is " + sensorValue)

		def fatalError(self, error):
			self.write("+++ FATAL ERROR +++")
			self.write(error)
			self.write("+++ END OF REPORT +++")

		def warning(self, error):
			self.write("*** warning ***")
			self.write(error)
			self.write("*** end of warning ***")



