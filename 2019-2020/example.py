#import kipr's package
import prototype as p

c = p.config()
L = p.logger()

bot = p.legobot(c.get("Ports", "Rmotor"), c.get("Ports", "Lmotor"), L)
bot.move(100, 100, 400)
