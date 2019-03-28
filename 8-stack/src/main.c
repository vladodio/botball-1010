#include <kipr/botball.h>

const int Rmotor = //x;
const int Lmotor = //x;
const int power = 800;

const int lift = 0;
const int down = 50;
const int up = 200; //?

const int farming = //x;
const int farmPower = 1500;

const int lineS = //x;
const int black = //x;
const int white = //x;


void timeFollow(double s){
double t = seconds() + s;
    while(seconds() < t){
        if(analog(lineS) > line){
            mav(Lmotor, 1000);
            mav(Rmotor, 500);
            msleep(5);
        }
        else {
            mav(Lmotor, 500);
            mav(Rmotor, 1000);
            msleep(5);
        }
    }
}

void turn(int direction, int degree, int speed){
    if(direction == 1){
	int ticks = degree * tickdeg;
    int d = gmpc(0);
    mav(Lmotor, speed);
    mav(Rmotor, -speed);
    while (gmpc(0)-d < ticks) { msleep(10); }
    ao();
	}
    
    if(direction == 0){
	int ticks = degree * tickdeg;
    int d = gmpc(1);
    mav(Lmotor, -speed);
    mav(Rmotor, speed);
    while (gmpc(1)-d < ticks) { msleep(10); }
    ao();   
	}
    return;
}

void flip(){
  enable_servos();
  set_servo_position(lift, up); 
  msleep(5000);
}

int main(){
	enable_servos();
    set_servo_position(lift, down);
    mav(l)
    
    
    
    
    mav(0,1500);
    msleep(100000);
    
}  
