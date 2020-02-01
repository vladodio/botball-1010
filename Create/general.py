#!/usr/bin/python2
# general purpose functions for Explorer Post 1010's botball team
# create variant
import wallaby



#
import os
from datetime import datetime
from time import time

class logger:
	
	def __init__(self, log_folder="./"):
		_fileList = []		
		currDate = datetime.now()
#		date =  currDate.strftime("%a %b %d %-I:%M")
		for (dirpath, dirnames, filenames) in os.walk(log_folder):
		    _fileList.extend(filenames)
		_fileCount = len(_fileList)+1
		_logLocation = log_folder + "["+str(_fileCount)+"] " + currDate.strftime("%-I:%M %p") + ".log"
		self._logfile = open(_logLocation, "w+")
		_logfile.write( date + "\n")
		del _fileCount,_logLocation,_fileList,_logFolder

	def __del__(self):
		pass

	def round(self, num):
		return(float('%.3f'%(num)))

	def getTime(self):
		return(self.round(time() - self.startTime))

	def startClock(self): 
		self.startTime = time()

	def timeStamp(self):
		return("[ " +str(self.getTime())+ " ] ")

	def printf(self, *args, **kwargs):
		try:
			output = timeStamp()
			for item in args:
				output += " " + str(item)
			print(output)
			_logfile.write(output +"\n")
		except(NameError):
			print("setup not complete yet.")
			output = ""
			for item in args:
				output += " " + str(item)
			print("intended output:" + output)


class roomba:

	self.turn_methods = ['gyro','time']
	def __init__(self, logging=False, log_directory="./"):
		if(logging):
			self._logging = True
			self.log = logger()
		else:
			self._logging = False
		self.current_right_power = 0
		self.current_left_power = 0
		self.current_turn_theta = 0
		wallaby.create_connect():


	def __del__(self):
		self.stop()
		wallaby.create_disconnect()

	def msleep(time):
		wallaby.msleep(time)

	def drive(left_power, right_power):
		if(logging):
			pass
		try:
			self.current_left_power = left_power
			self.current_right_power = right_power
			wallaby.create_drive_direct(left_power, right_power)	

	def stop(self):
		self.current_right_power = 0
		self.current_left_power = 0
		self.drive(0,0)

	def ao(self):
		self.stop()
		wallaby.ao()

	def pause():
		pass

	def _turn_with_gyro(self, left_power, right_power, theta):
		pass

	def _turn_with_time(self, left_power, right_power, theta):
		pass

	def turn(self, left_power, right_power, theta, direction=1, turn_method = 0):
		if(turn_method == 0):
			if(direction > 0):
				self._turn_with_gyro(left_power, right_power, theta)
			elif(direction < 0)
				self._turn_with_gyro(left_power, right_power, -theta)
			else:
				raise Exeception("Direction not properly defined. Adjust 4th field accordingly.")
		elif(turn_method == 1):
			if(direction > 0):
				self._turn_with_gyro(left_power, right_power, theta)
			elif(direction < 0)
				self._turn_with_gyro(left_power, right_power, -theta)
			else:
				raise Exeception("Direction not properly defined. Adjust 4th field accordingly.")
		else:
			if(direction > 0):
				eval("self._turn_with_"+ str(self.turn_methods[turn_method]) +"(left_power, right_power, theta)")
			elif(direction < 0)
				eval("self._turn_with_"+ str(self.turn_methods[turn_method]) +"(left_power, right_power, -theta)")
			else:
				raise Exeception("Direction not properly defined. Adjust 4th field accordingly.")

	def wallFollow():
		pass	

	def lineFollow():
		pass

	def pid():
		pass 

	def servo_setup():
		pass

	def set_servo():
		pass

	def motor_setup():
		pass

	def motor_control():
		pass

	def log():
		pass
