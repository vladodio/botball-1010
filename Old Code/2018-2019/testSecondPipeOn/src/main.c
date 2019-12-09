#include <kipr/botball.h>
/* Issues:
/       The start function doesn't compile
/       The code is LACKING comments, Remember Zain has to understand what the code is doing
/       Changing the constant names to be more descriptive wouldn't hurt
/       Checklist doesn't exist and very much needs to
/       
/
*/

const int TRUE = 1;
const int black = 2000;
const int pivot = 250;
const int forwardbl = 470;

//Create sensors
const int lCliff = 1;
const int rCliff = 2;
const int lfCliff = 3;
const int rfCliff = 4;

//Wallaby sensors
const int touch = 0; // touch sensor in grabber
const int start = 0; // light sensor for starting

const int right = 1;
const int left = -1;

int go = 0;
int current = 0;

const int wire = 3; // motor to repair comm wire
const int atWire = 800;

const int horizontal = 1683;
const int vertical = 520;

const int atLevel = 245;
const int atPipe = 625;
const int atUp = 1600;

// The tire claw consts
const int raise = 0; // The servo that raises the tireclaw
const int turner = 1; // The servo that rotates the tireclaw
const int push = 9; // The pushButton that detects the pipe

const int ninety = 1000;
const int semi = 2000;

const int forward = 530;
const int pivot2 = 320;
const int forward2 = 228;

// Compacted Functions

void drive(int lPower, int rPower, int sleep){
    create_drive_direct(lPower, rPower);
    msleep(sleep);
}

void stop(int sleep){
    create_drive_direct(0, 0);
    msleep(sleep);
}

// Turning defined with lennards msleep method
void turn(int degree, int direction, int adjustment){
    if(degree == 90){
        create_drive_direct(200 * (direction), -200 * (direction));
        msleep(ninety+adjustment);
    }
    else if(degree == 180){
        create_drive_direct(200 * (direction), -200 * (direction));
        msleep(semi+adjustment);
    }
    else{
        printf("Angle not Defined??");
        //exit();
    }
}

// Gyroscope package




// Turning defined with gyroscope
/*
void turn(int degree, int direction, int adjustment){
    if(degree == 90){
        
    }
    else if(degree == 180){
        
    }
    else{
        printf("Angle not Defined??");
        //exit();
    }
}
*/









// Servo functions
void servoSlowRaise(int initial, int final){
    int count = initial;
    while(count < final){
        set_servo_position(raise,count);
        msleep(15);
        count+=5;
    }
    ao();
    msleep(200);
}

void servoSlowLower(int initial, int final){
    int count = initial;
    while(count > final){
        set_servo_position(raise,count);
        msleep(15);
        count-=5;
    }
    ao();
    msleep(200);
}

// wall follow functions

void wallFollowleft() {
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
    msleep(1);
}

void wallFollowright() {
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
    msleep(1);
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
    msleep(1);
}


//Enables servos and does all the prep work 
void init(){
    create_connect();
    enable_servos();
    msleep(100);
    set_servo_position(raise, atUp);
    msleep(100);
    set_servo_position(turner, horizontal);
    msleep(100);
}

void getPipe2(){
    while (get_create_rcliff_amt() > black){  
        wallFollowright();
    }
    drive(200, 200, 200);
    while (get_create_rfcliff_amt() > black){  
        wallFollowright();
    }
    stop(400);
    
    drive(200, 200, 900);
    stop(100);
    drive(0, 200, 100);
    while(get_create_lcliff_amt() > black){
        drive(-200, -200, 1);
    }
    stop(100);
    while(get_create_rcliff_amt() > black){
        drive(0, -100, 1);
    }
    stop(100);

    msleep(100); // added during cleanup 
    set_servo_position(raise,atUp);
    msleep(400);

    set_servo_position(turner, horizontal);
    msleep(400);
    drive(-200, 0, pivot);
    stop(300);
    msleep(100); // added during cleanup
    set_servo_position(raise,atLevel);
    msleep(400);
    while(!(digital(push))){
        drive(200, 200, 1);
    }
    stop(200);
    msleep(100); // added during cleanup
    servoSlowRaise(atLevel, atUp);
    msleep(200);
    while(get_create_lcliff_amt() > black){
        drive(-200, -200, 1);
    }
    stop(100);
    while(get_create_rcliff_amt() > black){
        drive(0, -200, 1);
    }

    stop(100);
}

// Starting Position:
// Function: 
// Ends: 
void putSecondPipeOn(){
	drive(200, 200, forward2);
    stop(300);
    drive(0, 200, 500);
    stop(300);
    servoSlowLower(atUp,atPipe);
    msleep(200);
    stop(300);
    set_servo_position(turner,vertical);
    msleep(200);
    stop(300);
    drive(200, -200, 300);
	stop(300);
    drive(200, 0, 200);
}
void getWashers(){
    create_drive_direct(-200,200);
    msleep(semi);
    create_drive_direct(0,0);
    msleep(100);
    create_drive_direct(-200,-200);
    msleep(200);
    create_drive_direct(0,0);
    msleep(100);
    mav(0,700);
    msleep(800);
    mav(0,1);
    msleep(100);
    create_drive_direct(-200,-200);
    msleep(1370);
    create_drive_direct(0,0);
    msleep(500);
    mav(0,-700);
    msleep(800);
    mav(0,1);
    msleep(100);

    create_drive_direct(200,205);
    msleep(1900);
    create_drive_direct(0,0);
    msleep(100);
    mav(0,700);
    msleep(800);
    mav(0,1);
    msleep(100);
	create_drive_direct(200,220);
    msleep(1350);
    create_drive_direct(0,0);
    msleep(500);
    mav(0,-700);
    msleep(800);
    mav(0,1);
    msleep(100);
    
    create_drive_direct(-200, -200);
    msleep(1200);
    create_drive_direct(0,0);
    msleep(100);
    create_drive_direct(0,200);
    msleep(300);
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
}

// Starting Position:
// Function: 
// Ends: 

int main(){
	init();
	getPipe2();
	getWashers();
    putSecondPipeOn();
    return 0;
}
