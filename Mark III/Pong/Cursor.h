
class Cursor {
public:
  int x, y, r;
  int vy, vx;
  int width, height;
  int xPin, yPin;

  Adafruit_SSD1306 display;

  void start(int W, int H, Adafruit_SSD1306 screen, int pinX, int pinY) {
    width = W;
    height = H;
    display = screen;
    xPin = pinX;
  }

  void movement() {
    int stickY = analogRead(2);
    int stickX = analogRead(1);
    int m = 0;  //Directional multiplier, used to modify the velocity to be positvie/negative or Zero

    if (stickY > 550 && y < height) {    //if stick is is being pushed up and there is screen space to move up
      m = 1;                             //|set direction to be positive
      d = m;                             // set d to be current m for ball spawn purposes
    } else if (stickY < 450 && y > r) {  //if stick is is being pushed down and there is screen space to move down
      m = -1;                            //|set direction to be negative
      d = m;
    }
    
    y = y + m * vy;

    if (stickX > 550 && x < height) {    //if stick is is being pushed up and there is screen space to move up
      m = 1;                             //|set direction to be positive
      d = m;                             // set d to be current m for ball spawn purposes
    } else if (stickX < 450 && x > r) {  //if stick is is being pushed down and there is screen space to move down
      m = -1;                            //|set direction to be negative
      d = m;
    }


    x = x + m * vx;
    //have player move "vy" pixels in the "m" direction
  }

  void show();
}