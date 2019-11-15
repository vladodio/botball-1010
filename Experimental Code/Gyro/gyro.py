#!/usr/bin/python
import os, sys
from wallaby import *

# for testing purposes
bias = -0.9162

def main():
    #create_connect()
    calibrate_gyro(3000)
    #drive_with_gyro(300, 7000)

def calibrate_gyro(cycles):
    i = 0
    avg = 0
    while(i < cycles):
        avg += gyro_z()
        msleep(2)
        i += 1
    bias = avg / float(cycles)
    print(bias)





# Time given in seconds
# speed given in 
def drive_with_gyro(speed, time):

    startTime = seconds()
    theta = 0
    while(seconds() - startTime < (time / 1000.0)):
        if(speed > 0):
            create_drive_direct(int(speed + speed * (1.920137e-15 + 0.000004470956*theta - 7.399285e-28*(theta**2) - 2.054177e-18*(theta** 3) + 1.3145e-40*(theta** 4))) , int(speed - speed * (1.920137e-16 + 0.000004470956*theta - 7.399285e-28*(theta** 2) - 2.054177e-18*(theta** 3) + 1.3145e-40*(theta** 4))))
        else:
            create_drive_direct(int(speed - speed * (1.920137e-15 + 0.000004470956*theta - 7.399285e-28*(theta**2) - 2.054177e-18**(theta** 3) + 1.3145e-40*(theta** 4))), int(speed + speed * (1.920137e-16 + 0.000004470956*theta - 7.399285e-28*(theta** 2) - 2.054177e-18*(theta** 3) + 1.3145e-40*(theta** 4))))
        msleep(10)
        theta += (gyro_z() - bias) * 10

if __name__== "__main__":
    sys.stdout = os.fdopen(sys.stdout.fileno(),"w",0)
    main();



void turn_with_gyro(int left_wheel_speed, int right_wheel_speed, double targetTheta)
{
    double theta = 0;//declares the variable that stores the current degrees
    create_drive_direct(left_wheel_speed , right_wheel_speed);//starts the motors

    //keeps the motors running until the robot reaches the desired angle
    while(theta < targetTheta)
    {
        msleep(10);//turns for .01 seconds
        theta += abs(gyro_z() - bias) * 10;//theta = omega(angular velocity, the value returned by gyroscopes) * time
    }
    //stops the motors after reaching the turn
    create_drive_direct(0, 0);
}
