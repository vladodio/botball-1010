#include <kipr/botball.h>
#include <stdbool.h>
const int Rmotor = 1;
const int Lmotor = 0;
const int power = 800;
const int range = 0;
const int topHatF = 2;
const int topHatR = 1;
const int topHatL = 0;
const int black = 2000;
const int white = 400; 
const int line = 2000;
const int tickdeg = 11;
const int burning = 1;
const int people = 0;
const int topClaw = 0;
const int botClaw = 2;
const int topOpen = 0;
const int botOpen = 56;
const int topClose = 992;
const int botClose = 992;
bool burn = false;

void left (int degree, int speed) {
	int ticks = degree * tickdeg;
    int d = gmpc(1);
    mav(Lmotor, -speed);
    mav(Rmotor, speed);
    while (gmpc(1)-d < ticks) {
        msleep(10);
    }
    ao();
}
void right (int degree, int speed) {
	int ticks = degree * tickdeg;
    int d = gmpc(0);
    mav(Lmotor, speed);
    mav(Rmotor, -speed);
    while (gmpc(0)-d < ticks) {
        msleep(10);
    }
    ao();
}
void spinCW(){
    mav(Lmotor, power);
    mav(Rmotor, -power);
    msleep(5);
}
void forward(){
	mav(Lmotor, power);
    mav(Rmotor, power);
    msleep(1000);
}
void forward2(){
    mav(Lmotor, power);
    mav(Rmotor, power);
    msleep(5);
}
void backward2(){
    mav(Lmotor, -power);
    mav(Rmotor, -power);
    msleep(5);
}
void passWhite(){
    while (analog(topHatL) < line || analog(topHatR) < line){
        mav(Rmotor, power);
        mav(Lmotor, power);
        msleep(5);
    }
}

void passBlack(){
    while (analog(topHatL) > line || analog(topHatR) > line){
        mav(Rmotor, power);
        mav(Lmotor, power);
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

int main(){
    enable_servos();
    //set claws to default
    set_servo_position(topClaw, topClose); 
    set_servo_position(botClaw, botClose);
    //turn right and move foward until corner black box
    right(90, power);
    passWhite();
    passBlack();
    while (analog(topHatR) < line) {
		mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(1);
    }
    ao();
    msleep(10);
    msleep(1000);
    while (analog(topHatL) < line) {
		mav(Lmotor, 100);
        msleep(1);
    }
    ao();
    msleep(10);
    /*
    while (analog(topHatL) > line) {
    	mav(Lmotor, 100);
        mav(Rmotor, 0);
        msleep(1);
    }
    ao();
    msleep(10);
    while (analog(topHatR) > line) {
        mav(Lmotor, 0);
        mav(Rmotor, 100);
        msleep(1);
    }
    ao();
    msleep(10);
    */
	//align back
    //turn left and move to gray/black line
    left(90, power);
    passWhite();
    passBlack();
    
    //Align to black line
    while (analog(topHatR) < line) {
		mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(1);
    }
    ao();
    msleep(10);
    msleep(1000);
    while (analog(topHatL) < line) {
		mav(Lmotor, 100);
        msleep(1);
    }
    ao();
    msleep(10);
    
	//align back
    //Turn left onto line
    while (analog(topHatF) < line) {
        mav(Lmotor, -300);
        mav(Rmotor, 300);
        msleep(1);
    }
    
    //Opens camera
    int x;//, y ;
	camera_open_black();
 	msleep(50);
    
    //line follow for one second to pass the orange
    int t = seconds() + 3;
    while(seconds() < t){
               if(analog(topHatF) > line){
                mav(Lmotor, 1000);
                mav(Rmotor, 500);
                msleep(1);
            }
            else {
                mav(Lmotor, 500);
                mav(Rmotor, 1000);
                msleep(1);
        }
 }
    
    int i;
    for (i = 0; i < 2; i++) {
   		camera_update();
        //Line follow until sees red pawn
        while(get_object_count(people) == 0 || get_object_area(people, 0) < 100) { 
            if(analog(topHatF) > line){
                mav(Lmotor, 1000);
                mav(Rmotor, 900);
                msleep(1);
            }
            else {
                mav(Lmotor, 900);
                mav(Rmotor, 1000);
                msleep(1);
            }
            camera_update();
        }
		
        x = get_object_center_x(people, 0);
        camera_update();
	
        //Aligns (centers) robot to red pawn
        while (x <= 75 || x >= 85 ) {
            if(x > 85) {
                backward2();  
            } else if(x < 75 && x >= 0) {
                forward2();   
            } 
            printf("%d \n", x);
            x = get_object_center_x(people, 0);
            camera_update();
        }

        //Moves towards the red pawn then goes back to line
        mav(Lmotor, 0);
        mav(Rmotor, -power);
        msleep(1200);
        //open claws on top and bottom
        set_servo_position(topClaw, topOpen);
        msleep(400);
    	set_servo_position(botClaw, botOpen);
        msleep(400);
        //move forward
        mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(1800);
        //close claws
        set_servo_position(topClaw, topClose);
        msleep(3000);
    	set_servo_position(botClaw, botClose);
    	msleep(3000);
        while (analog(topHatF) < line) {
            mav(Lmotor, -power);
            mav(Rmotor, -power);
            msleep(1);
        }
        
            mav(Lmotor, 0);
            mav(Rmotor, power);
        	msleep(2350);
        
        //left(90, power);
        camera_update();
        while (get_object_count(people) > 0) {
            if(analog(topHatF) > line){

                mav(Lmotor, 1000);
                mav(Rmotor, 900);
                msleep(1);
            }
        	else {
                mav(Lmotor, 900);
                mav(Rmotor, 1000);
                msleep(1);
            }
            camera_update();
        }
    }
    
    //line follow to left double black box
    while(analog(topHatL) < black || analog(topHatR) < black){
        if(analog(topHatF) > line){

                mav(Lmotor, 1000);
                mav(Rmotor, 300);
                msleep(1);
        }

        if(analog(topHatF) < line){

            mav(Lmotor, 300);
            mav(Rmotor, 1000);
            msleep(1);
        }
    }
    
    while (analog(topHatL) > 1000 || analog(topHatR) > 1000) {
    	mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(5);
    }
    mav(Lmotor, power);
    mav(Rmotor, power);
    msleep(800);
    left(90, power);
    
    camera_close();
    camera_open_black();
    camera_update();
    while (analog(topHatR) < black) { 
		mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(1);
        camera_update();
        
        printf("%d \n", get_object_count(people));
        
        if (get_object_count(people) > 0) {
            printf("BURN");
        	burn = true;
        }
     }
    
     while (analog(topHatR) > white) {
    	mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(5);
   	  }
      while (analog(topHatR) < black) {
        
		mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(5);
    }
    left(90, power);
     while (analog(topHatR) > white) {
    	mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(5);
    }
     while (analog(topHatR) < black) {
    	mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(5);
    }
    mav(Lmotor, power);
    mav(Rmotor, power);
    msleep(1000);
    if (burn) {
     	printf("BURN");
    } else {
		printf("NO BURN");
    }
   return 0;
}