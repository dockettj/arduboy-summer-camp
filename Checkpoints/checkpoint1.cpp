#include <Arduboy2.h> //Adds the Arduboy 2 library
Arduboy2 arduboy; //Defines Arduboy 2 is named arduboy

void setup() {
  // put your setup code here, to run once:
  arduboy.begin(); //Tells the code to start
  arduboy.initRandomSeed(); //Generates a random number
  arduboy.setFrameRate(60); //Sets the FPS
  arduboy.clear(); //Clears the screen
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!arduboy.nextFrame()) { //Checks to see if a new frame is ready
    return; //If it is not, restart the loop.
  }
  arduboy.clear(); //Clears the screen
  arduboy.display(); //Displays the new screen
}