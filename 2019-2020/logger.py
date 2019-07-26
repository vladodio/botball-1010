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
