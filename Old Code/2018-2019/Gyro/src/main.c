 /*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
|
|	Project: DemoGyroLib
|	Creators: Reza Torbati, Andrew Zhang
|	Date: Summer 2018
|	Description: basic library to teach people how to use the gyroscope to drive straight and turn
|	Contact: Reza Torbati - kofcrotmgiv@gmail.com    Andrew Zhang - infinitepolygons@gmail.com
|
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include <kipr/botball.h>
#include<config.h>
//Gyroscopes are always off by a specific angular velocity so we need to subtract this bias from all readings.
//Call calibrate_gyro to find what the gyroscope reads when the robot is at a complete stop (this is what the bias is). 
//The bias may change between turning the robot on when compared to the bias that the gyroscope has when it starts moving.
void calibrate_gyro()
{
   	//takes the average of 50 readings
    int i = 0;
    double avg = 0;
    while(i < 1000)
    {
        avg += gyro_z();
        msleep(5);
        i++;
    }
    bias = avg / 1000.0;
    printf("New Bias: %f\n", bias);//prints out your bias. COMMENT THIS LINE OUT IF YOU DON'T WANT BIAS READINGS PRINTED OUT
}

//the same as calibrate_gyro() except faster to type
void cg()
{
    calibrate_gyro();
}
		
//turns the robot to reach a desired theta. 
//If you are expecting this function to work consistantly then don't take your turns too fast.
//The conversions from each wallaby to normal degrees varies but usually ~580000 KIPR degrees = 90 degrees
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

//drives straight forward or backwards. The closer speed is to 0 the faster it will correct itself and the more consistent it will be but just do not go at max speed. Time is in ms. 
void drive_with_gyro(int speed, double time)
{ 
    double startTime = seconds();
    double theta = 0;
    while(seconds() - startTime < (time / 1000.0))
    {
        if(speed > 0)
        {
            create_drive_direct((double)(speed + speed * (1.920137e-15 + 0.000004470956*theta - 7.399285e-28*pow(theta, 2) - 2.054177e-18*pow(theta, 3) + 1.3145e-40*pow(theta, 4))) ,(double)(speed - speed * (1.920137e-16 + 0.000004470956*theta - 7.399285e-28*pow(theta, 2) - 2.054177e-18*pow(theta, 3) + 1.3145e-40*pow(theta, 4))));  //here at NAR, we are VERY precise
        }
        else//reverses corrections if it is going backwards
        {
            create_drive_direct((double)(speed - speed * (1.920137e-15 + 0.000004470956*theta - 7.399285e-28*pow(theta, 2) - 2.054177e-18*pow(theta, 3) + 1.3145e-40*pow(theta, 4))), (double)(speed + speed * (1.920137e-16 + 0.000004470956*theta - 7.399285e-28*pow(theta, 2) - 2.054177e-18*pow(theta, 3) + 1.3145e-40*pow(theta, 4))));         }
        //updates theta
        msleep(10);
        theta += (gyro_z() - bias) * 10;
    }
}


int main(){
    double degToticks180 = 6290;
    double degToticks90  = 6000;
    printf("started...\n");
    create_connect();
    printf("connected\n");
    //cg();
    printf("Calibrated\n");
    drive_with_gyro(200, 40000);
    //turn_with_gyro(200, -200, 90*(degToticks90));
    return(0);
}
