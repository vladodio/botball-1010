#include <kipr/botball.h>
const int TRUE=1;
const int black = 2000;
const int pivot = 320;
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

const int horizontal = 1683;
const int vertical = 520;
const int atLevel = 240;
const int atPipe = 630;
const int atUp = 2040;
const int raise = 0;
const int turn = 1;
const int push = 0;
const int ninety = 940;
const int semi = 1910;
const int forward = 520;

void servoSlowRaise(int initial, int final){
    int count = initial;
    while(count < final){
        set_servo_position(0,count);
        msleep(20);
        count+=5;
    }
    ao();
    msleep(200);
}
void secondWallFollowright() {
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
int wallFollowleft() {
    if(get_create_lbump() == 0)
    {
        create_drive_direct(100, 180);
        msleep(5);
    }
    else
    {
        create_drive_direct (200, 100);
        msleep(5);
    }
}

int wallFollowright() {
    if(get_create_rbump() == 0)
    {
        create_drive_direct(180, 100);
        msleep(5);
    }
    else
    {
        create_drive_direct (100, 200);
        msleep(5);
    }
}
void main(){
    create_connect();
    enable_servos();
    while (get_create_rfcliff_amt() > black){  
        wallFollowright();
        msleep(1);
    }
    create_drive_direct(200,200);
    msleep(200);
    create_drive_direct(0,0);
    msleep(100);
	create_drive_direct(-200,200);
	msleep(ninety);
	create_drive_direct(0,0); 
	msleep(1000);
	create_drive_direct(200,200);
	msleep(forward);
	create_drive_direct(0,0); 
	msleep(1000);
	set_servo_position(raise, atPipe);
	msleep(200);
	set_servo_position(turn, vertical);
	msleep(200);
	create_drive_direct(-200,200);
	msleep(semi); 
	create_drive_direct(0,0); 
	msleep(1000);
	create_drive_direct(-250,-250);
	msleep(700);
	set_servo_position(raise, atUp);
	msleep(200);
	create_drive_direct(-200,200);
	msleep(semi);
    create_drive_direct(0,0);
    msleep(100);
	create_drive_direct(-250,-250);
	msleep(900);
	create_drive_direct(200,-200);
	msleep(ninety);
    create_drive_direct(0,0);
    msleep(100);
	while (!get_create_lbump() && !get_create_rbump()){
    	create_drive_direct(200,200);
    	msleep(1);
	}
	create_drive_direct(0,0);
	msleep(200);
	create_drive_direct(-200,200);
	msleep(ninety);
    create_drive_direct(0,0);
    msleep(100);
    create_drive_direct(-150, -150);
    msleep(1500);
    create_drive_direct(0,0);
    msleep(100);
    while (get_create_rcliff_amt() > black){  
        secondWallFollowright();
        msleep(1);
    }
    create_drive_direct(200, 200);
    msleep(200);
    while (get_create_rcliff_amt() > black){  
        secondWallFollowright();
        msleep(1);
    }
    create_drive_direct(0,0);
    msleep(100);
    
    create_drive_direct(200,200);
    msleep(350);
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
    //servoSlowRaise(atLevel, atUp);
   // msleep(200);
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
    create_drive_direct(-200,200);
    msleep(semi);
    create_drive_direct(200,200);
    msleep(300);
    mav(0, -400);
    msleep(1000);
    mav(0,1);
    msleep(200);
    /*
    create_drive_direct(200,200);
    msleep(400);
    create_drive_direct(0,0);
    msleep(100);
    mav(0, 400);
    msleep(1000);
    mav(0,1);
    msleep(200);
    create_drive_direct(0,200);
    msleep(100);
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
    create_drive_direct(-200,-200);
    msleep(200);

*/

}