#!/usr/bin/python
import os, sys
import createConfig
import logger
from prototypeC import *
from wallaby import *

import logger
log=logger.logger(createConfig.loggingFolder)

if __name__== "__main__":
	sys.stdout = os.fdopen(sys.stdout.fileno(),"w",0)
#	init();
	log.start()
	log.write("yeet")
	msleep(100)
	log.write("yote")
	msleep(1030)
	log.write("yeep")
