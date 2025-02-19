
#include <WiFiS3.h>  //import the library with all the server functions and stuff
char ssid[] = "Test";
char pass[] = "wordpass";
// set two character arrays with the Wifi and password you want to host the server on

WiFiServer Buggy(5200);  // establish an instance of class WiFiServer called Buggy

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  WiFi.begin(ssid, pass);          //give the arduino's wifi thing the network name and password
  IPAddress BOB = WiFi.localIP();  // establish an instance of class IPAddress called BOB and store the IP address that the WiFiServer is on
  Serial.println(BOB);             //print out BOB (the Ip address) on the arduino serial monitor
  Buggy.begin();                   //Tells the server to begin listening for incoming connections.
}


void loop() {
  WiFiClient laptop = Buggy.available();  //initialize a WifiClient called laptop

  sendUpdate(laptop);  //function that regularly sends data to laptop

  checkInput(laptop);  //function that checks for updates from the laptop and updates global vars accordingly

  if (laptop.connected() && follow == false) {  //the follow condition makes sure that f is only sent if we went from not following to following
    laptop.write("f");                          // let laptop know we are in follow mode
    follow = true;                              // udate follow so we dont send f in two concequtive loops
  }
   else {

    if (laptop.connected() && follow == true) {
      laptop.write("n");
      follow = false;
    }
  }
}
