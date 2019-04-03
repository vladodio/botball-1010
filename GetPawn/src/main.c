/*CHECKLIST
 Check sensors are plugged in correctly - motors red/black facing the right way
 Check back top hats are tightened in
 Check claw is tightened
 Check coins and battery are secure
 Make sure red pawns are in the middle of the line
 Make sure camera can see
 Top metal stick screwed in tight
*/

#include <kipr/botball.h>
#include <stdbool.h>
const int Rmotor = 1;
const int Lmotor = 0;
const int power = 1470;
const int powerL = 1500; //power for left motor
const int range = 0;
const int topHatF = 2; //front sensor
const int topHatF2 = 5;
const int topHatR = 1; //right
const int topHatL = 0; //left
const int black = 2000;
const int white = 400; 
const int line = 2000;
const double tickdegl = 15;
const double tickdegr = 15.5;
const int burning = 1;
const int people = 0;
const int green = 0;
const int topClaw = 0;
const int botClaw = 2;
const int topOpen = 0;
const int botOpen = 400;
const int topClose = 992;
const int botClose = 1400;
const int frontB = 9;
bool burn = false;
const int ambulance = 3;
const int ambuDown = 1800;
const int ambuUp = 1468;

void left (int degree, int speed) {
    double ticks = degree * tickdegl;
    int d = gmpc(Rmotor);
    mav(Lmotor, -speed);
    mav(Rmotor, speed);
    while (gmpc(Rmotor)-d < ticks) {
        msleep(10);
    }
    ao();
}
void leftone (int degree, int speed) {
    double ticks = degree * tickdegl * 2;
    int d = gmpc(Lmotor);
    mav(Lmotor, -speed);
    while (d-gmpc(Lmotor) < ticks) {
        msleep(10);
    }
    ao();
}
void right (int degree, int speed) {
    double ticks = degree * tickdegr;
    int d = gmpc(Lmotor);
    mav(Lmotor, speed);
    mav(Rmotor, -speed);
    while (gmpc(Lmotor)-d < ticks) {
        msleep(10);
    }
    ao();
}
void rightone (int degree, int speed) {
    double ticks = degree * tickdegr * 2;
    int d = gmpc(Rmotor);
    mav(Rmotor, -speed);
    while (d-gmpc(Rmotor) < ticks) {
        msleep(10);
    }
    ao();
}
void forward(){
    mav(Lmotor, powerL);
    mav(Rmotor, power);
    msleep(1000);
}
void passWhite(){
    while (analog(topHatL) < line || analog(topHatR) < line){
        mav(Rmotor, power);
        mav(Lmotor, powerL);
        msleep(5);
    }
}

void passBlack(){
    while (analog(topHatL) > line || analog(topHatR) > line){
        mav(Rmotor, power);
        mav(Lmotor, powerL);
        msleep(5);
    }
}

void back(int inches, int speed) {
    int ticks = inches * 23;
    int d = gmpc(1);
    int diff = gmpc(1)-gmpc(0);
    while(gmpc(1)-d < ticks){
        if(gmpc(0)+diff < gmpc(1)){
            mav(0,speed);
            mav(1,speed-100);           
        } else{
            mav(0,speed-100);
            mav(1,speed);
        }  
    }    
    msleep(10);
    ao();
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

void getPawn(int xpos){
    //line follow for one second to pass the orange
    int x;
    camera_update();
    //Line follow until sees green
    
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
    }
    
    printf("Area of red: %d \n", get_object_area(people,0));  
    x = get_object_center_x(people, 0);
    camera_update();

    //Aligns (centers) robot to red pawn
    while (x <= xpos || x > xpos + 20) {
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
    }
	ao();
    msleep(10);
    
    //Moves towards the red pawn then goes back to line
    ao();
    msleep(100);
    rightone(90, power);
    msleep(500);

    //open claws on top and bottom
    set_servo_position(topClaw, topOpen);
    msleep(400);
    set_servo_position(botClaw, botOpen);
    msleep(400);

    //Align to gray line
    while(analog(topHatR) < 2000) {
        mav(Lmotor, 0);
        mav(Rmotor, 300);
        msleep(1);
    }
    mav(Rmotor, -200);
    msleep(350);
    while (analog(topHatL) < 2000) {
        mav(Lmotor, 300);
        mav(Rmotor, 0);
        msleep(1);
    }
    
    //move forward
    double t = seconds() + 2.5;
    while(seconds() < t){
        if(digital(frontB)) {
    		mav(Lmotor, -powerL);
    		mav(Rmotor, -power);
    		msleep(500);
            //left(1,power);
            mav(Lmotor, -500);
    		mav(Rmotor, 0);
    		msleep(200);
            t += 0.9;
        } else {
    		mav(Lmotor, powerL);
    		mav(Rmotor, power);
    		msleep(10);
        }
    }
    ao();
    msleep(10);
    //close claws
    set_servo_position(topClaw, topClose);
    msleep(500);
    set_servo_position(botClaw, botClose);
    msleep(500);
    //set_servo_position(botClaw, 500);
    //msleep(400);
    //set_servo_position(botClaw, botClose);
    //msleep(400);
    while (analog(topHatL) < line || analog(topHatR) < line) {
        mav(Lmotor, -power);
        mav(Rmotor, -power);
        msleep(1);
    }
    mav(Lmotor, 1000);
    mav(Rmotor, 1000);
    msleep(200);
    while (analog(topHatF) < line) {
        mav(Lmotor, -500);
        mav(Rmotor, 0);
        msleep(1);
    }
    ao();
    msleep(10);
}

int main(){
    //setup
    enable_servos();
    set_servo_position(topClaw, topClose); 
    set_servo_position(botClaw, botClose);
    set_servo_position(ambulance,ambuDown);
    
    //
    
    //START
    wait_for_light(3);
    shut_down_in(119);
	
    set_servo_position(ambulance,ambuUp);
    msleep(500);
    //move forward to avoid collision with wall
    mav(Lmotor, powerL);
    mav(Rmotor, power);
    msleep(500);
    //turn right and move foward a bit
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
    
    //move forward and backup to align
    mav(Lmotor, powerL);
    mav(Rmotor, power);
    msleep(1000);
    ao();
    msleep(1000);
    while (analog(topHatL) < line) {
        mav(Lmotor, -100);
        mav(Rmotor, -100);
        msleep(1);
    }
    while (analog(topHatR) < line) {
        mav(Lmotor, 0);
        mav(Rmotor, -100);
        msleep(1);
    }
    //turn left onto line
    while (analog(topHatF) < line) {
        mav(Lmotor, -500);
        mav(Rmotor, 0);
        msleep(1);
        printf("%d\n", analog(topHatF));
    }
    
    //Opens camera
    camera_open_black();
    msleep(50);
	
    //Gets pawn thrice
    timeFollow(3);
    
    getPawn(80);
    camera_close();
    msleep(100);
    camera_open_black();
    msleep(2000);
    timeFollow(2);
    getPawn(80);
    camera_close();
    msleep(100);
    camera_open_black();
    msleep(2000);
    timeFollow(2);
    getPawn(85);
    
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
    if (get_object_count(people) > 0) {  
        right(150, power);
        set_servo_position(botClaw, 10); 
        msleep(500);
        //right(50, power);
        //left(10, power);
        mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(2000);
        //right(10, power);
        left(10, power);
       	mav(Rmotor, -power);
        mav(Lmotor, -power);
        msleep(3000);
        set_servo_position(botClaw, botClose);
        mav(Rmotor, power);
        mav(Lmotor, power);
        msleep(3000);
        mav(Rmotor, -power);
        mav(Lmotor, -power);
        msleep(-1000);
        left(20, power);
    	set_servo_position(ambulance,ambuDown);
   	 	msleep(500);
        /*
        mav(Rmotor, -power);
        mav(Lmotor, -power);
        msleep(2000);
        
        set_servo_position(botClaw, 513);
        left(20, power);
        
        
        while(!digital(frontB)){
         mav(Rmotor, power);
         mav(Lmotor, power);
         msleep(1);
        }
        */
        ao();
    } else {
        right(55, power);
        set_servo_position(botClaw, 10); 
        msleep(500);
        while (analog(topHatF2) < line) {
            mav(Lmotor, power);
            mav(Rmotor, power);
            msleep(1);
    	}
        while (analog(topHatF2) > line) {
            mav(Lmotor, power);
            mav(Rmotor, power);
            msleep(1);
    	}
        mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(500);
        
     	set_servo_position(botClaw, botClose);   
        left(20, power);
        mav(Lmotor, -power);
        mav(Rmotor, -power);
        msleep(500);
        set_servo_position(botClaw, botOpen);
		right(15, power);
        mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(500);
        rightone(10, power);
    	set_servo_position(ambulance,ambuDown);
   	 	msleep(500);
    }
    return 0;
}
