# general purpose functions for Explorer Post 1010's botball team
# create variant

# general function for moving
def cdd(lpower, rPower):
	create_drive_direct(lPower,rPower)
	


def move(lPower, rPower, time=null):
	create_drive_direct(lPower, rPower)
	try:
		msleep(time)
		create_drive_direct(lPower, rPower)
	except:
		pass


