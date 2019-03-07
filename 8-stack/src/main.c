#include <kipr/botball.h>
const int Rmotor = //x;
const int Lmotor = //x;
const int power = 800;

const int Rlift = //x;
const int Llift = //x;
const int liftPower = //x;
  
const int Rline = //x;
const int Lline = //x;
const int black = //x;
const int white = //x;

void forward(time){
  mav(Rmotor, power);
  mav(Lmotor, power);
  msleep(time);
}

void flip(ticks){
  int tick = gmpc(Rlift)+ticks;
  mav(Rlift, liftPower);
  mav(Llift, liftPower);
  while(gmpc() < tick){
    msleep(10);
  }
  ao();
  printf("I have decided I want to die.");
  return
}

void follow(){
  
  
}
int main(){
  
}  
