#!/usr/bin/env python2.7

# program to throw test values at pid 
# program
#
#
#
import PIDV1

times = [range(3)]
times[0] = PIDV1.pid(.1, .1, .1)
times[1] = PIDV1.pid(.15, .1, .1)
times[2] = PIDV1.pid(.1, .15, .1)
times[3] = PIDV1.pid(.1, .1, .15)

print("done")
for item in times:
	print(item)