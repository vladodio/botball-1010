#include <kipr/botball.h>

const int Rmotor = //x;
const int Lmotor = //x;
const int power = 800;

const int Rlift = 3;
const int Llift = 2;
const int RPower = 280;
const int LPower = 270;
const int R

const int degTicks = 15;

const int lineS = //x;
const int black = //x;
const int white = //x;
const int grey  = //x;


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



void flip(int ticks){
  enable_servos();
  set_servo_position(, Ready);

  int degrees = ticks * degTicks;
  while()  
}

int main(){
  
  flip(45);
}  

