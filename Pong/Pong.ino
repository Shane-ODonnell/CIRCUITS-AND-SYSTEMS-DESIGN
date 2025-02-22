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

Ball ball;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  setupPlayers();

  Serial.println(ball.getX()); // test line

}

void loop() {
  // put your main code here, to run repeatedly:

}


void setupPlayers(){
  playerH = floor(width/17.5);
  playerW = floor(0.5* playerH);

  playerX = floor(width / 35);
  botX = width - playerX;

  playerY = floor( (height + playerH) / 2 );
  botY = playerY;
}