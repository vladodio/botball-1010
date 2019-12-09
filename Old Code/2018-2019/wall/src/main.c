#include <kipr/botball.h>
const int lCliff = 1;
const int rCliff = 2;
const int lfCliff= 3;
const int rfCliff = 4;
const int pivot = 320;
//Wallaby sensors
const int touch=0; // touch sensor in grabber
const int start=0; // light sensor for starting
int go=0;
int current=0;
const int wire=3; // motor to repair comm wire

const int horizontal = 1683;
const int vertical = 520;
const int atLevel = 220;
const int atPipe = 590;
const int atUp = 2040;
const int raise = 0;
const int turn = 1;
const int push = 0;
const int ninety = 980;
const int semi = 2020;
const int forward = 430;
const int black = 2000;
void servoSlowRaise(int initial, int final){
    int count = initial;
    while(count < final){
        set_servo_position(raise,count);
        msleep(30);
        count+=5;
    }
    ao();
    msleep(200);
}
void wallFollowright() {
    if(get_create_rbump() == 0)
    {
        create_drive_direct(220, 100);
        msleep(5);
    }
    else
    {
        create_drive_direct (100, 240);
        msleep(5);
    }
}

int main()
{
    create_connect();
    enable_servos();
    	create_drive_direct(200, 0);
    	msleep(200);
    	create_drive_direct(0,0);
    	msleep(100);
    	create_drive_direct(-150, -150);
    	msleep(2000);
    create_drive_direct(0,0);
    	msleep(100);
       while (get_create_rcliff_amt() > black){  
        wallFollowright();
        msleep(1);
    }
       create_drive_direct(200, 200);
       msleep(200);
       while (get_create_rcliff_amt() > black){  
        wallFollowright();
        msleep(1);
    }
    create_drive_direct(0,0);
    msleep(100);
    
    create_drive_direct(200,200);
    msleep(200);
    while(get_create_lcliff_amt() > black){
        create_drive_direct(-200,-200);
        msleep(1);
    }
    create_drive_direct(0,0);
    msleep(100);
    while(get_create_rcliff_amt() > black){
        create_drive_direct(0,-100);
        msleep(1);
    }
    create_drive_direct(0,0);
    msleep(100);
    set_servo_position(raise,atUp);
    msleep(400);
    set_servo_position(turn, horizontal);
    msleep(400);
    create_drive_direct(-200,0);
    msleep(pivot);
    create_drive_direct(0,0);
    msleep(300);
    set_servo_position(raise,atLevel);
    msleep(400);
    while(!(digital(push))){
        create_drive_direct(200,200);
        msleep(1);
    }
    create_drive_direct(0,0);
    msleep(200);
    servoSlowRaise(atLevel, atUp);
    msleep(200);
    while(get_create_lcliff_amt() > black){
        create_drive_direct(-200,-200);
        msleep(1);
    }
    create_drive_direct(0,0);
    msleep(100);
    while(get_create_rcliff_amt() > black){
        create_drive_direct(0,-200);
        msleep(1);
    }
    create_drive_direct(0,0);
    msleep(100);
}
