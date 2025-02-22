#include <iostream>
#include "Ball.h"
using namespace std;

int playerH;
int playerW;//= floor(0.5 * playerH)
int playerX, botX;
int playerY, botY;

int vy = 4;
bool ballInPlay = false;

int width, height;  // TEMP width is a placeholder till I have the neccesary code for the screen

Ball ball; //initialise an instance of the ball class (initialise a ball)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  setupPlayers();

  Serial.println(ball.getX()); // test line

}

void loop() {
  // put your main code here, to run repeatedly:

}