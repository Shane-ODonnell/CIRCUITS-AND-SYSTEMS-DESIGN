#include <string.h>
#include "screen.h"
#include "Ball.h"
#include "Cursor.h"
#include "menu.h"
#include "dot.h"


int firstRun = 0;
int state = 0;
int stickX = A2;

int stickY = A1;   //pin that takes in Y value of joyStick
int clickPin = 2;  //stick that takes in stickClicks

int playerH;        //Height of the paddles/pongs
int playerW;        //Width of the paddles/pongs
int playerX, botX;  //X position for player
int playerY, botY;  //Pong y positions

int vy = 2;
int d = 1;  // d is for direction the ball will spawn in
bool ballInPlay = false;
bool clicked = true;

int width = 128;
int height = 64;

//***************************************************************************************


// CHANGED JOYSTICK CLICK FOR UI - WILL PROBABLY NOT WORK FOR THE PONG GAME IF WE USE THE SAME ONE
void joystickClick() {
  clicked = !clicked;
}  //interrupt function for click detection


void setup() {

  Serial.begin(9600);

  setupOLED();     // screen.h
  setupPlayers();  //intialise global variables

  // Joystick input code
  pinMode(stickX, INPUT);
  pinMode(stickY, INPUT);
  pinMode(clickPin, INPUT_PULLUP);

  ball.start(playerX + playerW, vy, width, height, display);  //give ball class all the information it needs.

  attachInterrupt(digitalPinToInterrupt(clickPin), joystickClick, RISING);
  drawMap();
  initialiseCursor();
}


void loop() {


  //-------------------- INTRO CUTSCENE --------------------//







  //---------------- MAIN MENU ----------------//
  if (state == 0) {
    display.clearDisplay();  // Clear the screen ONCE per loop

    drawMenu();
    drawCursor();
    buttonDetect();

    display.display();
  }


  //---------------- SINGLEPLAYER ----------------//
  if (state == 1) {

    display.clearDisplay();  // Clear the screen ONCE per loop
    int ballX = ball.getX();
    bool collision = false;

    if (clicked) {
      spawnBall();
      clicked = false;
    }

    movementPlayer();  //update playerY every second loop
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


  //---------------- MULTIPLAYER ----------------//
  if (state == 2) {
    display.clearDisplay();  // Clear the screen ONCE per loop
    display.fillCircle(20, 10, 3, SSD1306_WHITE);
    display.fillCircle(10, 10, 3, SSD1306_WHITE);
    display.display();
  }



  //---------------- MISC ----------------//
  if (state == 3) {
    display.clearDisplay();  // Clear the screen ONCE per loop
    display.fillCircle(20, 10, 3, SSD1306_WHITE);
    display.fillCircle(10, 10, 3, SSD1306_WHITE);
    display.fillCircle(30, 10, 3, SSD1306_WHITE);
    display.display();
  }
}
