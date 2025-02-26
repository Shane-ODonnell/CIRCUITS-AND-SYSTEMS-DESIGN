/*
TODO LIST
  Now I have a player and bot showing on the screen. the player can easily move up and down within the bounds of the screen, and there is a line down the middlle for set dressing.

  I currently have no notes for what needs improving on this project!!!

  my screen seems to be fully dead pixels at the bottom and fully yellow at the top.
  the code at the moment is a bit of a mess which isnt helping either.
*/

#include <iostream>
#include "screen.h"
#include "Ball.h"

int stickY = A1;   //pin that takes in Y value of joyStick
int clickPin = 2;  //stick that takes in stickClicks

int playerH;        //Height of the paddles/pongs
int playerW;        //Width of the paddles/pongs
int playerX, botX;  //X position for player
int playerY, botY;  //Pong y positions

int vy = 1;
bool ballInPlay = false;
bool clicked = false;

int width = 128;
int height = 32;

//***************************************************************************************

void joystickClick() {
  clicked = true;
}  //interrupt function for click detection

void setup() {

  Serial.begin(9600);

  setupOLED();     // screen.h
  setupPlayers();  //intialise global variables

  pinMode(stickY, INPUT);
  pinMode(clickPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(clickPin), joystickClick, CHANGE);

  ball.start(playerX + playerW, vy, width, height, display);  //give ball class all the information it needs.

  Serial.println("radius is: " + ball.r);
  drawMap();
  //Serial.println(ball.getX());  // test line
}

void loop() {
  display.clearDisplay();  // Clear the screen ONCE per loop
  int ballX = ball.getX();
  bool collision = false;

  if (clicked) {
    spawnBall();
    clicked = false;
  }

  movementPlayer();  //updare playerY
  movementBot();     //update botY


  drawMap();
  showPlayers();

  collision = collided();  //check if the ball has collided with the pongs

  if (ballInPlay) {

    if (ballX >= width || ballX <= 0) {  // if the ball leaves frame
      ballInPlay = false;                //set play to false so that ball can be "spawned"
      ball.active = false;               //dont show ball
    }

    ball.update(collision);  //update postion of and show ball
  }

  display.display();  // Update the screen
}
