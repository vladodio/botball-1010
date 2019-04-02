#include <kipr/botball.h>

const int RMotor = 3;
const int LMotor = 2;
const int Rpower = 1500;
const int Lpower = 1400;
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
            mav(RMotor, 1000);
            mav(LMotor, 500);
            msleep(5);
            continue;
        }

        else if ((analog(LineS) < grey)){
            mav(RMotor, 500);
            mav(LMotor, 1000);
            msleep(5);
            continue;
        }
        else if (RLineS > black){
            mav(RMotor, 1200);
            mav(LMotor, 500);
            msleep(5);
            continue;
        }    
        else{
            mav(RMotor, 250);
            mav(LMotor, 250);
        }
    }
    ao();
}

void turn(int direction, int degree, int speed){
    if(direction == 0){
        int ticks = degree * -tickdeg;
        int d = gmpc(RMotor);
        mav(LMotor, speed);
        mav(RMotor, -speed);

        while (gmpc(RMotor)-d > ticks) { msleep(10); }
        ao();
    }

    if(direction == 1){
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
    msleep(4000);
}

void slowline(double seconds ){
    double i = 0;
    seconds = seconds/4;
    while(i < seconds){
        timeFollow(4);
        msleep(250);
        i++;
        mav(farming, farmPower);
    }
}

void forward(int msecs){
    mav(RMotor, Rpower);
    mav(LMotor, Lpower);
    msleep(msecs);
    ao();
}
int main(){
    enable_servos();
    set_servo_position(lift, down);
    /*
    turn(right, 90, power);
    msleep(5000);
    return(0);
    */
        mav(RMotor,power);
    mav(LMotor,power);
    msleep(200);
    turn(right,100,power);
    mav(RMotor,power);
    mav(LMotor,power-50);
    while(analog(RLineS) < black){ msleep(5); }
    ao();
    msleep(10);
        forward(4000);
        turn(left, 90, power);
        ao();
        mav(RMotor, power);
        mav(LMotor, power);
    msleep(3000);
        while(analog(RLineS) < black) {msleep(5); }
      

        mav(RMotor, -power);
        mav(LMotor, -power);
        msleep(350);
        ao();
        turn(left, 95, power);
        ao();
        mav(farming, farmPower);
        slowline(28);
        ao();
    turn(left,160,power);
    mav(RMotor, power);
    mav(LMotor, power);
    msleep(3500);
    ao();
    turn(left, 180, power);
    flip();
        return 0;

        }  

