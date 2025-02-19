Welcome team.


This is currently a trimmed version of the networking from my buggy project which I would propose we use for our porject.
  this is why there are commented out variables such as speed, buggyV, targetV etc, aswell as references to functions which wont be relevant to this project like obstacleDist()

Here is how it worked.

Processing (the client/laptop) would continuously check (once per loop) to see if the buggy (server) sent anything. anything at all.

when the buggy wanted to tell Laptop something, (like the current velocity or distance travelled)
  it would first send a char to let laptop know what information to expect.
    So as an example of how this might look, if the buggy wanted to tell the buggy it had stopped for an obstacle it would send 's'
    upon receiving 's' the laptop knew to display the current velocity as 0 and flash the on screen light for obstacle.

    OR if the buggy sent 'u' (short for update) (as seen in the function sendUpdate(client)) the laptop knew it was about to receive an update to all the variables in a specific order
    so it would store the first int received as the distance travelled, then after that it would get and store the obstacleDistance, then the buggyVelocity and target velocity.

    this worked well because it made sure that all the integers being sent were stored where they were meant to be. 
      And some very simple processing functions could handle all the networking and ensure no data leaks
      
        data = buggy.readChar(); //read what the buggy sent and store it in "data"
        dataEval(data);          // Evaluate the Data we received and update global variables acordingly
        send();
        
      the above is only two lines short of the loop used in the silver challenge
      I am about to add the file containing these funtcions to the repo to help illustrate how the client side of things looked
      but basically dataEval would check which headsup it was given and then use the following function repeatedly to store everything where it needed to go 
      
          int getInteger() {
            //if we try to read in too early it'll save as -1, so keep checking until we get the actual signal
            int NUM = -1;
            while (NUM == -1) { //wait till count != -1
              NUM = buggy.read();
            }
            return NUM;
          }

**TL;DR : the networking I used for the buggy project was basically, tell the client headsup info coming your way, then throw all the info to the client.
        then the client would catch/organise all the following info into the appropriate boxes based on the provided headsup.**

sorry if I got carried away and this explanation doesnt make sense. I will happily explain in person and if you have any questions or want to see more of the code or know more of the context
just send me a text or ask in person. this is just How I propose we do the networking as it is quite effective in my experience and other groups who I helped get their networking online also liked my approach.
