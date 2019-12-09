/*CHECKLIST
 Check battery
 Check sensors are plugged in correctly - motors red/black facing the right way
 Check back top hats are tightened in
 Check claw is tightened and a tiny bit raised
 Check coins and battery are secure
 Make sure red pawns are in the middle of the line and out far enough
 Camera can see correctly (pushed down)
 Top metal stick screwed in tight
 Check legos are secure
 
 AGENDA
 check left and right hospitals by commenting out code
 possibly try switching wallabe b/c battery is shit
*/

#include <kipr/botball.h>
#include <stdbool.h>

//motor and sensor ports
const int Rmotor = 1;
const int Lmotor = 0;
const int power = 1470;
const int powerL = 1500; //power for left motor
const int topHatF = 2; //right front sensor
const int topHatF2 = 5;
const int topHatR = 1; //right
const int topHatL = 0; //left
const int people = 0;
const int green = 1;
const int topClaw = 0;
const int botClaw = 2;
const int frontB = 9;
const int ambulance = 3;
const int xPos1 = 80;
const int xPos2 = 75;
const int xPos3 = 75;

//constants
const int line = 1500;
const int grayline = 1500;
const double tickdegl = 15;
const double tickdegr = 15.5;

//claws
const int topOpen = 10;
const int botOpen = 300;
const int topClose = 992;
const int botClose = 1200;
const int ambuDown = 1800;
const int ambuUp = 1300;

//////////////////////// FUNCTIONS
//turning------------------------
void left (int degree, int speed) { //left with both wheels
    double ticks = degree * tickdegl;
    int d = gmpc(Rmotor);
    mav(Lmotor, -speed);
    mav(Rmotor, speed);
    while (gmpc(Rmotor)-d < ticks) {
        msleep(10);
    }
    ao();
}
void leftone (int degree, int speed) { //move left wheel back
    double ticks = degree * tickdegl * 2;
    int d = gmpc(Lmotor);
    mav(Lmotor, -speed);
    while (d-gmpc(Lmotor) < ticks) {
        msleep(10);
    }
    ao();
}
void leftone2 (int degree, int speed) { //move left wheel forward
    double ticks = degree * tickdegl * 2;
    int d = gmpc(Lmotor);
    mav(Lmotor, speed);
    while (gmpc(Lmotor)-d < ticks) {
        msleep(10);
    }
    ao();
}
void right (int degree, int speed) { //right with both wheels
    double ticks = degree * tickdegr;
    int d = gmpc(Lmotor);
    mav(Lmotor, speed);
    mav(Rmotor, -speed);
    while (gmpc(Lmotor)-d < ticks) {
        msleep(10);
    }
    ao();
}
void rightone (int degree, int speed) { //move right wheel back
    double ticks = degree * tickdegr * 2;
    int d = gmpc(Rmotor);
    mav(Rmotor, -speed);
    while (d-gmpc(Rmotor) < ticks) {
        msleep(10);
    }
    ao();
}
void rightone2 (int degree, int speed) { //move right wheel forward
    double ticks = degree * tickdegr * 2;
    int d = gmpc(Rmotor);
    mav(Rmotor, speed);
    while (gmpc(Rmotor)-d < ticks) {
        msleep(10);
    }
    ao();
}

//moving------------------------
void passWhite(){ //go to black
    while (analog(topHatL) < line || analog(topHatR) < line){
        mav(Rmotor, power);
        mav(Lmotor, powerL);
        msleep(5);
    }
}
void passBlack(){ //go to white
    while (analog(topHatL) > line || analog(topHatR) > line){
        mav(Rmotor, power);
        mav(Lmotor, powerL);
        msleep(5);
    }
}
void timeFollow(double z){
double t = seconds() + z;
    while(seconds() < t){
        if(analog(topHatF) > line){
            mav(Lmotor, 1300);
            mav(Rmotor, 800);
            msleep(1);
        }
        else {
            mav(Lmotor, 800);
            mav(Rmotor, 1300);
            msleep(1);
        }
    }
}

//this thing------------------------
int getPawn(int xpos){
    int x;
	
	//error check
    timeFollow(1);
	
    //Line follow until sees green
    camera_update();
   	while(get_object_count(green) == 0) { 
        if(analog(topHatF) > line){
            mav(Lmotor, 1300);
            mav(Rmotor, 800);
            msleep(1);
        }
        else {
            mav(Lmotor, 800);
            mav(Rmotor, 1300);
            msleep(1);
        }
        camera_update();
        if(analog(topHatF2) > line) return 0; //check for screw up
    }
  
    //Aligns (centers) robot to red pawn
    x = get_object_center_x(people, 0);
    camera_update();
    while (x <= xpos || x > xpos + 10) {
         if(analog(topHatF) > line){
            mav(Lmotor, 1300);
            mav(Rmotor, 800);
            msleep(1);
        }
        else {
            mav(Lmotor, 800);
            mav(Rmotor, 1300);
            msleep(1);
        }
        x = get_object_center_x(people, 0);
        camera_update();
        if(analog(topHatF2) > line) return 0;
    }
	ao();
    msleep(100);
    
    if(analog(topHatF2) > line) return 0; //check again
	
    //turns to set up and opens claws
    rightone(90, power);
    msleep(500);

    set_servo_position(topClaw, topOpen);
    msleep(400);
    set_servo_position(botClaw, botOpen);
    msleep(400);

    //Align to gray line
    while(analog(topHatR) < grayline) {
        mav(Lmotor, 0);
        mav(Rmotor, 300);
        msleep(1);
    }
    mav(Rmotor, -200);
    msleep(350);
    while (analog(topHatL) < grayline) {
        mav(Lmotor, 300);
        mav(Rmotor, 0);
        msleep(1);
    }
    
    //move forward and check button
    double t = seconds() + 2.5;
    while(seconds() < t){
        if(digital(frontB)) {
    		mav(Lmotor, -powerL);
    		mav(Rmotor, -power);
    		msleep(500);
            mav(Lmotor, -500);
    		mav(Rmotor, 0);
    		msleep(200);
            t += 1.1;
        } else {
    		mav(Lmotor, powerL);
    		mav(Rmotor, power);
    		msleep(10);
        }
    }
    ao();
    msleep(10);
    
	//close claws and back up
    set_servo_position(topClaw, topClose);
    msleep(500);
    set_servo_position(botClaw, botClose);
    msleep(500);
	
    while (analog(topHatL) < line || analog(topHatR) < line) {
        mav(Lmotor, -power);
        mav(Rmotor, -power);
        msleep(1);
    }
    mav(Lmotor, 1000);
    mav(Rmotor, 1000);
    msleep(250);
    while (analog(topHatF) < line) {
        mav(Lmotor, -500);
        mav(Rmotor, 0);
        msleep(1);
    }
    ao();
    msleep(10);
	
    return 0;
}

///////////////////////////////////////////////
///////////////////////////////////////////////
int main(){
    //setup and check
    enable_servos();
    set_servo_position(topClaw, topClose); 
    msleep(500);
	set_servo_position(botClaw, botClose);
	msleep(500);
	//set_servo_position(ambulance,ambuDown);
    //msleep(500);
   
   
	mav(Lmotor, 1000);
    mav(Rmotor, 1000);
    msleep(1000);
	ao();
	msleep(1000);
    mav(Lmotor, -1000);
    mav(Rmotor, -1000);
    msleep(500);
	ao();
	msleep(1000);
	
    //START
    wait_for_light(3);
    shut_down_in(119);
    msleep(500); //wait for other bot
	
    //set_servo_position(ambulance,ambuUp);
    //msleep(500);
	
    //move forward to avoid collision with wall
    mav(Lmotor, powerL);
    mav(Rmotor, power);
    msleep(1000);
    //turn right and move forward then turn back to go to center
    right(90, power);
    passWhite();
    passBlack();
    left(90, power);
    
    //go to center line
    while (analog(topHatF) < line) {
        mav(Lmotor, powerL);
        mav(Rmotor, power);
        msleep(1);
    }
    ao();
    msleep(10);
    
    //open so cubes fuck off
	set_servo_position(botClaw, botOpen);
	msleep(500);
	set_servo_position(botClaw, botClose);
	msleep(500);
    
    //move forward and backup to align
    mav(Lmotor, powerL);
    mav(Rmotor, power);
    msleep(1000);
    ao();
    msleep(1000);
    while (analog(topHatL) < line) {
        mav(Lmotor, -400);
        mav(Rmotor, -400);
        msleep(1);
    }
    while (analog(topHatR) < line) {
        mav(Lmotor, 0);
        mav(Rmotor, -200);
        msleep(1);
    }
	
    //turn left onto line
    while (analog(topHatF) < line) {
        mav(Lmotor, -800);
        mav(Rmotor, 0);
        msleep(1);
    }
    ao();
	msleep(10);
	
    //Opens camera
    camera_open_black();
    msleep(50);
	
    //Gets pawn thrice
    timeFollow(1);
    
    getPawn(xPos1);
    camera_close();
    msleep(100);
    camera_open_black();
    msleep(1000);
    getPawn(xPos2);
    camera_close();
    msleep(100);
    camera_open_black();
    msleep(1000);
    getPawn(xPos3);
    
    //line follow to left double black box
    while (analog(topHatF2) < line) {
        if(analog(topHatF) > line){
            mav(Lmotor, 1300);
            mav(Rmotor, 1000);
            msleep(1);
        }
        else{
            mav(Lmotor, 1000);
            mav(Rmotor, 1300);
            msleep(1);
        }
    }
    mav(Lmotor, -power);
    mav(Rmotor, -power);
    msleep(500);
    
    //turn to look for burning
    left(85, power);
	camera_close();
    msleep(100);
    camera_open_black();
    msleep(2000);
   
    int i = 0;
    for(i = 0; i < 50; i++){
    	camera_update();
    	msleep(1);
    	printf("is it burning?: %d\n", get_object_count(people));
	}
    
    //put pawns in zone
    if (get_object_count(people) > 0) {  //is burning
		//turn back to start and back up a bit
        right(85, power);
        msleep(500);
        mav(Lmotor, -powerL);
        mav(Rmotor, -power);
        msleep(500);
        ao();
        msleep(10);
		
		//turn right, back up to line
        leftone2(85, power);
        while(analog(topHatL) < line || analog(topHatR) < line){
        	mav(Lmotor, -800);
        	mav(Rmotor, -800);
        	msleep(10);
        }
        while(analog(topHatR) < line){
        	mav(Lmotor, 0);
        	mav(Rmotor, -300);
        	msleep(10);
        }
        while(analog(topHatL) < line){
        	mav(Lmotor, -300);
        	mav(Rmotor, 0);
        	msleep(10);
        }
        while(analog(topHatL) > line){
        	mav(Lmotor, 200);
        	mav(Rmotor, 0);
        	msleep(10);
        }
        while(analog(topHatR) > line){
        	mav(Lmotor, 0);
        	mav(Rmotor, 200);
        	msleep(10);
        }
        
        mav(Lmotor, powerL);
        mav(Rmotor, power);
        msleep(50);
		//turn left to line and do mini checks
        ao();
        msleep(10);
        while(analog(topHatF2) < line){
        	mav(Rmotor, 600);
            msleep(10);
    	}
        while(analog(topHatF2) > line){
        	mav(Rmotor, -600);
            msleep(10);
    	}
        ao();
        msleep(10);
        while(analog(topHatF) < line){
        	mav(Lmotor,300);
            msleep(10);
    	}
        ao();
        msleep(10);
		
		//back up to give room to open claw
        mav(Lmotor, -powerL);
        mav(Rmotor, -power);
        msleep(500);
        set_servo_position(botClaw, 400);
        msleep(500);
		
		//go in and make a turn to shake people out
        while (analog(topHatF2) < line){
            mav(Rmotor, power);
            mav(Lmotor, powerL);
            msleep(5);
    	}
        while (analog(topHatF2) > line){
            mav(Rmotor, power);
            mav(Lmotor, powerL);
            msleep(5);
        }
        ao();
        msleep(10);
        leftone(10, power);
        leftone2(20, power); 
        ao();
    } 
    ////////////not burning
    else { 
		//forward a bit and turn right to line and do mini checks 
        while(analog(topHatL) < line){
        	mav(Lmotor, powerL);
        	mav(Rmotor, power);
        	msleep(10);
        }
        mav(Lmotor, 500);
        mav(Rmotor, 500);
        msleep(100);
        while(analog(topHatL) > 2500){
        	mav(Lmotor, powerL);
        	mav(Rmotor, power);
        	msleep(10);
        }
        ao();
        msleep(1000);
        while(analog(topHatR) < 2500){
        	mav(Lmotor, 0);
        	mav(Rmotor, -500);
        	msleep(10);
        }
        mav(Lmotor, -powerL);
        mav(Rmotor, -power);
        msleep(100);
        ao();
        msleep(10);
        leftone2(90, powerL);
        while(analog(topHatF) < line){
        	mav(Lmotor, 800);
        	mav(Rmotor, 800);
        	msleep(10);
        }
        ao();
        msleep(10);
        while(analog(topHatF2) < line){
        	mav(Rmotor, 600);
            msleep(10);
    	}
        while(analog(topHatF) > line){
        	mav(Lmotor, -300);
        	mav(Rmotor, 0);
        	msleep(10);
        }
        ao();
        msleep(10);
		
		//back up to allow room for claw to open
        mav(Lmotor, -powerL);
        mav(Rmotor, -power);
        msleep(500);
        set_servo_position(botClaw, 400);
        msleep(500);
		
		//go in and make a turn to shake people out
        while (analog(topHatF2) < line){
            mav(Rmotor, power);
            mav(Lmotor, powerL);
            msleep(5);
    	}
        while (analog(topHatF2) > line){
            mav(Rmotor, power);
            mav(Lmotor, powerL);
            msleep(5);
        }
        ao();
        msleep(10);
        leftone(10, power);
        leftone2(25, power); 
        ao();
        right(30, power);
        ao();
    	}
    return 0;
}