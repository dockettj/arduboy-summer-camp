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
int playery = 27; //Sets the initial location of the paddle top to bottom
int computery = 27; //Sets the initial location of the cpu paddle top to bottom
int computerx = 127 - paddlewidth; //Sets the initial location of the paddle left to right
int playerscore = 0; //Creates player score and sets to 0
int computerscore = 0; //Creates computer score and sets to 0
int counter = 0; //Counts frames
int drawx = 16; //This is our paintbrush
int drawy = 16; //Part 2
int titlearray [5][25] {{1,1,1,1,0,0,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1}, //art
                        {1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,0,0,0},
                        {1,1,1,1,0,0,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1},
                        {1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1},
                        {1,1,0,0,0,0,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,0}};

void resetgame(){ //This is the name of the the function we will call later
  ballx = 63; //Puts the ball back in the middle
  playerscore = 0; //Reset the player's score
  computerscore = 0; //Reset the computer's score
}

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
      arduboy.setCursor(0,0); //Move the cursor
      arduboy.print("Mr. Dockett Presents"); //Give your self credit (20 char max)
      
      for(int i = 0; i < 25; i++) { //Build a counter for X
        arduboy.setCursor(drawx, drawy); // Move the cursor based on math
        for(int n = 0; n < 5; n++) { //Build a counter for Y
          if(titlearray[n][i] == 1) { //Check to see if the counters match 1
             arduboy.fillRect(drawx, drawy, ballsize, ballsize, WHITE); //Paint if so
          }
          drawy = drawy + 4; //Move the cursor down 4
        }
        drawx = drawx + 4; //Move the cursor right 4
        drawy = 16; //Reset the cursor up
      }
      drawx = 16; //Reset the cursor left

      counter = counter + 1; //Counts a frame;
      if (counter < 60) { //If fewer than 60 frames have passed
        arduboy.setCursor(20, 50); //Moves the cursor
        arduboy.print("Press A to play"); //Tells the user what to do
      }
      if (counter >= 120) { //If more than 120 frames have passed
        counter = 0; //Set the counter back to 0 (display nothing)
      }
      
      if (arduboy.pressed(A_BUTTON)) { //Checks to see if A is pressed
        gamestate = 1; //Add one to gamestate and go to the next screen
      }
      break;
      
    case 1:
      //Gameplay screen
      arduboy.setCursor(20, 0); //Moves the cursor
      arduboy.print(playerscore); //Displays the payer's current score
      arduboy.setCursor (101, 0); //Moves the cursor
      arduboy.print(computerscore); //Displays the computer's current score
      arduboy.fillRect(ballx, bally, ballsize, ballsize, WHITE); //Create ball
      if (ballright == 1) { //If the ball is moving right
        ballx = ballx + 1; //Continue moving right
      }
      if (ballright == -1) { //If the ball is moving left
        ballx = ballx -1; //Continue moving left
      }
      if (ballx == playerx + paddlewidth && //If the ball hits the player's paddle's x coordinate
          playery < bally + ballsize && //and the y coordinate of the ball is below the top of the paddle
          playery + paddleheight > bally) { //and the y coordinate of the ball is above to bottom of the paddle
        ballright = 1; //Change the ball to move right instead
      }
      if (ballx + ballsize == computerx && //If the ball hits the computers paddle
          computery < bally + ballsize &&  //and the y coordinate of the ball is below the top of the paddle
          computery + paddleheight > bally) { //and the y coordinate of teh ball is above the bottom of the paddle
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
      arduboy.fillRect(computerx, computery, paddlewidth, paddleheight, WHITE); //Create paddle
      if (ballx > 95 || //If the ball is close to the right side of the screen
          random(0, 10) == 1) { //Or a randomly selected number is 1
            if (bally < computery) { //If the ball is above the paddle
              computery = computery - 1; //Move the paddle up
            }
            if (bally + ballsize > computery + paddleheight) { //If the ball is below the paddle
              computery = computery + 1; //Move the paddle down
            }
      }
      if (ballx < -10) { //If the ball goes off the left side of the screen
        ballx = 63; //Put the ball back in the middle
        computerscore = computerscore + 1; //Add one to the computer's score
      }
      if (ballx > 130) { //If the ball goes off the right side of the screen
        ballx = 63; //Put the ball back in the middle
        playerscore = playerscore + 1; //Add one to the player's score
      }
      
      if (playerscore == 5) { //If the player's score is 5
        gamestate = 2; //Change to the win screen
      } 
      if (computerscore == 5) { //If the computer's score is 5
        gamestate = 3; //Change to the win screen
      }
      break;
      
    case 2:
      //Win screen
      arduboy.setCursor(45, 9); //Moves the cursor
      arduboy.print("You Won"); //Displays "Win Screen"
      arduboy.setCursor(30, 25); //Moves the cursor
      arduboy.print("Score - ");//Displays the score (4 lines)
      arduboy.print(playerscore);
      arduboy.print(" / ");
      arduboy.print(computerscore);
      counter = counter + 1; //Counts a frame;
      if (counter < 60) { //If fewer than 60 frames have passed
        arduboy.setCursor(0, 50); //Moves the cursor
        arduboy.print("Press A to play again"); //Tells the user what to do
      }
      if (counter >= 120) { //If more than 120 frames have passed
        counter = 0; //Set the counter back to 0 (display nothing)
      }
      
      if (arduboy.pressed(A_BUTTON)) { //Checks to see if A is pressed
        resetgame(); //Calls the resetgame method
        gamestate = 0; //Add one to gamestate and go to the next screen
      }
      break;
      
    case 3:
      //Lose screen
      arduboy.setCursor(40, 9); //Moves the cursor
      arduboy.print("You Lost"); //Displays "Win Screen"
      arduboy.setCursor(30, 25); //Moves the cursor
      arduboy.print("Score - ");//Displays the score (4 lines)
      arduboy.print(playerscore);
      arduboy.print(" / ");
      arduboy.print(computerscore);
      counter = counter + 1; //Counts a frame;
      if (counter < 60) { //If fewer than 60 frames have passed
        arduboy.setCursor(0, 50); //Moves the cursor
        arduboy.print("Press A to play again"); //Tells the user what to do
      }
      if (counter >= 120) { //If more than 120 frames have passed
        counter = 0; //Set the counter back to 0 (display nothing)
      }
      if (arduboy.pressed(A_BUTTON)) { //Checks to see if A is pressed
        resetgame(); //Calls the resetgame method
        gamestate = 0 ; //Reset back to the title screen.
      }
      break; 
  }
  arduboy.display(); //Displays the new screen
}
