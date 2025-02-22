
void drawPong(int x, int y) {
  //code that draws the paddle in based on where the bottom right corner should be
}  //TODO

void setupPlayers() {
  playerH = floor(width / 17.5);
  playerW = floor(0.5 * playerH);

  playerX = floor(width / 35);
  botX = width - playerX;

  playerY = floor((height + playerH) / 2);
  botY = playerY;
}

void movementPlayer() {
}  //TODO

bool collided() {
  int ballX = ball.getX();
  int ballY = ball.getY();
  int rad = ball.getR();

  if ((ballX + rad >= botX - playerW) && (ballX < botX)) {
    if (ballY <= botY && ballY >= botY - playerH) {
      return true;
    }
  } else if (ballX + rad >= playerX && ballX - rad <= playerX + playerW) {
    if (ballY <= playerY && ballY >= playerY - playerH) {
      return true;
    }
  }

  return false;
}

void movementBot() {
  int targetY, m;  // m to stpre direction
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

  if (botY <= height && botY >= playerH) {
    botY = botY + m * vy;
  } else {
    if (botY >= height) {
      botY = height - 1;
    } else {
      botY = playerH;
    }
  }
}