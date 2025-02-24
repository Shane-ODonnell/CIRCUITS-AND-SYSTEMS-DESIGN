/*
  AS OF NOW The entire game framework/ implementation is done or should in theory at least function

  What's missing? 
  well any functin labelled //TODO still needs to be filled in, likely because it has to do with the games' visuals
  some variables like width and height need to be set so that the functions that handle the proportions of everything will work
  variables like vy need to be apporpriately set but that will require playtests
  need to add anything related to using a screen basically or the input device
  
*/


#include <iostream>
#include "Ball.h"
using namespace std;

int playerH;  //Height of the paddles/pongs
int playerW;  //Width of the paddles/pongs
int playerX, botX; //X position for player 
int playerY, botY; //Pong y positions

int vy = 4;  // TODO calibrate an appropraite vy
bool ballInPlay = false;

int width = 128;
int height = 64;  // TEMP width is a placeholder till I have the neccesary code for the screen //TODO

Ball ball;  //initialise an instance of the ball class (initialise a ball)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  setupPlayers();
  ball.start(playerX + playerW, vy, width, height);
  drawMap();
  //Serial.println(ball.getX());  // test line
}

void loop() {
  int ballX = ball.getX();
  bool collision = false;

  drawMap();

  movementPlayer();
  movementBot();

  showPlayers();

  collision = collided();

  if (ballInPlay) {
    ball.update(collision);
    if (ballX >= width || ballX <= 0) {  // if the ball leaves frame
      ballInPlay = false;                //set play to false so that ball can be "spawned"
      ball.active = false;
    }
  }
}

void spawnBall() {
  // this will likely be an interrupt function which runs when the joystick is clicked
  if (!ballInPlay) {
    ball.spawn(floor(playerY - 0.5 * playerH));
    ballInPlay = true;
  }
}  // TODO (function finished but needs to be used)
