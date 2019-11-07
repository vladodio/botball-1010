#!/usr/bin/env python2.7

# program to throw test values at pid 
# program
#
#
#
from threading import Thread
from queue import Queue
import time

def thread1(threadname, q):
    while True:
        a = q.get()
        if a is None: return # Poison pill
        print a

def thread2(threadname, q):
    a = 0
    for _ in xrange(10):
        a += 1
        q.put(a)
        time.sleep(1)
    q.put(None) # Poison pill

queue = Queue()
thread1 = Thread( target=thread1, args=("Thread-1", queue) )
thread2 = Thread( target=thread2, args=("Thread-2", queue) )