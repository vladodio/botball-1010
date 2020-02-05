#!/usr/bin/python2
# general purpose functions for Explorer Post 1010's botball team
# create variant
import wallaby



# logging imports 
import os
from datetime import datetime
from time import time



class logger:
    
    def __init__(self, number_of_decimals=2, log_folder="./"):
        _fileList = []      
        currDate = datetime.now()
        self._number_of_decimals = number_of_decimals
        date =  currDate.strftime("%a %b %d %-I:%M")
        for (dirpath, dirnames, filenames) in os.walk(log_folder):
            _fileList.extend(filenames)
        _fileCount = len(_fileList)+1
        _logLocation = log_folder + "["+str(_fileCount)+"] " + currDate.strftime("%-I:%M %p") + ".log"
        self._logfile = open(_logLocation, "w+")
        self._logfile.write( date + "\n")
        del _fileCount,_logLocation,_fileList

    def __del__(self):
        try:
            self._logfile.close()
        except:
            pass

    def close(self):
        self._logfile.close()

    def round(self, num):
        return(float('%.3f'%(num)))

    def getTime(self):
        return(self.round(time() - self.startTime))

    def startClock(self): 
        self.startTime = time()

    def timeStamp(self):
        return("[ " +str(self.getTime())+ " ] ")

    def printf(self, *args, **kwargs):
        try:
            output = self.timeStamp()
            for item in args:
                output += " " + str(item)
            print(output)
            self._logfile.write(output +"\n")
        except(NameError):
            print("setup not complete yet.")
            output = ""
            for item in args:
                output += " " + str(item)
            print("intended output:" + output)


class roomba:

    turn_methods = ['gyro','time']
    # hand calculate for now
    # ******* note to self: Build calibrate
    degrees_to_ticks = 6100
    gyroscope_bias = 2.2699
    def __init__(self, logging=False, log_directory="./"):
        if(logging):
            self._logging = True
            self.log = logger()
            self.log.startClock()
        else:
            self._logging = False
        self.current_right_power = 0
        self.current_left_power = 0
        self.current_turn_theta = 0
        wallaby.create_connect()


    def __del__(self):
        self.printf("End of Log.")
        self.log.close()        
        self._logging = False
        self.stop()
        wallaby.create_disconnect()

    def printf(self, text):
        try:
            self.log.printf(str(text))
        except:
            print(str(text)+ " [Failed to Log]")

    def gyro_val():
        return(wallaby.gyro_z())

    def msleep(time):
        wallaby.msleep(time)

    def _drive_direct(self, left_power, right_power):
        wallaby.create_drive_direct(left_power, right_power)

    def drive(self, left_power, right_power):
        if(self._logging):
            self.printf("drivin")
        self.current_left_power = left_power
        self.current_right_power = right_power
        self._drive_direct(left_power, right_power)


    def stop(self, log=True):
        if(log and self._logging):
            self.printf("Stop")
        self.current_right_power = 0
        self.current_left_power = 0
        self._drive_direct(0,0)

    def ao(self, log=True):
        if(log and self._logging):
            self.printf("ALL OFF")
        self.stop(False)
        wallaby.ao()

    def pause():
        

    def _turn_with_gyro(self, targetDegrees, Lpower, Rpower, tickLength=10):
        targetTheta = targetDegrees * self.degrees_to_ticks
        self.drive(Lpower,Rpower)
        while(self.current_theta < targetTheta):
            self.msleep(tickLength)
            self.current_theta += abs(gyro_val() - gyroscope_bias) * tickLength
        self.stop(False)
        self.current_theta=0

    def _turn_with_time(self, left_power, right_power, theta):
        pass


# rewrite this, this shit is too crackhead
    def turn(self, left_power, right_power, theta, direction=1, turn_method = 0):
        self.stop(False)
        if(turn_method == 0):
            if(direction > 0):
                self._turn_with_gyro(left_power, right_power, theta)
            elif(direction < 0):
                self._turn_with_gyro(left_power, right_power, -theta)
            else:
                raise Exeception("Direction not properly defined. Adjust 4th field accordingly.")
        elif(turn_method == 1):
            if(direction > 0):
                self._turn_with_gyro(left_power, right_power, theta)
            elif(direction < 0):
                self._turn_with_gyro(left_power, right_power, -theta)
            else:
                raise Exeception("Direction not properly defined. Adjust 4th field accordingly.")
        else:
            if(direction > 0):
                eval("self._turn_with_"+ str(self.turn_methods[turn_method]) +"(left_power, right_power, theta)")
            elif(direction < 0):
                eval("self._turn_with_"+ str(self.turn_methods[turn_method]) +"(left_power, right_power, -theta)")
            else:
                raise Exeception("Direction not properly defined. Adjust 4th field accordingly.")

    def wallFollow():
        pass    

    def lineFollow():
        pass

    def pid():
        pass 


# separate these off from the roomba
class servo():
    
    def __init__(self, port, idle_position, servo_min, servo_max):
        self.port = port
        if((servo_min <= idle_position) and (servo_max >= idle_position)):
            raise Exeception("Idle servo position out of bounds, adjust as needed")
        self.idle_position = idle_position
        self.servo_min = servo_min
        self.servo_max = servo_max
        self.current_servo_position = idle_position
        self.set_servo(idle_position)

    def __del__(self):
        pass

    def _set_servo_pos(self, servo_position):
        wallaby.set_servo_position(self.port, servo_position)

    def _stepped_servo_position_change(self, target_position, steps, time_for_change):
        if((self.servo_min <= target_position) and (self.servo_max >= target_position)):
            time_per_cycle = float(time_for_change)/float(steps) # optimize
            pos_change_per_cycle = (target_position-self.current_servo_position)/steps
            for i in range(steps):
              self.current_servo_position=self.current_servo_position+ pos_change_per_cycle  
              self._set_servo_pos(self.current_servo_position)
              wallaby.msleep(time_per_cycle)
            self._set_servo_pos(target_position)
        else:
            raise Exeception("Attempt to set servo to an out of bound position. attempted to set value to : " + str(target_position))

    def enable():
        wallaby.enable_servos()

    def disable():
        wallaby.disable_servos()

    def go_home(self, stepped=True):
        if(stepped):
            # use some math here
            self.set_servo_stepped(self.idle_position, 5, 200)
        else:
            self._set_servo_pos(self.idle_position)

    def set_servo(self, servo_position):
        if((servo_min <= servo_position) and (servo_max >= servo_position) ):
            self.current_servo_position = servo_position
            wallaby.set_servo_position(self.port, servo_position)
        else:
            raise Exeception("Attempt to set servo to an out of bound position. attempted to set value to : " + str(servo_position))
    
    def set_servo_stepped(self, target_position, steps, time_for_change):
        self._stepped_servo_position_change(target_position, steps, time_for_change)

class motor():

    def __init__(self, port, max_power=1500):
        self.port = port
        self.max_power = 1500

    def __del__(self):
        pass

    def stop(self):
        mav(self.port, 0)

    def drive(self, power):
        if(power>self.max_power):
            power = self.max_power
        mav(self.port, power)

def main():
    r = roomba(True)
    wallaby.msleep(1000)
    r.drive(100,100)
    wallaby.msleep(1000)
    r.drive(300,300)
    wallaby.msleep(1000)
    r.stop()
    wallaby.msleep(1000)
    r.drive(100, -100)
    wallaby.msleep(1000)

if __name__ == '__main__':
    main()

