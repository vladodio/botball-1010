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
const int pivot = 300;
const int forwardbl = 400;

//Create sensors
const int lCliff = 1;
const int rCliff = 2;
const int lfCliff = 3;
const int rfCliff = 4;

//Wallaby sensors
const int touch = 0; // touch sensor in grabber
const int start = 0; // light sensor for starting

int go = 0;
int current = 0;

const int wire = 3; // motor to repair comm wire
const int atWire = 800;

const int horizontal = 1683;
const int vertical = 520;

const int atLevel = 240;
const int atPipe = 625;
const int atUp = 1600;

// The tire claw consts
    const int raise = 0; // The servo that raises the tireclaw
    const int turn = 1; // The servo that rotates the tireclaw
    const int push = 9; // The pushButton that detects the pipe

//const int ninety = 980;
//const int semi = 2020;

const int forward = 580;
const int pivot2 = 320;
const int forward2 = 228;

double bias;
double degToticks180 = 6290;
double degToticks90  = 6000;

// Functions

void calibrate_gyro()
{
   	//takes the average of 50 readings
    int i = 0;
    double avg = 0;
    while(i < 50)
    {
        avg += gyro_z();
        msleep(1);
        i++;
    }
    bias = avg / 50.0;
    printf("New Bias: %f\n", bias);//prints out your bias. COMMENT THIS LINE OUT IF YOU DON'T WANT BIAS READINGS PRINTED OUT
}

//the same as calibrate_gyro() except faster to type
void cg()
{
    calibrate_gyro();
}

//default right
void ninety(int direction)
{
    double theta = 0;//declares the variable that stores the current degrees
    create_drive_direct(200 * (direction) , 200 * (-direction));//starts the motors

    //keeps the motors running until the robot reaches the desired angle
    while(theta < (tickTodegs90 * 90))
    {
        msleep(10);//turns for .01 seconds
        theta += abs(gyro_z() - bias) * 10;//theta = omega(angular velocity, the value returned by gyroscopes) * time
    }
    //stops the motors after reaching the turn
    create_drive_direct(0, 0);
}

//pos value == right
void semi(int direction)
{
    double theta = 0;//declares the variable that stores the current degrees
    create_drive_direct(200 * (direction) , 200 * (-direction));//starts the motors

    //keeps the motors running until the robot reaches the desired angle
    while(theta < (tickTodegs180 * 90))
    {
        msleep(10);//turns for .01 seconds
        theta += abs(gyro_z() - bias) * 10;//theta = omega(angular velocity, the value returned by gyroscopes) * time
    }
    //stops the motors after reaching the turn
    create_drive_direct(0, 0);
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
void servoSlowLower(int initial, int final){
    int count = initial;
    while(count > final){
        set_servo_position(raise,count);
        msleep(30);
        count-=5;
    }
    ao();
    msleep(200);
}
void lineFollow (int time) {
    int t = seconds()+time;
    while (seconds()<t){ 
        if( (get_create_lfcliff_amt() < black) &&  get_create_rfcliff_amt() > black)
        { 
            create_drive_direct(100, 300);
            msleep(5);
        }
        else if ((get_create_lfcliff_amt() > black) && get_create_rfcliff_amt() < black)
        {
            create_drive_direct(300, 100);
            msleep(5);
        }
        else
        {
            create_drive_direct(100, 100);
            msleep(5);
        }
    }
}

void moveToBump() {
    while((get_create_lbump() == 0) || (get_create_rbump() == 0)){
        create_drive_direct(100, 100);
    }
}

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
}

void singlelineright(double time) {
    double t = seconds()+time;
    while (seconds()<t){ 
        if(get_create_rfcliff_amt() < black)
        { 
            create_drive_direct(200, 100);
            msleep(1);
        }
        else{
            create_drive_direct(100, 200);
            msleep(1);
        }
    }
}

/*
void start(){
    printf("Team 0160 Create Robot\n");
    create_connect();
    create_full();
    printf("Walaby Battery = %f\n",power_level());
    printf("Create Battery = %d\n", get_create_battery_capacity());
    //Set up for start
    enable_servos();
    msleep(100);
    set_servo_position(raise, atUp);
    msleep(500);
    set_servo_position(turn, horizontal);
    msleep(200);
    printf(" \n");
    printf("Press A Button to Light Start\n");
    printf("Press B Button to Bypass\n");
    printf("Press C Button to Quit\n");
    while (TRUE) {
        if (a_button()==1) {  // A Button for light start
            printf("Waiting for start light\n");
            go=analog(start)/2;
            while (TRUE) {
                current = analog(start);
                if (current<go) {
                    printf("Current=%d, Start=%d\n",current, go);
                    break;
                }
            }
            break;
        }
        if (b_button()==1) {  // B Button to bypass light start
            break;
        }
        if (c_button()==1) {  // c Button to quit
            disable_servos();            
            camera_close();
            create_stop(); 
            create_disconnect();
            return(0);
        }
    }
    shut_down_in(118); // Shut down before two minutes
    msleep(1000); //Let other robot start
}
*/

//Enables servos and does all the prep work 
void init(){
	create_connect();
	enable_servos();
	msleep(100);
    set_servo_position(raise, atUp);
    msleep(100);
    set_servo_position(turn, horizontal);
    msleep(100);
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

    create_drive_direct(-100, -100);
    msleep(900);

    //Get onto the vertical black line
    while (get_create_lfcliff_amt() > black){
        create_drive_direct(200, -200);
        msleep(1);
    }
    msleep(10);      

    //Get to the wall where the cylinder is
    while (!get_create_lbump() && !get_create_rbump()){
        if(get_create_lfcliff_amt() < black &&  get_create_rfcliff_amt() > black)
        { 
            create_drive_direct(150, 180);
            msleep(1);
        }
        else if (get_create_lfcliff_amt() > black && get_create_rfcliff_amt() < black)
        {
            create_drive_direct(200, 150);
            msleep(1);
        }
        else
        {
            create_drive_direct(100, 100);
            msleep(1);
        }
    }
    msleep(10);

    //Back up to set up for picking up the cylinder
    t = seconds()+2.2;
    while (seconds()<t){ 
        if(get_create_lfcliff_amt() < black &&  get_create_rfcliff_amt() > black)
        { 
            create_drive_direct(-100, -75);
            msleep(1);
        }
        else if (get_create_lfcliff_amt() > black && get_create_rfcliff_amt() < black)
        {
            create_drive_direct(-75, -100);
            msleep(1);
        }
        else
        {
            create_drive_direct(-100, -100);
            msleep(1);
        }
    }
    create_drive_direct(0, 0);
    msleep(300);
}

// Starting Position:
// Function: 
// Ends: 

void pickUpPipe(){
	//Bring down the arm until the lever switch
    set_servo_position(raise, atLevel);
    msleep(300);
    //Pick up and lift out the cylinder backing up a bit
    while (!(digital(push))){
        if(get_create_lfcliff_amt() < black &&  get_create_rfcliff_amt() > black)
        { 
            create_drive_direct(70, 100);
            msleep(1);
        }
        else if (get_create_lfcliff_amt() > black && get_create_rfcliff_amt() < black)
        {
            create_drive_direct(100, 70);
            msleep(1);
        }
        else
        {
            create_drive_direct(100, 100);
            msleep(1);
        }
    }
    create_drive_direct(0,0);
    msleep(400);
    ao();
    msleep(100);
    servoSlowRaise(atLevel,atUp);
    create_drive_direct(-150,-150);
    msleep(150);

}

// Starting Position:
// Function: 
// Ends: 

void moveToPipeZone(){
    //Turn onto the black line 
    create_drive_direct(200, -200);
    msleep(1800);
    create_stop();
    msleep(200);


    //LineFollow while the roomba has not hit the wall
    while (!get_create_lbump() && !get_create_rbump()){
        if( (get_create_lfcliff_amt() < black) &&  get_create_rfcliff_amt() > black)
        { 
            create_drive_direct(100, 200);
            msleep(1);
        }
        else if ((get_create_lfcliff_amt() > black) && get_create_rfcliff_amt() < black)
        {
            create_drive_direct(180, 100);
            msleep(1);
        }
        else
        {
            create_drive_direct(120, 100);
            msleep(1);
        }
    }
    ao();
    //Back up a bit and turn to set up the wallfollow owo
    create_drive_direct(-200, 200);
    msleep(1000);
	 //Wallfollow until we get to the right corner box owo
    while (get_create_rfcliff_amt() > black){
        wallFollowright();
        msleep(1);
    }
    create_drive_direct(200,200);
    msleep(200);
    while (get_create_rfcliff_amt() > black){  
        wallFollowright();
        msleep(1);
    }
    create_drive_direct(200,200);
    msleep(200);

    while (get_create_rfcliff_amt() > black){
        wallFollowright();
        msleep(1);
    }
	create_drive_direct(200,200);
    msleep(forwardbl);
    create_drive_direct(0,0);
    msleep(200);
	create_drive_direct(-200,200);
	msleep(ninety);
    create_drive_direct(0,0);
    msleep(200);
	ao();
}

// Starting Position:
// Function: 
// Ends: 

void putFirstPipeOn(){
	create_drive_direct(0,0); 
	msleep(1000);
	create_drive_direct(200,200);
	msleep(forward);
    create_drive_direct(0,0);
    msleep(100);
	ao();
	msleep(200);
	create_drive_direct(0,0); 
	msleep(1000);
	servoSlowLower(atUp,atPipe);
	msleep(200);
  	create_drive_direct(0,0);
    msleep(100);
	ao();
	msleep(100);
	set_servo_position(turn, vertical);
	msleep(200);
	ao();
	msleep(100);
    semi(-1);
	create_drive_direct(0,0); 
	msleep(1000);
    create_drive_direct(-250,-250);
	msleep(700);
}

// Starting Position:
// Function: 
// Ends: 

void alignForPipe2(){
	create_drive_direct(-250,-250);
	msleep(700);
	set_servo_position(raise, atUp);
	msleep(200);
    semi(-1);
    create_drive_direct(0,0);
    msleep(100);
	create_drive_direct(-250,-250);
	msleep(900);
    create_drive_direct(0,0);
    msleep(100);
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
    msleep(2700);
    create_drive_direct(0,0);
    msleep(100);
}


// Starting Position:
// Function: Follows the left wall, aligns, then picks up the pipe
// Ends: Aligned with the wall 
void getPipe2(){
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
    msleep(400);
    
    create_drive_direct(200,200);
    msleep(400);
    create_drive_direct(0,0);
    msleep(100);
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

// Starting Position:
// Function: 
// Ends: 

void getWashers(){
	semi(-1);
    create_drive_direct(0,0);
    msleep(100);
    mav(0,700);
    msleep(800);
    mav(0,1);
    msleep(100);
	create_drive_direct(-200,-200);
    msleep(1280);
    create_drive_direct(0,0);
    msleep(100);
    mav(0,-700);
    msleep(800);
    mav(0,1);
    msleep(100);

    create_drive_direct(200,200);
    msleep(1800);
    create_drive_direct(0,0);
    msleep(100);
    mav(0,700);
    msleep(800);
    mav(0,1);
    msleep(100);
	create_drive_direct(200,200);
    msleep(1270);
    create_drive_direct(0,0);
    msleep(100);
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

void putSecondPipeOn(){
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

void cleanUp(){
    disable_servos();
    create_stop(); 
    create_disconnect();
}


// Runs the other functions in tandem
int main() {
    //start()
    init();
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
