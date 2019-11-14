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

def lower_pulley(stack):
    mav(pulley, -1000)
    msleep(stack*500)
    mav(pulley, 0)
    set_servo_position(claw, open)
    msleep(500)
    mav(pulley, -500)
    msleep(stack*500)
    mav(pulley, 0)

def raise_pulley(stack):
	set_servo_position(claw, closed)
	msleep(500)
    mav(pulley, 1000)
    msleep(stack*1000)
    mav(pulley, 0)

def go_to_black():
    while(analog(toph_left) > 2000 or analog(toph_right) > 2000):
    	move(1000, 1000)
    mav(left_motor, 0)
	mav(right_motor, 0)

def go_to_white():
    while(analog(toph_left) < 2000 or analog(toph_right) < 2000):
    	move(1000, 1000)
    mav(left_motor, 0)
	mav(right_motor, 0)

def go_to_object(stack):
	for i in range(50):
		camera_update()
		msleep(1)
	
	while(get_object_count(yellow) = 0 or get_object_center_y(yellow) > 70):
		camera_update();
		msleep(1);
		line_follow()
	lower_pulley(stack)
	raise_pulley(stack)


#BEGIN--------------------------

raise_pulley(1)
lower_pulley(1)

"""
wait_for_light(5)
shut_down_in(119)

camera_open_black()
msleep(2000)

raise_pulley(1)

turn_left_wheel(90)
go_to_black()
go_to_white()
go_to_black()
turn(-90)
go_to_object(2)

move(5)
go_to_black()
turn_right_wheel(90)
while(not toph_front):
	for i in range(3,6):
		go_to_object(3)

turn_left_wheel(90)
turn_right_wheel(90)
go_to_object(6)
turn(90)
lower_pulley(6)
"""