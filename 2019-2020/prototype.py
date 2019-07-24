# for driving motors and stuff
#import kipr.shitty.module.py
from wallaby import *

# for logging
from time import time as cTime

#import threading ??
# maybe i'll just build the threading into these funtions?
# good naming convention??
# moveWithThread?
#


#import configparser
# Maybe theres a better solution
# ask in IBC?


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


	def __init__(self, logger="none"):
		enable_servos()
		if(isinstance(logger, str)):
			self.loggingEnabled=False
		else:
			self.loggingEnabled=True

	def __del__(self):
		disable_servos()		 


	def move(self, Lpower, Rpower, T):
		create_drive_direct(Lpower, Rpower)
		msleep(T)

	def stop(self, T):
		create_drive_direct(0, 0)
		msleep(T)

	def turn(self, degree, direction, power=200):
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


	def wallfollowR(self, T):




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

# drones?
"""
class drone():


"""

class config():

        def __init__(self, pathOfConfig="/home/alex/config.ini"):
                try:
                        self.config = open(pathOfConfig, "r")
                except:
                        print("VALID FILE????")

        def __del__(self):
                self.config.close()

        def get(self, header, variable, returnType="f"):
                #ranges on searches are prob off
                headerFound=False
                valueLength=0
                isolatedValue=""
                found=False
                try:
                        for line in self.config:
                                if(not headerFound and ("[" == line[0]) and (line[1:len(header)+2] == (header + "]"))):
                                        headerFound=True
                                        continue
                                if(headerFound and line[0] == "["):
                                        break
                                if(headerFound and (line[:len(variable)+1] == (variable + "="))):
                                        valueLength=len(line)-len(variable)-1
                                        print(line[-valueLength:])
                                        print(valueLength)
                                        isolatedValue=line[-valueLength:]
                                        found=True
                                        break
                except:
                        pass

                if(not headerFound):
                        raise Exception("Header not found.")
                if(not found):
                        raise Exception("Variable was not found.")

                if(returnType=="f"):
                        return(float(isolatedValue))
                elif(returnType=="i"):
                        return(int(isolatedValue))
                elif(returnType=="s"):
                        return(isolatedValue)
                else:
                        return(isolatedValue)


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
