# general purpose functions for Explorer Post 1010's botball team
# legobot variant
from wallaby import *

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

def turn(deg):
    pass

def turn_right_wheel(deg):
    pass

def turn_left_wheel(deg):
    pass

def lower_pulley():
    pass

def raise_pulley(stack):
    pass

def go_to_black():
    pass

def go_to_white():
    pass


#BEGIN--------------------------
wait_for_light(2)
shut_down_in(119)

lower_pulley()
raise_pulley(1)

turn_left_wheel(90)
go_to_black()
go_to_white()
go_to_black()
turn(-90)
go_to_object()
lower_pulley()
raise_pulley(2)

move(5)
go_to_black()
turn_right_wheel(-90)
while(not other_sensor)