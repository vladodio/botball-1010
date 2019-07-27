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
* moves the roomba
  ```python
  move(Lpower, Rpower, T)
  ```
  
* stops the roomba
  ```python
  stop(T)
  ```
  
* turns the roomba x degrees. direction: (right or left) 
  ```python 
  turn(degree, direction, Mpower)
  ```
  
[Legobot]
* move(Lpower, Rpower, T) = moves the legobot
* stop(T) = stops the legobot
* turn(degree, direction, Mpower) = turns the legobot x degrees. direction: (right or left) 

[Logger]

Write helpful information to file allowing
debuging after run.

* Create an logger object:
  ```python 
  L = prototype.logger("Log-Folders-absolute-path")
  ```
* Write a message with a timestamp:
  ```python 
  L.write("message")
  ```

* Write a message without a timestamp:
  ```python 
  L.writeNT("message")
  ```
  
* Writing a sensor value:
  ```python 
  L.sensor("Name-of-the-sensor", the-sensors-current-value)
  ```
  
* Write an error message to the file:
  ```python 
  L.fatalError(str(e))
  ```
  
* Write a warning to the file
  ```python 
  L.warning("warning")
  ```
