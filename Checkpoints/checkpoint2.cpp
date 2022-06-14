#include <Arduboy2.h> //Adds the Arduboy 2 library
Arduboy2 arduboy; //Defines Arduboy 2 is named arduboy

int gamestate = 0; //Creates a gamestate and sets it to 0

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
    switch (gamestate) { //Check the current value for gamestate
    case 0:
      //Title screen
      arduboy.setCursor(0, 0); //Moves the cursor to the top left
      arduboy.print("Title Screen"); //Displays "Title Screen"
      if (arduboy.pressed(A_BUTTON)) { //Checks to see if A is pressed
        gamestate = 1; //Add one to gamestate and go to the next screen
      }
      break;
      
    case 1:
      //Gameplay screen
      arduboy.setCursor(0, 0); //Moves the cursor to the top left
      arduboy.print("Gameplay Screen"); //Displays "Gameplay Screen"
      if (arduboy.pressed(A_BUTTON)) { //Checks to see if A is pressed
        gamestate = 2; //Add one to gamestate and go to the next screen
      }
      break;
      
    case 2:
      //Win screen
      arduboy.setCursor(0, 0); //Moves the cursor to the top left
      arduboy.print("Win Screen"); //Displays "Win Screen"
      if (arduboy.pressed(A_BUTTON)) { //Checks to see if A is pressed
        gamestate = 3; //Add one to gamestate and go to the next screen
      }
      break;
      
    case 3:
      //Lose screen
      arduboy.setCursor(0, 0); //Moves the cursor to the top left;
      arduboy.print("Lose Screen"); //Displays "Lose Screen"
      if (arduboy.pressed(A_BUTTON)) { //Checks to see if A is pressed
        gamestate = 0 ; //Reset back to the title screen.
      }
      break; 
  }
  arduboy.display(); //Displays the new screen
}