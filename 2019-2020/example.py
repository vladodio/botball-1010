# import kipr's package
import prototype as p

# assigns all the values from the config file
import config

# create a logger object
log = p.logger()


bot = p.legobot(Rmotor, Lmotor, log)
bot.move(100, 100, 400)
