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

