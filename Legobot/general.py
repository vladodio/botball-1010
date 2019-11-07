# general purpose functions for Explorer Post 1010's botball team
# legobot variant

# general function for moving
def move(lPower, rPower, time=null):
	mav(lMotor, lPower)
	mav(rMotor, rPower)
	try:
		msleep(time)
		mav(lMotor, 0)
		mav(rMotor, 0)
	except:
		pass


