#include <kipr/botball.h>
const int nSpeed = 100;
const int gSpeed = 600;	
const int lSpeed = 400;
const int black = 2000;

void lineFollow ()
{
    if( (get_create_lfcliff() > black) &&  get_create_rfcliff() < black)
    { 
        create_drive_direct(lSpeed, gSpeed);
    }
    else if ((get_create_lfcliff() < black) && get_create_rfcliff() > black)
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
    while (get_create_lfcliff() < black)
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
    turn(90, -nSpeed);
    msleep(10);
    
    /*
    create_drive_direct(nSpeed, nSpeed); //check this shit if program dont work
    msleep(500);
    moveToLine();
    //Previous Couple Lines are just to get to the vertical line on the left side

    turn(90, nSpeed);
    while((get_create_lbump() == 0) & (get_create_rbump() == 0)){
        lineFollow();
    }
    create_stop();
    msleep(1000);
    //Get to the Orange Cylinder

    create_drive_direct(-nSpeed, -nSpeed);
    msleep(1000);

    turn(180, nSpeed);
    //Back up and do a 180 turn to start linefollowing until the wall

    while((get_create_lbump() == 0) & (get_create_rbump() == 0))
        lineFollow();

    create_drive_direct(-nSpeed, -nSpeed);
    msleep(1000);

    turn(-90, nSpeed);

    moveToLine();
    //Go back to the middle box

    create_drive_direct(lSpeed, lSpeed);
    msleep(500);

    turn(-90, nSpeed);

    moveToLine();

    //Previous lines are used to make sure the robot is on the horizontal line for the middle Box

    create_drive_direct(lSpeed, lSpeed);
    msleep(600);

    while(get_create_lfcliff() < black)
        create_drive_direct(nSpeed, -lSpeed);

    create_drive_direct(-lSpeed, lSpeed);
    msleep(100);

    while(get_create_lfcliff() > black || get_create_rfcliff() > black);
    lineFollow();
    //Linefollow to the end of the box and get exactly on the black line there

    while(get_create_lfcliff() < black)
        create_drive_direct(nSpeed, -lSpeed);

    create_drive_direct(-lSpeed, lSpeed);
    msleep(100);

    while((get_create_lbump() == 0) & (get_create_rbump() == 0))
        lineFollow();

    create_drive_direct(-gSpeed, -gSpeed);
    msleep(500);

    turn(-90, gSpeed);

    moveToLine();
    //All Previous Lines are just to get to the right corner box 

    while((get_create_lbump() == 0) & (get_create_rbump() == 0))
        create_drive_direct(gSpeed, gSpeed);

    create_drive_direct(-nSpeed, -nSpeed);
    msleep(1000);

    turn(90, nSpeed);

    moveToLine();

    create_drive_direct(nSpeed, nSpeed);
    turn(90, nSpeed);

    create_stop();
    msleep(10000);

    turn(-90, nSpeed);

    moveToLine();

    create_drive_direct(nSpeed, nSpeed);
    msleep(750);

    turn(90, nSpeed);

    create_stop();
    msleep(1000);

    turn(-90, nSpeed);

    while((get_create_lbump() == 0) & (get_create_rbump() == 0))
        create_drive_direct(nSpeed, nSpeed);

    create_stop();
    msleep(1000);

    turn(180, nSpeed);
    
    moveToLine();

    create_drive_direct(gSpeed, gSpeed);
*/
    return 0;
}