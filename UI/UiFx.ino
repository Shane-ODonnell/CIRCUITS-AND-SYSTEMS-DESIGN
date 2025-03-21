int UPPER_DEADZONE = 750;  // The amount the joystick must be moved to increase coordinates
int LOWER_DEADZONE = 350;  // The amount the joystick must be moved to decrease coordinates
int SCREEN_PADDING = 7;    // This is how close the cursor is able to get to the "edge" of the screen

////////////////////////////////// DOT OBJECT USED FOR "SNOW FALLING" ANIMATIONS ///////////////////////////////
Dot dot1(1, 1);
Dot dot2(9, 12);
Dot dot3(16, 31);
Dot dot4(25, 16);

Dot dot5(3, -12);
Dot dot6(12, -15);
Dot dot7(18, -45);
Dot dot8(35, -24);

Dot dot9(91, 11);
Dot dot10(97, 21);
Dot dot11(112, 51);
Dot dot12(120, 31);

Dot dot13(93, -24);
Dot dot14(99, -36);
Dot dot15(105, -12);
Dot dot16(123, -57);
/*
  Dot dot17(45, 11);
  Dot dot18(57, 21);
  Dot dot19(76, 51);
  Dot dot20(85, 31);

  Dot dot21(75, -24);
  Dot dot22(86, -36);
  Dot dot23(42, -12);
  Dot dot24(58, -57);
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////


// First we initialise the cursor to appear at the centre of the screen
void initialiseCursor() {
  display.fillCircle(width / 2, height / 2, 1, SSD1306_WHITE);
  display.display();  // Update the screen
}


// Now we want to update the position of the cursor based on the user input
void drawCursor() {
  // First we need to find what position to draw the cursor at
  updateCursorPosition();
  // Update the size of the cursor depending on whether or not the joystick is being clicked
  updateCursorSize();
  display.fillCircle(cursor.x_position, cursor.y_position, cursor.size, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
  display.display();                                                                     // Update the screen
  cursor.size = 3;
}



void getCursorX() {
  int xPosition = analogRead(1);
  // We check to see if the joystick is outside of the DEADZONE, if it is, we can update accordingly
  if (xPosition > UPPER_DEADZONE) {
    if (cursor.x_position > width - 10) {
      return;
    }
    cursor.x_position = cursor.x_position + 3;
  } else if (xPosition < LOWER_DEADZONE) {
    if (cursor.x_position < 10) {
      return;
    }
    cursor.x_position = cursor.x_position - 3;
  } else {
    return;
  }
}




int getCursorY() {
  int yPosition = analogRead(2);
  // We check to see if the joystick is outside of the DEADZONE, if it is, we update accordingly
  if (yPosition > UPPER_DEADZONE) {

    // Check to see if we have hit the top of the screen
    if (cursor.y_position > height - 10) {
      return;
    }
    cursor.y_position = cursor.y_position + 3;
  } else if (yPosition < LOWER_DEADZONE) {

    // Check to see if we have hit the bottom of the screen
    if (cursor.y_position < 10) {
      return;
    }
    cursor.y_position = cursor.y_position - 3;
  } else {
    return;
  }
}


void updateCursorPosition() {
  getCursorX();  // Get the correct X position
  getCursorY();  // Get the correct Y position
}


void updateCursorSize() {
  if (clicked) {
    // If clicked play the click animation
    clickAnimation();
    return;
  }
}



void clickAnimation() {

  Serial.println(cursor.AnimationFrame);

  // First 3 frames of the animation
  if (cursor.AnimationFrame <= 3) {
    cursor.size = 2;
    display.fillCircle(cursor.x_position + 8, cursor.y_position + 8, 3, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
    display.fillCircle(cursor.x_position - 8, cursor.y_position + 8, 3, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
    display.fillCircle(cursor.x_position + 8, cursor.y_position - 8, 3, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
    display.fillCircle(cursor.x_position - 8, cursor.y_position - 8, 3, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
    cursor.AnimationFrame++;
    return;
  }
  // Second three frames of the animation
  if (cursor.AnimationFrame >= 3 && cursor.AnimationFrame <= 6) {
    display.fillCircle(cursor.x_position + 12, cursor.y_position + 12, 2, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
    display.fillCircle(cursor.x_position - 12, cursor.y_position + 12, 2, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
    display.fillCircle(cursor.x_position + 12, cursor.y_position - 12, 2, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
    display.fillCircle(cursor.x_position - 12, cursor.y_position - 12, 2, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
    cursor.AnimationFrame++;
    return;
  }
  // Last three frames of the animation
  if (cursor.AnimationFrame >= 6 && cursor.AnimationFrame <= 9) {
    display.fillCircle(cursor.x_position + 20, cursor.y_position + 20, 1, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
    display.fillCircle(cursor.x_position - 20, cursor.y_position + 20, 1, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
    display.fillCircle(cursor.x_position + 20, cursor.y_position - 20, 1, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
    display.fillCircle(cursor.x_position - 20, cursor.y_position - 20, 1, SSD1306_WHITE);  // We draw the cursor at the correct coordiantes
    cursor.AnimationFrame++;
    return;
  }

  // If we reach the end of the animation we reset the click variable and set the frame back to 0
  else {
    clicked = !clicked;
    cursor.Animation = false;
    cursor.AnimationFrame = 0;
    return;
  }
}


// This just draws a nice clean border around the edge of the screen
void menuBorder() {
  display.drawLine(0, 0, width - 1, 0, SSD1306_WHITE);
  display.drawLine(0, 0, 0, height - 1, SSD1306_WHITE);
  display.drawLine(width - 1, height - 1, width - 1, 0, SSD1306_WHITE);
  display.drawLine(width - 1, height - 1, 0, height - 1, SSD1306_WHITE);
}

// Draws the single player button
void singlePlayerButton() {
  display.drawRoundRect(menu.single_button_x_position, menu.single_button_y_position, menu.single_button_width, menu.single_button_height, menu.single_button_radius, SSD1306_WHITE);
  display.fillRoundRect(menu.single_button_x_position + menu.single_icon_x_offset, menu.single_button_y_position + menu.single_icon_y_offset, 3, 10, 1, SSD1306_WHITE);
}

// Draws the multiplayer button
void multiPlayerButton() {
  display.drawRoundRect(menu.multi_button_x_position, menu.multi_button_y_position, menu.multi_button_width, menu.multi_button_height, menu.multi_button_radius, SSD1306_WHITE);
  display.fillRoundRect(menu.single_button_x_position + menu.multi_icon_x_offset, menu.single_button_y_position + menu.multi_icon_y_offset, 3, 10, 1, SSD1306_WHITE);
  display.fillRoundRect(menu.single_button_x_position + menu.multi_icon_x_offset + 4, menu.single_button_y_position + menu.multi_icon_y_offset, 3, 10, 1, SSD1306_WHITE);
}

// Draw the settings button
void settingsButton() {
  display.drawRoundRect(menu.settings_x, menu.settings_y, menu.settings_width, menu.settings_height, menu.settings_radius, SSD1306_WHITE);
}

// Draws the Main Menu
void drawMenu() {
  // Play the background animation
  menuAnimation();
  // Draw the settings button
  settingsButton();
  // Draw the border
  menuBorder();
  // Draw the single player button
  singlePlayerButton();
  // Draw the multiplayer button
  multiPlayerButton();
}



// Run through a bunch of frames and change the positions of the dot object accordingly
void menuAnimation() {
  if (menu.frame < 109) {
    drawDots();
    menu.frame = menu.frame + 2;
  } else {
    drawDots();
    menu.frame = 0;
  }
  return;
}


// Draw the dots at their coordinates (hell no)
void drawDots() {
  display.fillCircle(dot1.x_position, getDotCoord(dot1), 1, SSD1306_WHITE);
  display.fillCircle(dot2.x_position, getDotCoord(dot2), 1, SSD1306_WHITE);
  display.fillCircle(dot3.x_position, getDotCoord(dot3), 2, SSD1306_WHITE);
  display.fillCircle(dot4.x_position, getDotCoord(dot4), 1, SSD1306_WHITE);

  display.fillCircle(dot5.x_position, getDotCoord(dot5), 1, SSD1306_WHITE);
  display.fillCircle(dot6.x_position, getDotCoord(dot6), 1, SSD1306_WHITE);
  display.fillCircle(dot7.x_position, getDotCoord(dot7), 2, SSD1306_WHITE);
  display.fillCircle(dot8.x_position, getDotCoord(dot8), 1, SSD1306_WHITE);

  display.fillCircle(dot9.x_position, getDotCoord(dot9), 1, SSD1306_WHITE);
  display.fillCircle(dot10.x_position, getDotCoord(dot10), 1, SSD1306_WHITE);
  display.fillCircle(dot11.x_position, getDotCoord(dot11), 1, SSD1306_WHITE);
  display.fillCircle(dot12.x_position, getDotCoord(dot12), 1, SSD1306_WHITE);

  display.fillCircle(dot13.x_position, getDotCoord(dot13), 1, SSD1306_WHITE);
  display.fillCircle(dot14.x_position, getDotCoord(dot14), 2, SSD1306_WHITE);
  display.fillCircle(dot15.x_position, getDotCoord(dot15), 1, SSD1306_WHITE);
  display.fillCircle(dot16.x_position, getDotCoord(dot16), 1, SSD1306_WHITE);
  /*
  display.fillCircle(dot9.x_position, getDotCoord(dot17), 1, SSD1306_WHITE);
  display.fillCircle(dot10.x_position, getDotCoord(dot18), 1, SSD1306_WHITE);
  display.fillCircle(dot11.x_position, getDotCoord(dot19), 1, SSD1306_WHITE);
  display.fillCircle(dot12.x_position, getDotCoord(dot20), 1, SSD1306_WHITE);

  display.fillCircle(dot13.x_position, getDotCoord(dot21), 1, SSD1306_WHITE);
  display.fillCircle(dot14.x_position, getDotCoord(dot22), 2, SSD1306_WHITE);
  display.fillCircle(dot15.x_position, getDotCoord(dot23), 1, SSD1306_WHITE);
  display.fillCircle(dot16.x_position, getDotCoord(dot24), 1, SSD1306_WHITE);
*/
}


// If the dot goes off the screen (y > 64) reset it back to the top of the screen
int getDotCoord(Dot &dot1) {
  dot1.y_position++;
  if (dot1.y_position >= 64) {
    dot1.y_position = 0;
  }
  return dot1.y_position;
}

// Check to see if any button has been pressed
void buttonDetect() {
  if (state == 0) {
    if ((clicked) && (cursor.x_position > menu.settings_x && cursor.x_position < menu.settings_x + menu.settings_width)) {
      if (cursor.y_position > 6 && cursor.y_position < 16) {
        state = 1;
        clicked = false;
      } else if (cursor.y_position > 18 && cursor.y_position < 34) {
        //Serial.println("state set to 2");
        state = 2;
        clicked = false;
      } else if (cursor.y_position > 36 && cursor.y_position < 52) {
        state = 3;
        clicked = false;
      }
    } else return;
  } else {
    return;
  }
}



void ballstart(int X, int vy, int W, int H) {
  ball.width = W;
  ball.r = floor(ball.width / 70);
  ball.x = X + ball.r;
  ball.height = H;
  ball.dy = vy;
  ball.dx = 2;
  //ball.display = screen;
}

void show() {  //draw the ball
  if (ball.active) {
    //show ball at x,y with radius r
    display.fillCircle(ball.x, ball.y, ball.r, SSD1306_WHITE);
  }
}

void update(boolean collided) {

  if (collided) {  // if the ball hits a paddle change direction
    ball.count++;
    ball.dx = floor(pow(-1, ball.count));
  }

  //update the position of the ball
  ball.x = ball.x + ball.dx;
  ball.y = ball.y + ball.dy;

  //if ball hits the top or bottom of screen, bounce!
  if (ball.y > ball.height || ball.y < 0) {
    ball.dy = ball.dy * -1;  //invert the slope to bounce next frame
  }

  ball.show();
}