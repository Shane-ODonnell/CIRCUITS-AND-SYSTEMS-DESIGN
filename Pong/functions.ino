
void drawPong(int x, int y) {
  //code that draws the paddle in based on where the bottom right corner should be
  display.fillRect(x, y, playerW, playerH, SSD1306_WHITE);
}

void movementPlayer() {
  int temp = analogRead(stickY);
  int m = 0;
  if (temp > 550 && playerY < height) {
    m = 1;
  } else if (temp < 450 && playerY > playerH) {
    m = -1;
  }

  playerY = playerY + m * vy;
}

void drawMap() {
  //this will likely just be a line down the middle and at the bot and player x positions
  //display.drawLine(playerX, 0, playerX, height, SSD1306_WHITE);
  //display.drawLine(botX, 0, botX, height, SSD1306_WHITE);

  display.drawLine(width / 2, 0, width / 2, height, SSD1306_WHITE);
}

void setupPlayers() {
  playerH = floor(width / 17.5);
  playerW = floor(0.5 * playerH);

  playerX = floor(width / 35);
  botX = width - playerX;

  playerY = floor((height + playerH) / 2);
  botY = playerY;
}

void showPlayers() {
  drawPong(playerX, playerY - playerH);
  drawPong(botX - playerW, botY - playerH);
}

bool collided() {
  int ballX = ball.getX();
  int ballY = ball.getY();
  int rad = ball.r;  // store the current positon of the ball

  if ((ballX + rad >= botX - playerW) && (ballX < botX)) {  //if the ball is in or at the x position for the Bot paddle
    if (ballY <= botY && ballY >= botY - playerH) {         //if the ball is in or at the y positon of the bot paddle
      return true;
    }
  } else if (ballX + rad >= playerX && ballX - rad <= playerX + playerW) {  // if the ball is in or at the x position of the player paddle
    if (ballY <= playerY && ballY >= playerY - playerH) {                   // if the ball is in or at the y position of the player paddle
      return true;
    }
  }

  return false;  // ball coords are not the same as or in contact with the coords of either paddle, no collision
}

void movementBot() {
  int targetY, m;
  int curr = botY;

  int Y = ball.getY();
  int X = ball.getX();
  int slope = ball.getSlope();

  //find targetY

  if (!ballInPlay) {
    // if the ball isnt in play move to center
    targetY = floor((height + playerH) / 2);
  } else {

    targetY = slope * (botX - X - playerW) + Y + floor(playerH / 2);  //find the expected position of the ball using y = m(x2 - x1) + y2

    //if target is off frame, set it to be the nearest extreme of the frame
    if (targetY < playerH) {
      targetY = playerH;
    } else if (targetY > height) {
      targetY = height;
    }
  }

  //now we have the desired y position of the bot (adjusted so that the ball will strike the centre of the paddel)
  //now move the pong up or down

  if (abs(targetY - curr) < vy) {
    m = 0;  //already at target
  } else if (targetY > curr) {
    m = 1;  //go up
  } else {
    m = -1;  //go down
  }

  //now determine which way you need to go to reach the target

  if (botY >= 0 && botY <= height) {
    botY = botY + m * vy;
  } else {
    if (botY >= height) {
      botY = height - 1;
    } else {
      botY = 0;
    }
  }
}

void spawnBall() {
  // this will likely be an interrupt function which runs when the joystick is clicked
  if (!ballInPlay) {
    ball.spawn(floor(playerY - 0.5 * playerH));
    ballInPlay = true;
  }
}