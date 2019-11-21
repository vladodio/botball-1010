# general purpose functions for Explorer Post 1010's botball team
# legobot variant
from wallaby import *

# general function for moving
def move(lPower, rPower, time=null):
    mav(left_motor, lPower)
    mav(right_motor, rPower)
    try:
        msleep(time)
        mav(left_motor, 0)
        mav(right_motor, 0)
    except:
        pass

def turn(deg):
    pass

def turn_right_wheel(deg):
    pass

def turn_left_wheel(deg):
    pass

def lower_pulley():
    set_servo_position(claw, open)
    msleep(500)
    mav(pulley, -1500)
    msleep(2300)
    mav(pulley, 0)
    
def raise_pulley():
    set_servo_position(claw, closed)
    msleep(500)
    mav(pulley, 1500)
    msleep(2400)
    mav(pulley, 0)

def go_to_black():
    while(analog(toph_left) < 2000 or analog(toph_right) < 2000):
        move(1000, 1000)
    stop()

def go_to_white():
    while(analog(toph_left) > 2000 or analog(toph_right) > 2000):
        move(1000, 1000)
    stop()

def go_to_object():
    for i in range(50):
        camera_update()
        msleep(1)
    
    while(get_object_count(yellow) = 0 or get_object_center_y(yellow) > 70):
        camera_update();
        msleep(1);
        line_follow()
    lower_pulley()
    raise_pulley()

def stop():
    mav(left_motor, 0)
    mav(right_motor, 0)

def wait():
    msleep(5000)

#BEGIN--------------------------

raise_pulley()
lower_pulley()

"""
wait_for_light(5)
shut_down_in(119)

camera_open_black()
msleep(2000)

raise_pulley()

turn_left_wheel(90)
wait()
go_to_black()
go_to_white()
go_to_black()
wait()
turn(-90)
wait()
go_to_object()
wait()
move(5)
go_to_black()
wait()
turn_right_wheel(90)
wait()
for i in range(3):
    go_to_object()
    
while(not analog(toph_front)):
    line_follow()

wait() 
turn_left_wheel(90)
turn_right_wheel(90)
wait()
go_to_object()
turn(90)
lower_pulley()
"""
