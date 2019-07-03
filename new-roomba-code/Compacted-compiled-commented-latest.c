#include <kipr/botball.h>
/* Issues:
/       The start function doesn't compile
/       The code is LACKING comments, Remember Zain has to understand what the code is doing
/       Changing the constant names to be more descriptive wouldn't hurt
/       Checklist doesn't exist and very much needs to
/       * add a variable for the washerclaw's port
/       * cleanup the variables and comment them
/       * make the servo start lower in the starting box
/       * other shit i cant remember because its two am
*/

const int TRUE = 1;
const int black = 2000;
const int pivot = 250;
const int forwardbl = 450;

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

const int atLevel = 260;
const int atPipe = 625;
const int atUp = 1600;

// The tire claw consts
const int raise = 0; // The servo that raises the tireclaw
const int turner = 1; // The servo that rotates the tireclaw
const int push = 9; // The pushButton that detects the pipe

const int ninety = 930;
const int semi = 1860;

const int forward = 560;
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
        msleep(ninety + adjustment);
    }
    else if(degree == 180){
        create_drive_direct(200 * (direction), -200 * (direction));
        msleep(semi + adjustment);
    }
    else{
        printf("Angle not Defined??");
        //exit();
    }
}

/*
// Gyroscope package




// Turning defined with gyroscope

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
// make this lower so it fits in the starting box
    set_servo_position(raise, atUp);
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
            cleanUp();
            exit(0);
        }
    }
    shut_down_in(118); // Shut down before two minutes
// msleep(1000); //Let other robot start : Now that i look at it, doesn't this robot start first
}


// Starting Position:
// Function: 
// Ends: 

void posForPickup(){
    // drive forward past the starting box
    drive(200, 200, 600);
    // drive until black line
    while (get_create_lfcliff_amt() > black){
        wallFollowleft();
    }
    // go forward to push the yellow and blue cube out of the way   
    double t = seconds()+1.7;
    while (seconds()<t){ 
        wallFollowleft();
    }
    // reposition to follow the line
    drive(-100, -100, 900);

    // rotate clockwise and align with the black line
    while (get_create_lfcliff_amt() > black){
        drive(200, -200, 1);
    }
    msleep(10);

    // follow the wall until both bump sensors are depressed 
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

    // back up to set up for picking up the cylinder
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
	
    //Bring down the arm 
    set_servo_position(raise, atLevel);
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
    
    // raise the servo
    servoSlowRaise(atLevel, atUp);
    // back out a little
    drive(-150, -150, 150);
}

// Starting Position:
// Function: 
// Ends: 

void moveToPipeZone(){

    //Turn onto the black line
    turn(180, right, -60); 
    stop(200);


    // lineFollow until the roomba hits the wall
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

    // turn to prepare to wall follow
    drive(-200, 200, 1000);

	// wallfollow until we get to the right corner box 
    
    /* For loop to replace this code?
    for(int i = 0, i < 2, ++i){
        while (get_create_rfcliff_amt() > black){
            wallFollowright();
        }
        drive(200, 200, 200);
    }
    while (get_create_rfcliff_amt() > black){
        wallFollowright();
    }
    drive(200, 200, forwardbl);

    */
    // actually now that i look at this its really dumb
    // reminder to flex finding a use for a for loop to lennard

    // skip line one
    while (get_create_rfcliff_amt() > black){
        wallFollowright();
    }
    drive(200, 200, 200);

    // skip line two
    while (get_create_rfcliff_amt() > black){  
        wallFollowright();
    }
    drive(200, 200, 200);

    // locate the line in the right corner
    while (get_create_rfcliff_amt() > black){
        wallFollowright();
    }
	drive(200, 200, forwardbl);
    stop(200);

    // turn to face away from the final pipe location
    turn(90, left, 0);
	stop(200);
	ao();
}

// Starting Position:
// Function: 
// Ends: 

void putFirstPipeOn(){

	stop(1000);

    // drive forward a set distance so the orange pipe fits cleanly on
	drive(200, 200, forward);
    stop(1300);
	ao();

    // lower the pipe
	servoSlowLower(atUp,atPipe);
	msleep(200);
  	stop(100);
	ao();
	msleep(100);
	
    // turn the pipe 
    set_servo_position(turner, vertical);
	msleep(200);
	ao();
	msleep(100);

    // rotate and place the pipe on
    turn(180, left, 0); 
	stop(1000);

    // back up leaving the pipe 
    drive(-250, -250, 700);
}

// Starting Position:
// Function: 
// Ends: 

void alignForPipe2(){

// am i autistic or is this line a duplicate?
// maybe just combine the msleep between the two
// Good readability???
	drive(-250, -250, 700);

    // msleeps for safety 
    // raise the tireclaw so its out of the way
    msleep(100); //line added during cleanup 
	set_servo_position(raise, atUp);
	msleep(200);
    
// alignment code i cant understand at 12:10
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
    drive(200, 0, 200);
    while(!get_create_rbump()){
        drive(100, 100, 1);
    }
    drive(-200, 0, 200);
    stop(100);
    drive(-150, -150, 3200);
// end of alighment code i cant understand at 12:10
}

// Starting Position:
// Function: Follows the left wall, aligns, then picks up the pipe
// Ends: Aligned with the wall 

void getPipe2(){
    
    // skip the first black line
    while (get_create_rcliff_amt() > black){  
        secondWallFollowright();
    }
    drive(200, 200, 200);
    
    // find the second black line while wall following
    while (get_create_rfcliff_amt() > black){  
        secondWallFollowright();
    }
    stop(400);
    
    // drive forward a bit
    drive(200, 200, 900);
    stop(100);

    // pivot a tad
    drive(0, 200, 100);
    
    // backup to the black line 
    while(get_create_lcliff_amt() > black){
        drive(-200, -200, 1);
    }
    stop(100);

    // finish aligning
    while(get_create_rcliff_amt() > black){
        drive(0, -100, 1);
    }
    stop(100);

// wait the servo is already up
// lennard you are legitimatly smacked
// you idiot read your own fucking code
// you are a big monkey

    msleep(100); // added during cleanup 
    set_servo_position(raise,atUp);
    msleep(400);

    // i really have no idea what this is doing 
    // rotate the tire claw ??
    set_servo_position(turner, horizontal);
    msleep(400);

    // position to drive straight at the pipe 
    drive(-200, 0, pivot);
    stop(300);
    
    // position the tireclaw to grab the claw
    set_servo_position(raise,atLevel);
    msleep(400);

    // drive till the push button gets hit
    while(!(digital(push))){
        drive(200, 200, 1);
    }
    stop(200);

    // raise the claw up with pipe in tow
    servoSlowRaise(atLevel, atUp);
    msleep(200);

    // back up from the pipe
    while(get_create_lcliff_amt() > black){
        drive(-200, -200, 1);
    }
    stop(100);

    // re-align with the black line
    while(get_create_rcliff_amt() > black){
        drive(0, -200, 1);
    }

    stop(100);
}

// Starting Position:
// Function: 
// Ends: 

void getWashers(){

// FIX THE HARD CODED MOTOR PORT

    
    // turn around
    turn(180, left, 0);
    stop(100);

    // ensure the washer motor is at its lowest postition
    mav(0,700);
    msleep(800);
    
    // ensure the washer claw is pushing against the pvc pipe
    mav(0,1); // FIX THIS ACTUAL HARD CODE!!!!!!!!
// is the 1 to keep current flowing? Guiermo asks
// Sorry for butchering your name
    msleep(100);
	
    // backup pushing the washers to the magnite
    drive(-200, -200, 1280);
    stop(100);

    // bring the washer claw down
    mav(0,-700);
    msleep(800);
// make this 1 below negative? i think that makes sense, you make that call lennard
    mav(0,1);
    msleep(100);

    //drive forward a past the middle pvc pipe
    drive(200, 205, 1800);
    stop(100);

    // put the washer claw up 
    mav(0,700);
    msleep(800);

// keep the current flowing ?
    mav(0,1);
    msleep(100);
	
    // drive forward pushing the washer to the magnet
    drive(200, 220, 1290);
    stop(100);

    //bring the washer claw down
    mav(0,-700);
    msleep(800);
// keep current flowing ?
    mav(0,1);
    msleep(100);
    
    // backup 
    drive(-200, -200, 1200);
    stop(100);

// what the actual fuck does this do?
    drive(0, 200, 300);
    stop(100);

    // align on the black line
    while (get_create_rcliff_amt() > black){
        drive(200, 200, 1);
    }
    stop(100);
    while (get_create_lcliff_amt() > black){
        drive(200, 0, 1);
    }
    stop(100);
}

// Starting Position:
// Function: 
// Ends: 

void putSecondPipeOn(){
	
    // drive forward a hardcoded amount
    drive(200, 200, forward2);
    stop(300);

    // pivot a hardcoded amount
    drive(0, 200, 500);
    stop(300);
    
    // put the servo down
    servoSlowLower(atUp,atPipe);
    msleep(200);
    stop(300);
    
    // turn the tire claw
    set_servo_position(turner,vertical);
    msleep(200);
    stop(300);
    
    // turn in order to put the pipe on
    drive(200, -200, 300);
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
