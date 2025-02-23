
class Ball {
public:
  int r;  //ball size
  int x, y; // ball position
  int dy, dx; // ball velocity components
  int count = 2;  //count of collisions for accelerating the ball
  bool active = false;

  int width, height; // temp to be replaced later //TODO

  void start(int X, int vy, int W, int H){
    x = X + r;
    width = W;
    height = H;
    dy = vy;
    r = floor(width/8);
  } // constructor may need some work
  
  void spawn(int Y) {
    y = Y;
    dx = 2;
    count = 2;
    active = true;
  }  //spawn ball at desired y value 

  void show() {  //draw the ball
    if (active) {
      //show ball at x,y with radius r
    }
  }//TODO

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
