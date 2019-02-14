#include <kipr/botball.h>
#include <stdbool.h>

const int Rmotor = 1;
const int Lmotor = 0;
const int power = 800;
const int range = 0;
const int topHatR = 1;
const int topHatL = 2;
const int black = 2000;
const int white = 400; 
const int tickdeg = 10;
const int burning = 1;
const int people = 0;
bool burn = false;
void left (int degree, int speed) {
	int ticks = degree * tickdeg;
    int d = gmpc(1);
    mav(0, -speed);
    mav(1, speed);
    while (gmpc(1)-d < ticks) {
        msleep(10);
    }
    ao();
}
void right (int degree, int speed) {
	int ticks = degree * tickdeg;
    int d = gmpc(0);
    mav(0, speed);
    mav(1, -speed);
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
void back(int inches, int speed) {
	int ticks = inches * 23;
    int d = gmpc(1);
    int diff = gmpc(1)-gmpc(0);
	while(gmpc(1)-d < ticks){
        if(gmpc(0)+diff < gmpc(1)){
        	mav(0,speed);
        	mav(1,speed-100);
           
    }else{
         mav(0,speed-100);
         mav(1,speed);
        
        }  
    }    
	msleep(10);
	ao();
}

int main(){
    	//start facing right
    	//get past start line
  		while (analog(topHatL) < black){
            mav(Rmotor, power);
            mav(Lmotor, power);
            msleep(5);
    	}
        
    	while (analog(topHatL) > white){
            mav(Rmotor, power);
            mav(Lmotor, power);
            msleep(5);
    	}
    	
    	//move forward until hit right black box	
        while (analog(topHatL) < black){
            mav(Rmotor, power);
            mav(Lmotor, power);
            msleep(5);
    	}
    	mav(Rmotor, power);
    	mav(Lmotor, power);
    	msleep(2500);
    
    	//Turn left
    	left(90, power);
    	
    	//Moves out of box
    	while (analog(topHatL) < black && analog(topHatR) < black) {
            printf("%d \n", analog(topHatL));
			mav(Rmotor, power);
            mav(Lmotor, power);
            msleep(5);
        }
 
    
    	while (analog(topHatL) > white && analog(topHatR) > white) {
            mav(Rmotor, power);
            mav(Lmotor, power);
            msleep(5);
        }
    
    	//Moves till black/grey line
    	while (analog(topHatL) < black && analog(topHatR) < black) {
			mav(Rmotor, power);
            mav(Lmotor, power);
            msleep(1);
        }
    
    	while (analog(topHatL) > white && analog(topHatR) > white) {
            mav(Rmotor, power);
            mav(Lmotor, power);
            msleep(5);
        }
    	
    	mav(Rmotor, power);
        mav(Lmotor, power);
        msleep(1200);
  
    	//Turn left onto line
    	left(90, power);
    
    
    //Opens camera
    int x;//, y ;
	camera_open_black();
 	msleep(500);
    
    int i;
    for (i = 0; i < 2; i++) {
   		camera_update();
        //Line follow until sees red pawn
        while(get_object_count(people) == 0 || get_object_area(people, 0) < 100) { 
            if(analog(topHatL) > 1000){

                mav(Lmotor, 1000);
                mav(Rmotor, 500);
                msleep(1);
            }

            if(analog(topHatL) < 1000){

                mav(Lmotor, 500);
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
        mav(Lmotor, power);
        mav(Rmotor, 0);
        msleep(2170);
        mav(Lmotor, power);
        mav(Rmotor, power);
        msleep(1300);
        
        //back(100, -power);
        mav(Lmotor, -430);
        mav(Rmotor, -power);
        msleep(1900);
        left(90, power);
        camera_update();
        while (get_object_count(people) > 0) {
            
              if(analog(topHatL) > 1000){

                mav(Lmotor, 1000);
                mav(Rmotor, 500);
                msleep(1);
            }
        	if(analog(topHatL) < 1000){

                mav(Lmotor, 500);
                mav(Rmotor, 1000);
                msleep(1);
            }
            camera_update();
        }

    }
    
    //line follow to left double black box
    while(analog(topHatL) < black || analog(topHatR) < black){
        if(analog(topHatL) > 1000){

                mav(Lmotor, 1000);
                mav(Rmotor, 500);
                msleep(1);
        }

        if(analog(topHatL) < 1000){

            mav(Lmotor, 500);
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
