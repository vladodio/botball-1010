#include <kipr/botball.h>

const int Rmotor = //x;
const int Lmotor = //x;
const int power = 800;

const int Rlift = 3;
const int Llift = 2;
const int RPower = 280;
const int LPower = 270;
const int degTicks = 15;

const int Rline = //x;
const int Lline = //x;
const int black = //x;
const int white = //x;
const int grey  = //x;

void flip(int degrees){
  int ticks = degrees * degTicks;
  int time = gmpc(Llift)+ticks;
  mav(Rlift, RPower);
  mav(Llift, LPower);
  while(gmpc(Llift) < time){
    msleep(10);
    //printf("%d", gmpc(Llift));
  }
  ao();
  msleep(10);
  printf("I have decided I want to die.");
}

void follow(time){
  int tick = gmpc(Rlift) + time;
  if(analog() > ){
  
  }
  
}

int main(){
  flip(45);
}  

