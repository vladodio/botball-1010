#include <kipr/botball.h>
const int nSpeed = 100;
const int gSpeed = 600;	
const int lSpeed = 400;
const int black = 2000;
const int lCliff = 1;
const int rCliff = 2;
const int lfCliff= 3;
const int rfCliff = 4;

void lineFollow ()
{
    if( (get_create_lfcliff() < black) &&  get_create_rfcliff() > black)
    { 
        create_drive_direct(lSpeed, gSpeed);
    }
    else if ((get_create_lfcliff() > black) && get_create_rfcliff() < black)
    {
        create_drive_direct(gSpeed, lSpeed);
    }
    else
    {
        create_drive_direct(nSpeed, nSpeed);
    }
}

void moveToLine (int which)
{
    if(which == lCliff){
    while (get_create_lcliff_amt() > black)
    {
        create_drive_direct(nSpeed, nSpeed);
    }
    }
    else if(which == rCliff){
    while (get_create_rcliff_amt() > black)
    {
        create_drive_direct(nSpeed, nSpeed);
    }
    }
    else if(which == lfCliff){
    while (get_create_lfcliff_amt() > black)
    {
        create_drive_direct(nSpeed, nSpeed);
    }
    }
    else if(which == rfCliff){
    while (get_create_rfcliff_amt() > black)
    {
        create_drive_direct(nSpeed, nSpeed);
    }
    }
    create_stop();
    msleep(100);
}

void turn (int time, int speed)
{
    int t = seconds()+time;
 
    
    while(seconds() < t)
    {
		create_drive_direct(-speed, speed);
    }
    create_stop();
    msleep(10);
}
void moveToBump(){
    while((get_create_lbump() == 0) || (get_create_rbump() == 0)){
        create_drive_direct(nSpeed, nSpeed);
    }
}

int sensorFindTurn(int which){
    
    int sec = seconds();
    
    if(which == lCliff){
    while(get_create_lcliff_amt() > black){
        create_drive_direct(200, -200);
    } 
    }
    else if(which == rCliff){
        while(get_create_rcliff_amt() > black){
        create_drive_direct(-200, 200);
    } 
    }
    else if(which == lfCliff){
        while(get_create_lfcliff_amt() > black){
        create_drive_direct(200, -200);
    } 
    }
    else if(which == rfCliff){
        while(get_create_rfcliff_amt() > black){
        create_drive_direct(-200, 200);
    } 
    }
    return sec;
}

int main()
{
    create_connect();
    enable_servos();
    /*
    while(get_create_rfcliff_amt() < 100000){ 
        //create_drive_direct(50,50);
        msleep(10);
    	printf("%d \n", get_create_rfcliff_amt());
    }
    */
    //Moves to the left corner box
	moveToLine(lCliff);
    create_drive_direct(nSpeed-15, nSpeed);
    msleep(500);
    
    //Moves so it is at horizontal line of left upper rectangle
    moveToLine(lCliff);
   	sensorFindTurn(lfCliff);   
    moveToLine(lCliff);
	create_drive_direct(nSpeed, nSpeed);
    msleep(700);
    moveToLine(lCliff);
    
    //Aligns on the line to lineFollow
    sensorFindTurn(lfCliff);
    sensorFindTurn(rfCliff);
    create_drive_direct(50,-50);
    msleep(300);
  
    //Line follow to left side horizontal line on rectangle
    while(get_create_lcliff_amt() > black){
    lineFollow();
    printf("lf cliff %d \n", get_create_lfcliff_amt());
    printf("rf cliff %d \n", get_create_rfcliff_amt());
	}
   	
    //Aligns back onto black line
    sensorFindTurn(lfCliff);
    sensorFindTurn(rfCliff);
    create_drive_direct(50, -50);
    msleep(300);
   
	set_servo_position(0, 800);
    msleep(100);
    
    lineFollow();
    msleep(300);
    
    create_stop();
    msleep(1000);
    
    create_drive_direct(200, -200);
    msleep(400);
    
    sensorFindTurn(lfCliff);
    create_drive_direct(50, -50);
    msleep(400);
    create_drive_direct(100,100);
    msleep(400);
    sensorFindTurn(lfCliff);
    sensorFindTurn(rfCliff);
    create_drive_direct(50,-50);
    msleep(100);
    
    while(get_create_lflightbump_amt() != 1	|| get_create_rflightbump_amt() != 1){
    lineFollow();
        printf(" \n %d", get_create_lflightbump_amt);
    }
    
    create_drive_direct(nSpeed, nSpeed);
    msleep(100);
    
    //should line follow down the whole line, probably won't
    while ((get_create_lbump() == 0) && (get_create_rbump() == 0))
    {
		lineFollow();
    }
    //goes backward
    create_drive_direct(-50, -50);
    msleep(200);
    //turns right
    create_drive_direct(50, 0);
    msleep(100);
    
    return 0;
}