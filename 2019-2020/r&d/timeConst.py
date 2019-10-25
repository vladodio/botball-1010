#!/usr/bin/python
import os, sys
from wallaby import *
black = 2000 #?
compTime = 0 # .127999999997


def frontLineSen():
	while(True):
		currValueLeft = (get_create_lcliff_amt() < black)
		currValueRight = (get_create_rcliff_amt() < black)
		if(currValueLeft or currValueRight):
			if(currValueRight):
				return False
			else:
				return True
		msleep(1)	





def main():
	create_connect()
	create_drive_direct(-20,-20)
	msleep(300)
	leftTime=0.0
	rightTime=0.0
	startTime = seconds()
	create_drive_direct(20,20)
	if(frontLineSen()):
		leftTime = float(seconds()) - startTime
		while(get_create_rcliff_amt() > black):
			msleep(1)
		rightTime = float(seconds()) - startTime-compTime
	else:
		rightTime = float(seconds()) - startTime
		while(get_create_lcliff_amt() > black):
			msleep(1)
		leftTime = float(seconds()) - startTime-compTime
	create_drive_direct(0,0)
	print(rightTime)
	print(leftTime)




if __name__== "__main__":
    sys.stdout = os.fdopen(sys.stdout.fileno(),"w",0)
    main();
