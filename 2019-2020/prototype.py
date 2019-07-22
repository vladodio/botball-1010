import kipr.shitty.module.py


#import threading ??
# maybe i'll just build the threading into these funtions?
# uses for threading:
# moveNoWait? 
#


#import configparser
# Maybe theres a better solution
# ask in IBC?

class create():


	def __init__(self, R, L):
		enable_servos()

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


	def __init__(self):
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

	def __init__(self, pathOfConfig):
		try:
			self.config = open(pathOfConfig, r)
		except:
			print("VALID FILE????")

	def __del__(self):
		#idk i dont think i need a destructor?
		print("Config Destroyed")

	def get(self, header, variable):
		#ranges on searches are prob off
		i=0
		p=0
		line=""
		while(True):
			line=self.config.readline(i)
			if(line[0] == "["): # intent: look at the first character of the line
				if(line[0:] == ("[" + header + "]") ): # intent: compare the header to the defined header
					++i
					while(True):
						line=self.config.readline(i) # intent: continue to look at the lines below the heading
						if(line[0] == "[" or line[0] == "<"): # intent: second check is too look for end of file character
							raise Exception("Variable not found in config file.")
						try: # intent: make sure the code doesn't error if one line is shorter than the given var
							if(line[0:len(variable)+1] == variable):
								return(line[len():i])
						except:
							pass
						i++
			i++
		
