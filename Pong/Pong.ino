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

int stickY = A1;
int clickPin = 2;
int playerH;        //Height of the paddles/pongs
int playerW;        //Width of the paddles/pongs
int playerX, botX;  //X position for player
int playerY, botY;  //Pong y positions

int vy = 1;  // TODO calibrate an appropraite vy
bool ballInPlay = false;
bool interrupted = false;

int width = 128;
int height = 32;  // TEMP width is a placeholder till I have the neccesary code for the screen //TODO

//***************************************************************************************

void joystickClick() {
  interrupted = true;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  setupOLED();  // screen.h
  setupPlayers();

  pinMode(stickY, INPUT);
  pinMode(clickPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(clickPin), joystickClick, CHANGE);

  ball.start(playerX + playerW, vy, width, height, display);

  drawMap();
  //Serial.println(ball.getX());  // test line
}

void loop() {
  display.clearDisplay();  // Clear the screen ONCE per loop
  int ballX = ball.getX();
  bool collision = false;

  if (interrupted) {
    spawnBall();
    interrupted = false;
  }

  movementPlayer();
  movementBot();


  drawMap();
  showPlayers();

  collision = collided();

  if (ballInPlay) {

    if (ballX >= width || ballX <= 0) {  // if the ball leaves frame
      ballInPlay = false;                //set play to false so that ball can be "spawned"
      ball.active = false;
    }
    ball.update(collision);
  }

  display.display();  // Only update the screen ONCE
}
