
class Cursor {
public:

  int size = 3;  // Size of cursor

  int x_position = 64;  // X Position of the cursor, initialised to the centre of the screen
  int y_position = 32;  // Y Position of the cursor, initialised to the centre of the screen
  bool Animation = false; // Are we playing the cursor animation 
  int AnimationFrame; // The frame of the animation 

  int width, height;         // Screen dimensions
  Adafruit_SSD1306 display;  // Initialise the display

  void start(int W, int H, Adafruit_SSD1306 screen) {
    width = W;
    height = H;
    display = screen;
  }


  // I am *almost* certain this is not used and I just put all of the functions in the functions.ino file
  drawCursor(int size, int x_position, int y_position) {
    display.fillCircle(50, 50, size, SSD1306_WHITE);
  }

};              // close cursor class
Cursor cursor;  //initialise an instance of the ball class (initialise a ball)
