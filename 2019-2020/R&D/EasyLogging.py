#!/usr/bin/env python2.7


# Timer
from time import time # alternative to seconds from wallaby package for testing

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



# Log File
from os import walk
logFolder = "./logs/"
logNamePreface = "logs#"
_fileList = []
for (dirpath, dirnames, filenames) in walk(logFolder):
    _fileList.extend(filenames)

_fileCount = len(_fileList)+1
_logLocation = logFolder + logNamePreface + str(_fileCount)+".log"
_logfile = open(_logLocation, "w+")
del _fileCount,_logLocation,_fileList

# timestamp the top of the log
from datetime import datetime
date = datetime.now()
date =  date.strftime("%a %b %d %I:%M")
_logfile.write( date + "\n")

# end user functions
def log(function):
	def wrapper(*args, **kwargs):
		function(args, kwargs)
		_logfile.write(function+ " is running with args:" + args +"\n")

def printf(*args, **kwargs):
	output = timeStamp()
	for item in args:
		output += " " + str(item)
	print(output)
	_logfile.write(output +"\n")


from time import sleep
startClock()
sleep(1)
printf("hi")
sleep(1)
printf("hi2", "hello")
from subprocess import call
call(["ls","./logs"])