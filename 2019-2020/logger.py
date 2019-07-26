from time import time as cTime
# To do:
# 	 Properly do log file naming
#    maybe use datetime (Not that type of datetime you mong)

class logger:


	def __init__(self, folder="~/logs/"):
		try:
			self.logFile = open(folder+"latest-run.log", "w")
		except:
			raise Exeception("Unable to open destination folder.")
		self.startTime = cTime()
		self.logFile.write("[ 0.00 ] Start of Log.\n")


	def __del__(self):
		self.write("End Of Log.")
		self.logFile.close()


	def write(self, info):
		self.logFile.write( "[ " + ("%.2f" %(cTime() - self.startTime )) + " ] " + info + "\n")


	def writeNT(self, info):
		self.logFile.write(info+ "\n")


	def motor(self, Lpower, Rpower, T):
		self.write("Moving with L: " + Lpower + " R: " + Rpower + " for " + T + "seconds")


	def sensor(self, sensorName, sensorValue):
		self.write(sensorName+ "'s current value is " + sensorValue)
	
	
	def stop(self, T):
		log.write("Stopping for " + T + " ms")


	def fatalError(self, error):
		self.writeNT("+++ FATAL ERROR +++")
		self.write(error)
		self.writeNT("+++ END OF REPORT +++")


	def warning(self, error):
		self.writeNT("*** warning ***")
		self.write(error)
		self.writeNT("*** end of warning ***")
