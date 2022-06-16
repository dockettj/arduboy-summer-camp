# Arduboy Pong Instructions

## Chapter 1: Environment Setup

**Step 1: Download, install, and open the Arduino IDE.**

- [https://www.arduino.cc/en/software#download](https://www.arduino.cc/en/software#download)


**Step 2: Open the library manager so we can install libraries.**

- Sketch > Include Library > Manage Libraries


**Step 3: Install the following libraries.**

- Arduboy by Ross O. Shoger
- Arduboy 2 by Scott Allen
- ArduboyTones by Scott Allen
- ArduboyPlaytune by Scott Allen
- ArdBitmap by Ignacio Vina
- ArdVoice by Ignacio Vina
- ATMlib by info@Team_arg.org
- Arduboy-TinyFont by Boti Kis


**Step 4: Plug your Arduboy in and target it.**

- Substep 1: Tools > Board > Arduino AVR Boards > Arduino Leonardo
- Substep 2: Tools > Port > *Com#/Filepath]*(Arduino Leonardo)
  - It is important to note that this may look different at home.
  - However, look for "Arduino Leonardo" and you will probably still get the right one.

**Step 5: Test**
   
- Substep 1: File > Examples > Arduboy 2 > Buttons
  - This will open a new window. 
  - Click the arrow pointing to the right in the new window (upload).
  - The button test will be pushed to your arduboy.
  - Test the buttons to make sure they all do something.
- Substep 2: File > Examples > Arduboy 2 > PlayTune
  - This will open a new window.
  - This example will be extremely loud.
  - Click the arrow pointing to the right in the new window (upload).
  - The Playtune test will be pushed to your arduboy.
  - This will test the speaker to make sure it works.
  - Press A to mute and B to unmute.
- Substep 3: File > Examples > Arduboy 2 > Ardubreakout
  - This will open in a new window.
  - Click the arrow pointint to the right in the new window (upload).
  - The ArduBreakout Game will be pushed to your arduboy.
  - Press A to start/launch.
  - Move the joystick left/right to move.
  - Press B to pause.

### Congratulations! Your device works.
---



##Chapter 2: Creating our first game (Pong)

*Table of Contents:*

- Step 1: Set up a new Sketch
- Step 2: Create a title, game, win, and lose screen
- Step 3: Create a bouncing ball
- Step 4: Create and control a paddle
- Step 5: Create the computer's paddle
- Step 6: Collision
- Step 7: Adjusting the AI
- Step 8: Scoring
- Step 9: Creating a new ball and resetting the game
- Step 10: Final quality improvements

---

###Step 1: Set up a new Sketch

- File > New
- You do not need to type from the double slash on. These are comments.
- At the very top before anything else add the following:
  
```c++
    #include <Arduboy2.h>   //Adds the Arduboy 2 library
    Arduboy2 arduboy;       //Defines Arduboy 2 is named arduboy
```
- Between the curly brackets for setup, add the following:
```c++
    arduboy.begin();            //Tells the code to start
    arduboy.initRandomSeed()    //Generates a random number
    arduboy.setFrameRate(60)    //Sets the FPS
    arduboy.clear();            //Clears the screen
```
- Between the curly brackets for loop, add the following:
```c++
    if(!arduboy.nextFrame()) {    //Checks to see if a new frame is ready
      return;                     //If it is not, restart the loop
    }
    arduboy.clear();     //Clears the screen
    arduboy.display();   //Displays the new screen
```
- This complete checkpoint can be found in the checkpoints folder (1).
- All checkpoints can be opened with notepad or Visual Studio Code
- Free download: https://code.visualstudio.com

---
###Step 2: Create a title, game, win, and lose screen
- Create and set a gamestate for the different potential screens.
- Place the following above setup and below where arduboy is named.

```c++
    int gamestate = 0;  //Creates a gamestate and sets it to 0.
```

- Create a switch that checks gamestate to change the screens.
- Each case represents a different possible screen.
- "break;" tells the program to leave the switch.
- Place the following in the loop between clear and display.

```c++
    switch (gamestate) {                    //Check the current value for gamestate
      case 0:                               //Title screen
        arduboy.setCursor(0,0);             //Moves the cursor to the top left
        arduboy.print("Title Screen");      //Displays "Title Screen"
        if (arduboy.pressed(A_BUTTON)) {    //Checks to see if A is pressed
          gamestate = 1;                    //Add one to gamestate and go to the next screen
        }
      break;

      case 1:                               //Gameplay screen
        arduboy.setCursor(0,0);             //Moves the cursor to the top left
        arduboy.print("Gameplay Screen");   //Displays "Gameplay Screen"
        if (arduboy.pressed(A_BUTTON)) {    //Checks to see if A is pressed
          gamestate = 2;                    //Add one to gamestate and go to the next screen
        }
      break;
        
      case 2:                               //Win screen
        arduboy.setCursor(0,0);             //Moves the cursor to the top left
        arduboy.print("Win Screen");        //Displays "Win Screen"
        if (arduboy.pressed(A_BUTTON)) {    //Checks to see if A is pressed
          gamestate = 3;                    //Add one to gamestate and go to the next screen
        }
      break;
        
      case 3:                               //Game over screen
        arduboy.setCursor(0,0);             //Moves the cursor to the top left
        arduboy.print("Lose Screen");       //Displays "Lose Screen"
        if (arduboy.pressed(A_BUTTON)) {    //Checks to see if A is pressed
          gamestate = 0;                    //Reset back to the title screen.
        }
      break;
    }
```

- We can now conduct our first test. Click the upload button.
- Pressing A will cycle through the different screens very quickly.
- Remember, this phase is just proof of concept.
- This complete checkpoint can be found in the checkpoints folder (2).

---
###Step 3: Create a bouncing ball
        
- Add a ball and have it bounce around the screen
- Place the following just below where we declared the gamestate variable

```c++
    int ballx = 62;         //Sets the ball's location in the middle, left to right
    int bally = 0;          //Sets the ball's location at the top, top to bottom
    int ballsize = 4;       //The ball will be four pixels by four pixels
    int ballright = 1;      //Sets the left to right direction of the ball
    int balldown = 1;       //Sets the top to bottom direction of the ball
```
- We want to be stuck at gameplay now, so comment out the button check in the gameplay screen's case. You will need to comment all three lines
- Comments are created by putting // before whatever you want ignored
- Draw the ball on the screen by adding the following inside of the gameplay case below the print statement:

```c++
    arduboy.fillRect(ballx, bally, ballsize, ballsize, WHITE);  //Create ball
```      

- Make the ball move left to right on the screen by adding the following directly beneath the arduboyfillRect line:

```c++
    if (ballright == 1) {             //If the ball is moving right
      ballx = ballx + 1;              //Continue moving right
    }
    if (ballright == -1) {            //If the ball is moving left
      ballx = ballx -1;               //Continue moving left
    }
    if (ballx == 0) {                 //If the ball hits the left side of the screen
      ballright = 1;                  //Change the ball to move right instead
    }
    if (ballx + ballsize == 127) {    //If the ball hits the right side of the screen
      ballright = -1;                 //Change the ball to move left instead
    }
```
        
- Make the ball move up and down on the screen by adding the following directly beneath what we just added.

```c++
    if (balldown == 1) {             //If the ball is moving down
      bally = bally + 1;             //Continue moving down
    }
    if (balldown == -1) {            //If the ball is moving up
      bally = bally - 1;             //Continue moving up
    }
    if (bally == 0) {                //If the ball hits the top of the screen
      balldown = 1;                  //Change the ball to move down instead
    }
    if (bally + ballsize == 63) {    //If the ball hits the bottom of the screen
      balldown = -1;                 //Change the ball to move up instead
    }
```

- It is now time to test again. Click the upload button.
- Pressing A will take you to the gameplay screen.
- You no longer have access to the win or lose screens.
- You should have a ball bouncing around on your screen.
- This complete checkpoint can be found in the checkpoints folder (3)

---
###Step 4: Create and control a paddle
- Add a paddle and get it moving on the screen with your input
- Place the following just below your ball variables:

```c++
    int paddlewidth = 4;    //Sets the width of the paddle
    int paddleheight = 9;   //Sets the height of the padle
    int playerx = 0;        //Sets the initial location of the paddle left to right
    int playery = 0;        //Sets the initial location of the paddle top to bottom
```

- Draw the paddle on the screen by adding the following inside of the gameplay case below all of the pieces we added for the ball.

```c++
    arduboy.fillRect(playerx, playery, paddlewidth, paddleheight, WHITE);   //Create paddle
```

- Make the controller move the paddle up and down based on user input and limit how far up and down it can go by adding the following on the next line.

```c++
    if (arduboy.pressed(UP_BUTTON) &&           //If up is pressed   
        playery > 0) {                          //and not at top

      playery = playery - 1;                    //Move the paddle up
    }
    if (arduboy.pressed(DOWN_BUTTON) &&         //If down is pressed
       (playery + paddleheight) < 63) {         //not at bottom

      playery = playery + 1;                    //Move the paddle down
    }
```     
- Let's test again. Click the upload button.
- Press A to go to the gameplay screen
- You now have a paddle that you can move up and down on the screen.
- This complete checkpoint can be found in the checkpoints folder (4)

---
###Step 5: Create the computer's paddle
       
- It is not fair for only you to have a paddle, and makes for a boring game.
- Add a paddle for your computer opponent.
- Place the following just below your paddle variables.

```c++
    int computery = 0;                    //Sets the initial location of the cpu paddle top to bottom
    int computerx = 127 - paddlewidth;    //Sets the initial location of the paddle left to right
```

- Draw the paddle on the screen by adding the following inside of the gameplay case below the pieces for the player controlled paddle.

```c++
    arduboy.fillRect(computerx, computery, paddlewidth, paddleheight, WHITE);   //Create paddle
```

- Time to create a really basic AI based on some rules.
- Place under where the computer paddle was created.

```c++
    if (bally < computery) {                                //If the ball is above the paddle
      computery = computery -1;                             //Move the paddle up
    }
    if (bally + ballsize > computery + paddleheight) {      //If the ball is below the paddle
      computery = computery + 1;                            //Move the paddle down
    }
```

- Let's test again. Click the upload button.
- Press A to go to the gameplay screen.
- The computer now has a paddle.
- It plays perfectly. It is too good. We need to fix that.
- This complete checkpoint can be found in the checkpoints folder (5)

---
###Step 6: Collision

- Check to see if the ball is hitting the paddles instead of the edge of the screen with respect to left to right movement while leaving up and down the same.
- Change the ballx collision on the left to check to see if it is hitting the paddle instead of an invisible wall.
- Update "if(ballx == 0)..." to the following:

```c++
    if (ballx == playerx + paddlewidth &&   //If the ball hits the player's paddle's x coordinate
      playery < bally + ballsize &&         //and the y coordinate of the ball is below the top of the paddle
      playery + paddleheight > bally) {     //and the y coordinate of the ball is above to bottom of the paddle
```

- Repeat the process for the computer by changing "if (ballx + ballsize == 127)..." to the following:

```c++
    if (ballx + ballsize == computerx &&    //If the ball hits the computers paddle
      computery < bally + ballsize &&       //and the y coordinate of the ball is below the top of the paddle
      computery + paddleheight > bally) {   //and the y coordinate of the ball is above the bottom of the paddle
```

- Time for another test. Click the upload button.
- Press A to go to the gameplay screen.
- The computer is still perfect, but if you miss the ball with your paddle, it goes off the side of the screen and never comes back.
- Click upload to test again.
- This complete checkpoint can be found in the checkpoints folder (6)

---
###Step 7: Adjusting the AI

- The AI is currently impossible to beat (literally, it is perfect).
- We need to change that.
- Let's start by looking at the code for the computer's y movements. "if (bally < computery) {..."
- We're going to add an if statement above this section, but below the paddle creator, but it will end after the two if statements for the paddle's y coordinate

```c++
    if (ballx > 95 ||           //If the ball is close to the right side of the screen 
      random(0, 10) == 1) {     //Or a randomly selected number is 1

      //[[EXISTING COMPUTER PADDLE MOVEMENT CODE]]

    }
```
        
- We also want to move the paddles to the middle.
- Find the playery and computer y variables
- Set their values to 27
- This should make the computer less capable.
- It still needs some work, though. We will come back to this.
- Time to test again. Click the upload button.
- Press A to go to the gameplay screen.
- When the ball goes off the screen, click upload to start again.
- This complete checkpoint can be found in the checkpoints folder (7)
                
---
###Step 8: Scoring

- Time to add scoring. Add variables for player and computer scores

```c++
    int playerscore = 0;        //Creates player score and sets to 0
    int computerscore = 0;      //Creates computer score and sets to 0
```

- Time to make some changes to the old "Gameplay Screen" text.
- Replace setCursor and print with the following

```c++
    arduboy.setCursor(20, 0);       //Moves the cursor
    arduboy.print(playerscore);     //Displays the payer's current score
    arduboy.setCursor 101, 0);      //Moves the cursor
    arduboy.print(computerscore);   //Displays the computer's current score
```

- Now it is time to deterimine when a point should be added
- At the bottom of Case 1, just before the break add the following:

```c++
    if (ballx < -10) {                      //If the ball goes off the left side of the screen
      ballx = 63;                           //Put the ball back in the middle
      computerscore = computerscore + 1;    //Add one to the computer's score
    }
    if (ballx > 130) {                      //If the ball goes off the right side of the screen
      ballx = 63;                           //Put the ball back in the middle
      playerscore = playerscore + 1;        //Add one to the player's score
    }
```

- The game will go on forever this way.
- Adding a win/lose condition allows us to access those screens again.
- Remove the commented out check to see if A has been pressed to change screens
- Replace with:

```c++
    if (playerscore == 5) {     //If the player's score is 5
      gamestate = 2;            //Change to the win screen
    } 
    if (computerscore == 5) {   //If the computer's score is 5
      gamestate = 3;            //Change to the win screen
    }
```

- Lastly, in case 2 set the gamestate change to 0 instead of 3
&nbsp;
- Time to test! Click the upload button.
- This is almost a complete game now.
- When you get to the win or lose screens, press A to start over.
- This will still move quickly and the points will not reset.
- This complete checkpoint can be found in the checkpoints folder (8)

---
###Step 9: Creating a new ball and resetting the game

- The reset function is the last thing we need to do before having a fully functional game and applying some polish.
&nbsp;
- Start by declaring a method/function between the variables and setup.
- The code should look like this:
```c++
    void resetgame() {      //This is the name of the the function we will call later
      ballx = 63;           //Puts the ball back in the middle
      playerscore = 0;      //Reset the player's score
      computerscore = 0;    //Reset the computer's score
    } 
```

- Now we just need to call the method/function from the win/lose gamestates after the A button has been pressed, but before the screen changes.
- Add the following in both places:

```c++
    resetgame();    //Calls the resetgame method
```

- Let's test our game again. Click the upload button.
- This is a complete game now.
- When you get to the win or lose screens, press A to start over.
- This will reset properly now.
- This complete checkpoint can be found in the checkpoints folder (9)

---
###Step 10: Final Quality Improvements

- Let's start by improving the win/lose screens
- Add a counter variable to make text flash

```c++    
    int counter = 0;    //Frame counter
``` 

- Go to case 2 and replace the setCursor and print with the following:

```c++
    arduboy.setCursor(45, 9);                   //Moves the cursor
    arduboy.print("You Won");                   //Displays "Win Screen"
    arduboy.setCursor(30, 25);                  //Moves the cursor
    arduboy.print("Score - ");                  //Displays the score (4 lines)
    arduboy.print(playerscore);
    arduboy.print(" / ");
    arduboy.print(computerscore);               
    counter = counter + 1;                      //Counts a frame;
    if (counter < 60) {                         //If fewer than 60 frames have passed
      arduboy.setCursor(0, 50);                 //Moves the cursor
      arduboy.print("Press A to play again");   //Tells the user what to do
    }
    if (counter >= 120) {                       //If more than 120 frames have passed
      counter = 0;                              //Set the counter back to 0 (display nothing)
    }
```
        
- Repeat the same thing for case 3 but replace "You Won" with "You Lost"
- You also need to change the first setCursor to 40,9
&nbsp;
- Now we need to make the title screen look good
- In our variables, we need to make a 4x4 paintbrush

```c++
    int drawx = 16;     //This is our paintbrush
    int drawy = 16;     //Part 2
```

- More importantly, we have to create our instructions for which spots to fill

```c++
    int titlearray [5][25] {{1,1,1,1,0,0,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1}, //Art
                            {1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,0,0,0},
                            {1,1,1,1,0,0,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1},
                            {1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1},
                            {1,1,0,0,0,0,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,0}};
```

- Go to case 0 and replace the setCursor and print with the following:

```c++
    for(int i = 0; i < 25; i++) {                                       //Build a counter for X
      arduboy.setCursor(drawx, drawy);                                  // Move the cursor based on math
      for(int n = 0; n < 5; n++) {                                      //Build a counter for Y
        if(titlearray[n][i] == 1) {                                     //Check to see if the counters match 1
          arduboy.fillRect(drawx, drawy, ballsize, ballsize, WHITE);    //Paint if so
        }
        drawy = drawy + 4;                                              //Move the cursor down 4
      }
      drawx = drawx + 4;                                                //Move the cursor right 4
      drawy = 16;                                                       //Reset the cursor up
    }
    drawx = 16;                                                         //Reset the cursor left
```

- Two last touches. We're going to steal from cases 2 and 3.
- Place this beneath the piece we just made:

```c++
    counter = counter + 1;                  //Counts a frame;
    if (counter < 60) {                     //If fewer than 60 frames have passed
      arduboy.setCursor(10, 50);            //Moves the cursor
      arduboy.print("Press A to play");     //Tells the user what to do
    }
    if (counter >= 120) {                   //If more than 120 frames have passed
      counter = 0;                          //Set the counter back to 0 (display nothing)
    }
```

- Give yourself credit by adding the following at the top of case0:
- Above the foor loops for the painter, but below "case 0:"

```c++
    arduboy.setCursor(0,0);             //Move the cursor
    arduboy.print("A game by me!");     //Give your self credit (20 char max)
```
- Go ahead and build and play one more time!
- This final checkpoint can be found in the checkpoionts folder (10)
- Congratulations! You've made it to the end. 
- There is a lot more to learn! Come back and visit us for 8th and 10th grade days.
- Most importantly, come take our classes in 11th and 12th grade.
&nbsp;
- Have a great rest of your summer!
&nbsp;
- Mr. Dockett and Mr. Mullen
