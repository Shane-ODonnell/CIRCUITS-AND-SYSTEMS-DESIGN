
class Ball {
public:
  int r = 20;  //ball size
  int x = 60;  //intial x position
  int y, dy, dx;
  int count = 2;  //initial x velocity
  bool active = false;

  int width, height; // temp to be repllaced later

  void start(int X, int Y, int vy, int w, int h) {
    x = X;
    y = Y;
    dy = vy;
    dx = 2;
    width = w;
    height = h;
  }  //this will set the x&y of the ball, and the velocities basically the constructor

  void show() {  //draw the ball
    if (active) {
      //show ball at x,y with radius r
    }
  }

  void update(boolean collided) {

    if (collided) {  // if the ball hits a paddle change direction and speed up
      count++;       //count the number of collisions
      dx = floor(pow(-1, count) * count);
      //increase the pixels per frame by 1 and change the direction
    }

    //update the position of the ball
    x = x + dx;
    y = y + dy;

    //if ball hits the top or bottom of screen, bounce!
    if (y > height || y < 0) {
      dy = dy * -1;  //invert the slope to bounce next frame
    }

    show();
  }

  int getX() {
    return x;
  }

  int getY() {
    return y;
  }

  int getSlope() {
    if (dx != 0) {
      return floor(dy / dx);
    } else
      return 0;
  }
};  // close ball class
