#!/usr/bin/python

# not functional at the moment 
# DO NOT USE
# Note to self: Rewrite from scratch, to many shitty conventions present

import os
from datetime import datetime
from time import time

# Timer
startTime=0
def round(num):
	return(float('%.3f'%(num)))

def getTime():
	return(round(time() - startTime))

def startClock():
	global startTime 
	startTime = time()

def timeStamp():
	return("[ " +str(getTime())+ " ] ")


# timestamp the top of the log
currDate = datetime.now()
date =  currDate.strftime("%a %b %d %-I:%M")


# Log File
_logFolder = "./"
_fileList = []
for (dirpath, dirnames, filenames) in os.walk(logFolder):
    _fileList.extend(filenames)
_fileCount = len(_fileList)+1
_logName =  "["+str(_fileCount)+"] " + currDate.strftime("%-I:%M %p") + ".log"
_logLocation = _logFolder + _logName
_logfile = open(_logLocation, "w+")

# timestamp the top of the log
_logfile.write( date + "\n")

# end user functions
'''

# decorators in python2.7 are a pain in the ass
# figure it out???
def log(function):
	def wrapper(*args, **kwargs):
		function(args, kwargs)
		output = str(function) + " is running with args:" + str(args) +"\n"
		print(output)
		_logfile.write(output)
		function(args, kwargs)
'''

def printf(*args, **kwargs):
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

# mem cleanup
del _fileCount,_logLocation,_fileList,_logFolder
