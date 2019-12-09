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
const int black = 1500;
const int pivot = 280;
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
const int atPipe = 600;
const int atUp = 1600;
const int atStart = 2000;

// The tire claw consts
const int raise = 0; // The servo that raises the tireclaw
const int turner = 1; // The servo that rotates the tireclaw
const int push = 9; // The pushButton that detects the pipe

const int ninety = 1000;
const int semi = 2000;

const int forward = 530;
const int pivot2 = 320;
const int forward2 = 60;

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
        msleep(10);
        count+=5;
    }
    ao();
    msleep(100);
}

void servoSlowLower(int initial, int final){
    int count = initial;
    while(count > final){
        set_servo_position(raise,count);
        msleep(10);
        count-=5;
    }
    ao();
    msleep(100);
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
    set_servo_position(raise, atStart);
    msleep(100);
    set_servo_position(turner, horizontal);
    msleep(100);
}

void cleanUp(){
    disable_servos();
    create_stop(); 
    create_disconnect();
}


void starter(){
    printf("Team 0160 Create Robot\n");
    printf("Walaby Battery = %f\n",power_level());
    printf("Create Battery = %d\n", get_create_battery_capacity());
    //Set up for start
    printf(" \n");
    printf("Press A Button to Light Start\n");
    printf("Press B Button to Bypass\n");
    printf("Press C Button to Quit\n");
    while (TRUE) {
        if (a_button()==1) {  // A Button for light start
            printf("Waiting for start light\n");
            wait_for_light(start);
            break;
        }
        if (b_button()==1) {  // B Button to bypass light start
            break;
        }
        if (c_button()==1) {  // c Button to quit
            cleanUp();
            exit(0);
        }
    }
    shut_down_in(119); // Shut down before two minutes
    //wtf   msleep(1000); //Let other robot start
}


// Starting Position:
// Function: 
// Ends: 

void posForPickup(){
    create_drive_direct(200, 200);
    msleep(600);
    while (get_create_lfcliff_amt() > black){
        wallFollowleft();
        msleep(1);
    }  
    double t = seconds()+1.7;
    while (seconds()<t){ 
        wallFollowleft();
        msleep(1);
    }
    set_servo_position(raise,atUp);
    create_drive_direct(-100, -100);
    msleep(900);

    //Get onto the vertical black line
    while (get_create_lfcliff_amt() > black){
        create_drive_direct(200, -200);
        msleep(1);
    }
    msleep(10); 
    //Get onto the vertical black line   

    //Get to the wall where the cylinder is
    while (!get_create_lbump() && !get_create_rbump()){
        if(get_create_lfcliff_amt() < black &&  get_create_rfcliff_amt() > black)
        { 
            drive(150, 180, 1);
        }
        else if (get_create_lfcliff_amt() > black && get_create_rfcliff_amt() < black)
        {
            drive(200, 150, 1);
        }
        else
        {
            drive(100, 100, 1);
        }
    }
    msleep(10);

    //Back up to set up for picking up the cylinder
    t = seconds()+2.2;
    while (seconds()<t){ 
        if(get_create_lfcliff_amt() < black &&  get_create_rfcliff_amt() > black)
        { 
            drive(-100, -75, 1);
        }
        else if (get_create_lfcliff_amt() > black && get_create_rfcliff_amt() < black)
        {
            drive(-75, -100, 1);
        }
        else
        {
            drive(-100, -100, 1);
        }
    }
    stop(300);
}

// Starting Position:
// Function: 
// Ends: 

void pickUpPipe(){
	//Bring down the arm until the lever switch
    servoSlowLower(atUp,atLevel);
    msleep(300);
    //Pick up and lift out the cylinder backing up a bit
    while (!(digital(push))){
        if(get_create_lfcliff_amt() < black &&  get_create_rfcliff_amt() > black)
        { 
            drive(70, 100, 1);
        }
        else if (get_create_lfcliff_amt() > black && get_create_rfcliff_amt() < black)
        {
            drive(100, 70, 1);
        }
        else
        {
            drive(100, 100, 1);
        }
    }
    stop(400);
    ao();
    msleep(100);
    servoSlowRaise(atLevel,atUp);
    drive(-150, -150, 150);
}

// Starting Position:
// Function: 
// Ends: 

void moveToPipeZone(){
    //Turn onto the black line
    turn(180, right, -60); 
    stop(200);


    //LineFollow while the roomba has not hit the wall
    while (!get_create_lbump() && !get_create_rbump()){
        if( (get_create_lfcliff_amt() < black) &&  get_create_rfcliff_amt() > black)
        { 
            drive(100, 200, 1);
        }
        else if ((get_create_lfcliff_amt() > black) && get_create_rfcliff_amt() < black)
        {
            drive(180, 100, 1);
        }
        else
        {
            drive(120, 100, 1);
        }
    }
    ao();
    //Back up a bit and turn to set up the wallfollow owo
    drive(-200, 200, 1000);
    create_drive_direct(0,0);
    msleep(200);
    double t = seconds()+1;
    while (seconds()<t){ 
        wallFollowright();
    }
	 //Wallfollow until we get to the right corner box owo
    while (get_create_rcliff_amt() > black){
        wallFollowright();
    }
    drive(200, 200, 200);
    while (get_create_rcliff_amt() > black){  
        wallFollowright();
    }
    drive(200, 200, 200);

    while (get_create_rfcliff_amt() > black){
        wallFollowright();
    }
	drive(200, 200, forwardbl);
    stop(200);
    turn(90, left, 0);
	stop(200);
	ao();
}

// Starting Position:
// Function: 
// Ends: 

void putFirstPipeOn(){

	stop(1000);
	drive(200, 200, forward);
    stop(1300);
	ao();
	servoSlowLower(atUp,atPipe);
	msleep(200);
  	stop(100);
	ao();
	msleep(100);
	set_servo_position(turner, vertical);
	msleep(200);
	ao();
	msleep(100);
    turn(180, left, 30); 
	stop(1000);
    drive(-250, -250, 700);
}

// Starting Position:
// Function: 
// Ends: 

void alignForPipe2(){
	drive(-250, -250, 700);
    msleep(100); //line added during cleanup 
	set_servo_position(raise, atUp);
	msleep(200);
    turn(180, left, 0);
    stop(500);
	drive(-250, -250, 900);
    stop(100);
    turn(90, right, 0);
    stop(500);

	while (!get_create_lbump() && !get_create_rbump()){
    	drive(200, 200, 1);
	} 
	stop(200);
    turn(90, left, 0);
    stop(500);
   	drive(-150, -150, 2700);
    drive(200, 0, 300);
    while(!get_create_rbump()){
        drive(100, 100, 1);
    }
    drive(-200, 0, 400);
    stop(100);
    drive(-150, -150, 3200);
}

// Starting Position:
// Function: Follows the left wall, aligns, then picks up the pipe
// Ends: Aligned with the wall 
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
    servoSlowLower(atUp,atLevel);
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

void getWashers(){
    create_drive_direct(-200,200);
    msleep(semi);
    create_drive_direct(0,0);
    msleep(100);
    create_drive_direct(-200,-200);
    msleep(150);
    create_drive_direct(0,0);
    msleep(100);
    mav(0,750);
    msleep(800);
    mav(0,1);
    msleep(100);
    create_drive_direct(-200,-200);
    msleep(700);
    create_drive_direct(0,0);
    msleep(100);
    mav(0,750);
    msleep(75);
    mav(0,1);
    msleep(100);
    create_drive_direct(-200,-200);
    msleep(550);
    create_drive_direct(0,0);
    msleep(500);
    create_drive_direct(200,200);
    msleep(300);
    mav(0,-750);
    msleep(900);
    mav(0,1);
    msleep(100);

    create_drive_direct(200,205);
    msleep(1200);
    create_drive_direct(0,0);
    msleep(100);
    //mav(0,750);
    msleep(800);
    //mav(0,1);
    msleep(100);
	create_drive_direct(200,220);
    msleep(1100);
    create_drive_direct(0,0);
    msleep(500);
    //mav(0,-750);
    msleep(800);
    //mav(0,1);
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

void putSecondPipeOn(){
	drive(200, 200, forward2);
    stop(300);
    drive(0, 200, 500);
    stop(300);
    servoSlowLower(atUp,(atPipe+5));
    msleep(200);
    stop(300);
    set_servo_position(turner,vertical);
    msleep(200);
    stop(300);
    drive(200, -200, 500);
	stop(300);
    drive(200, 0, 200);
}


// Runs the other functions in tandem
int main() {
    init();
    starter();
    posForPickup();
	pickUpPipe();
	moveToPipeZone();
    putFirstPipeOn();
    alignForPipe2();
	getPipe2();
	getWashers();
	putSecondPipeOn();
    cleanUp();
    return(0);
}