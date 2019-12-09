#include <kipr/botball.h>
const int TRUE=1;
const int black = 2000;
const int pivot = 320;
const int pivot2 = 320;
const int forward2 = 215;
//Create sensors
const int lCliff = 1;
const int rCliff = 2;
const int lfCliff= 3;
const int rfCliff = 4;

//Wallaby sensors
const int touch=0; // touch sensor in grabber
const int start=0; // light sensor for starting
int go=0;
int current=0;
const int wire=3; // motor to repair comm wire
const int atWire = 800;
const int horizontal = 1683;
const int vertical = 520;
const int atLevel = 240;
const int atPipe = 625;
const int atUp = 2040;
const int raise = 0;
const int turn = 1;
const int push = 9;
const int ninety = 980;
const int semi = 2020;
const int forward = 550;
int main()
{
    create_connect();
    enable_servos();
    set_servo_position(raise,atUp);
    msleep(200);
    create_drive_direct(-200, -200);
    msleep(800);
    create_drive_direct(0,0);
    msleep(100);
    create_drive_direct(0,200);
    msleep(100);
    create_drive_direct(0,0);
    msleep(100);
    while (get_create_rcliff_amt() > black){
        create_drive_direct(200,200);
    	msleep(1);
    }
    create_drive_direct(0,0);
    msleep(100);
    while (get_create_lcliff_amt() > black){
        create_drive_direct(200,0);
    	msleep(1);
    }
    create_drive_direct(0,0);
    msleep(100);
 
    create_drive_direct(200,200);
    msleep(forward2);
    create_drive_direct(0,0);
    msleep(300);
    create_drive_direct(0,200);
    msleep(500);
	create_drive_direct(0,0);
    msleep(300);
    set_servo_position(raise,atPipe);
    msleep(200);
    create_drive_direct(0,0);
    msleep(300);
    set_servo_position(turn,vertical);
    msleep(200);
    create_drive_direct(0,0);
    msleep(300);
    create_drive_direct(200,-200);
    msleep(300);
	create_drive_direct(0,0);
    msleep(300);
    create_drive_direct(200,0);
    msleep(200);
}
