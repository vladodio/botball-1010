#include <kipr/botball.h>
const int nSpeed = 500;
const int gSpeed = 600;	
const int lSpeed = 400;
const int lTopHat = 0;
const int rTopHat = 1;
const int black = 2000;

void lineFollow ()
{
    if( (analog (lTopHat) > black) && analog (rTopHat) < black)
    { 
        create_drive_direct(lSpeed, gSpeed);
    }
    else if ( (analog (lTopHat) < black) && analog (rTopHat) > black)
    {
        create_drive_direct(gSpeed, lSpeed);
    }
    else
    {
        create_drive_direct(nSpeed, nSpeed);
    }
}

void moveToLine ()
{
	while ( analog (lTopHat) < black)
    {
    create_drive_direct(nSpeed, nSpeed);
    }
    create_stop();
    msleep(100);
}

void turn (int degrees, int speed)
{
    set_create_total_angle(0);
    msleep(10);
    
	while (abs(get_create_total_angle ()) < degrees)
    {
    	int x = get_create_total_angle ();
        printf(" total angle is %d \n", x);
        
        create_drive_direct(speed, -speed);
        msleep(10);
    }
        create_stop();
}
    
int main()
{
    create_connect();
    turn(-90, nSpeed);
    create_drive_direct(nSpeed, nSpeed); //check this shit if program dont work
    msleep(500);
    moveToLine();
    turn(90, nSpeed);
    while((get_create_lbump() == 0) & (get_create_rbump() == 0)){
    lineFollow();
    }
    return 0;
}