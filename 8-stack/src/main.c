#include <kipr/botball.h>

const int RMotor = 2;
const int LMotor = 3;
const int power = 1500;
const int left = 1;
const int right = 0;
const double tickdeg = 16;

const int lift = 0;
const int down = 50;
const int up = 1024;

const int farming = 0;
const int farmPower = 1500;

const int LineS = 0;
const int black = 2200;
const int grey = 1000;
const int white = 250;
const int RLineS = 1;
const int LLineS = 2;

void timeFollow(double s){
double t = seconds() + s;
    while(seconds() < t){
        if((analog(LineS) > grey)){
            mav(LMotor, 1000);
            mav(RMotor, 500);
            msleep(5);
            continue;
        }
        
        else if ((analog(LineS) < grey)){
            mav(LMotor, 500);
            mav(RMotor, 1000);
            msleep(5);
            continue;
        }
        else if (RLineS > black){
            mav(LMotor, 1200);
            mav(RMotor, 500);
            msleep(5);
            continue;
        }    
        else{
          mav(LMotor, 250);
          mav(RMotor, 250);
        }
    }
}

void turn(int direction, int degree, int speed){
    if(direction == 1){
	int ticks = degree * -tickdeg;
    int d = gmpc(RMotor);
    mav(LMotor, speed);
    mav(RMotor, -speed);
        
    while (gmpc(RMotor)-d > ticks) { msleep(10); }
    ao();
	}
    
    if(direction == 0){
	int ticks = degree * -tickdeg;
    int d = gmpc(LMotor);
    mav(LMotor, -speed);
    mav(RMotor, speed);
    while (gmpc(LMotor)-d > ticks) { msleep(10); }
        ao();   
	}
    return;
}

void flip(){
  enable_servos();
  set_servo_position(lift, up); 
}

int main(){
	enable_servos();
    set_servo_position(lift, down);
    /*
    turn(right, 90, power);
    msleep(5000);
    return(0);
    */
    turn(right,120,power);
    mav(RMotor,power);
    mav(LMotor,power);
    while(analog(RLineS) < black){ msleep(5); }
    ao();
    msleep(10);
    mav(RMotor,power);
    mav(LMotor,power);
    msleep(2000);
    while(analog(RLineS) < black){ msleep(5); }
    ao();
    turn(left, 90, power);
    ao();
    mav(RMotor, power);
    mav(LMotor, power);
    while(analog(RLineS) < black) {msleep(5); }
    mav(RMotor, power);
    mav(LMotor, power);
    msleep(2000);
	
    while(analog(RLineS) < black){ 
        mav(RMotor,power);
   	   mav(LMotor,power);
        msleep(1);
     
    }
    ao();
    msleep(100);
    mav(RMotor, -power);
    mav(LMotor, -power);
    msleep(350);
    ao();
    turn(left, 95, power);
    ao();
    mav(farming, farmPower);
    timeFollow(60);
    ao();
    return 0;
   
}  

