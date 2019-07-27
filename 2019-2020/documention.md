[Documentation]

[General Function Rules]
* Any function that takes Left and Right parameters will have its first two parameters (L, R)
* Time is always in milliseconds
* ... 

[Reserved Variables]
* T = used for time
* log = refers to the logger object
* ...

[Importing a package]
* Uhhhh i should probably write something here
*
*

[Create]
* move(Lpower, Rpower, T) = moves the roomba
* stop(T) = stops the roomba
* turn(degree, direction, Mpower) = turns the roomba x degrees. direction: (right or left) 

[Legobot]
* move(Lpower, Rpower, T) = moves the legobot
* stop(T) = stops the legobot
* turn(degree, direction, Mpower) = turns the legobot x degrees. direction: (right or left) 

[Logger]

Write helpful information to file allowing
debuging after run.

* Create an logger object:
  * L = prototype.logger("Log-Folders-absolute-path")

* Write a message with a timestamp:
  * `L.write("message")`

* Write a message without a timestamp:
  * L.writeNT("message")

* Writing a sensor value:
  * L.sensor("Name-of-the-sensor", the-sensors-current-value)

* Write an error message to the file:
  * L.fatalError(str(e))

* Write a warning to the file
  * L.warning("warning")
