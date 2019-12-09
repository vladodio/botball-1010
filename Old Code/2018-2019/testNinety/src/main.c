#include <kipr/botball.h>
/* Issues:
/       The start function doesn't compile
/       The code is LACKING comments, Remember Zain has to understand what the code is doing
/       Changing the constant names to be more descriptive wouldn't hurt
/       Checklist doesn't exist and very much needs to
/       
/
*/

const int TRUE = 1;
const int black = 2000;
const int pivot = 250;
const int forwardbl = 470;

//Create sensors
const int lCliff = 1;
const int rCliff = 2;
const int lfCliff = 3;
const int rfCliff = 4;

//Wallaby sensors
const int touch = 0; // touch sensor in grabber
const int start = 0; // light sensor for starting

const int right = 1;
const int left = -1;

int go = 0;
int current = 0;

const int wire = 3; // motor to repair comm wire
const int atWire = 800;

const int horizontal = 1683;
const int vertical = 520;

const int atLevel = 245;
const int atPipe = 625;
const int atUp = 1600;

// The tire claw consts
const int raise = 0; // The servo that raises the tireclaw
const int turner = 1; // The servo that rotates the tireclaw
const int push = 9; // The pushButton that detects the pipe

const int ninety = 1000;
const int semi = 2000;

const int forward = 530;
const int pivot2 = 320;
const int forward2 = 228;

void turn(int degree, int direction, int adjustment){
    if(degree == 90){
        create_drive_direct(200 * (direction), -200 * (direction));
        msleep(ninety+adjustment);
    }
    else if(degree == 180){
        create_drive_direct(200 * (direction), -200 * (direction));
        msleep(semi+adjustment);
    }
    else{
        printf("Angle not Defined??");
        //exit();
    }
}

int main(){
    create_connect();
	turn(90,right,0);
    return 0;
}