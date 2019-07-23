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


#import configparser
# Maybe theres a better solution
# ask in IBC? 



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
# multiply by 100 for ms
	def timer(self, T):
		start = cTime()
		end = start + T
		while(end > cTime()):



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
                raise Exeception("Unable to open Logfile")
            self.startTime = cTime()
            self.logFile.write("[ 0.000 ] Start of Log.\n")

        def __del__(self):
            self.write("End Of Log.")
            self.logFile.close

        def write(self, info):
            self.logFile.write( "[ " + ("%.3f" %(cTime() - self.startTime )) + " ] " + info + "\n")

        def writeNT(self, info):
        	self.logFile.write(info+ "\n")

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



