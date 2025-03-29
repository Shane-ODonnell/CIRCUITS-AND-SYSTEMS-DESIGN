/*
TODO LIST
  Now I have a player and bot showing on the screen. the player can easily move up and down within the bounds of the screen, and there is a line down the middlle for set dressing.

  I currently have no notes for what needs improving on this project!!!
  
  Added new feature: when spawned the ball will move in the same direction that the player last moved in

  my screen seems to be fully dead pixels at the bottom and fully yellow at the top.
  the code at the moment is a bit of a mess which isnt helping either.
*/
#include "screen.h"
#include "Ball.h"
#include <WiFiS3.h>

// WiFi details
char ssid[] = "giveTeam1fullmarks";
char pass[] = "giveTeam1fullmarks";

// Create a WiFi server on port 5200
WiFiServer server(5200);

// Declare clients for two players
WiFiClient Player_1;
WiFiClient Player_2;

// Define desired IP addresses for each player
IPAddress desiredPlayer1IP(192, 168, 4, 2);
IPAddress desiredPlayer2IP(192, 168, 4, 3);


int stickY = A1;    //pin that takes in Y value of joyStick
int clickPin = 2;   //stick that takes in stickClicks
int stickY2 = A2;   //pin that takes in Y value of joyStick
int clickPin2 = 3;  //stick that takes in stickClicks

int playerH;        //Height of the paddles/pongs
int playerW;        //Width of the paddles/pongs
int playerX, botX;  //X position for player
int playerY, botY;  //Pong y positions

int vy = 2;
int d = 1;  // d is for direction the ball will spawn in
bool ballInPlay = false;
bool clicked = false;
bool SinglePlayer = true;

int width = 128;
int height = 64;

int player1In;
int player2In;
//***************************************************************************************

void joystickClick() {
  clicked = true;
}  //interrupt function for click detection

void setup() {

  Serial.begin(9600);

  networkingSetup();

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

  checkServer();

  if (player1In == 2 || player2In == 2) {
    clicked == true;
  }

  display.clearDisplay();  // Clear the screen ONCE per loop
  int ballX = ball.getX();
  bool collision = false;

  if (clicked) {
    spawnBall();
    clicked = false;
  }


  movementPlayer();  //update playerY every second loop

  if (SinglePlayer) {
    movementBot();  //update botY
    ensureClientConnected(Player_1, desiredPlayer1IP, "Player 1");
  } else {
    movementPlayer2();
    ensureClientConnected(Player_2, desiredPlayer2IP, "Player 2");
  }

  /* 
    the player was moving to fast to be anyway controlled with precison. 
    I couldnt make vy a fraction because theres no moving half pixels
    the velocity is measured in pixels per frame
    so if I cant make it travel 0.5 pixels every frame
    I made it travel 1 pixel but only every second frame 
    I can have my slower player (0,5 pixel/frame = 1 pixel/ 2 frames) !!!


    ALSO by making the bot slower than the ball it makes for a bot that can actually be beaten!
  */

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
