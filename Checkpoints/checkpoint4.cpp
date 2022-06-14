#include <Arduboy2.h> //Adds the Arduboy 2 library
Arduboy2 arduboy; //Defines Arduboy 2 is named arduboy

int gamestate = 0; //Creates a gamestate and sets it to 0
int ballx = 62; //Sets the ball's location in the middle, left to right
int bally = 0; //Sets the ball's location at the top, top to bottom
int ballsize = 4; //The ball will be four pixels by four pixels
int ballright = 1; //Sets the left to right direction of the ball
int balldown = 1; //Sets the top to bottom direction of the ball
int paddlewidth = 4; //Sets the width of the paddle
int paddleheight = 9; //Sets the height of the padle
int playerx = 0; //Sets the initial location of the paddle left to right
int playery = 0; //Sets the initial location of the paddle top to bottom

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
      arduboy.fillRect(ballx, bally, ballsize, ballsize, WHITE); //Create ball
      if (ballright == 1) { //If the ball is moving right
        ballx = ballx + 1; //Continue moving right
      }
      if (ballright == -1) { //If the ball is moving left
        ballx = ballx -1; //Continue moving left
      }
      if (ballx == 0) { //If the ball hits the left side of the screen
        ballright = 1; //Change the ball to move right instead
      }
      if (ballx + ballsize == 127) { //If the ball hits the right side of the screen
        ballright = -1; //Change the ball to move left instead
      }
      if (balldown == 1) { //If the ball is moving down
        bally = bally + 1; //Continue moving down
      }
      if (balldown == -1) { //If the ball is moving up
        bally = bally - 1; //Continue moving up
      }
      if (bally == 0) { //If the ball hits the top of the screen
        balldown = 1; //Change the ball to move down instead
      }
      if (bally + ballsize == 63) { //If the ball hits the bottom of the screen
        balldown = -1; //Change the ball to move up instead
      }
      arduboy.fillRect(playerx, playery, paddlewidth, paddleheight, WHITE); 
      // ^^^^ Create paddle
      if (arduboy.pressed(UP_BUTTON) && playery > 0) { 
        // ^^^^ If up is pressed and not at top
        playery = playery - 1; //Move the paddle up
      }
      if (arduboy.pressed(DOWN_BUTTON) && (playery + paddleheight) < 63) { 
        // ^^^^ If down is pressed and not at bottom
        playery = playery + 1; //Move the paddle down
      }
      
      //if (arduboy.pressed(A_BUTTON)) { //Checks to see if A is pressed
      //  gamestate = 2; //Add one to gamestate and go to the next screen
      //}
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