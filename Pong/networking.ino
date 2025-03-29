
// Setup the Arduino as an Access Point and start the server.
void connectionSetup() {
  Serial.println("Setting up WiFi as Access Point...");
  WiFi.beginAP(ssid, pass);
  delay(10000);  // Allow time for the AP to initialize

  IPAddress ip = WiFi.localIP();
  Serial.print("Arduino Server IP Address: ");
  Serial.println(ip);

  server.begin();
}

// Waits for a client connection that matches the desired IP.
// The playerName parameter is used for logging purposes.
WiFiClient waitForClientWithIP(const IPAddress &desiredIP, const char *playerName) {
  WiFiClient client;
  Serial.print("Waiting for ");
  Serial.print(playerName);
  Serial.print(" with IP: ");
  Serial.println(desiredIP);

  while (true) {
    Serial.print(".");
    client = server.available();
    if (client) {
      IPAddress remoteIP = client.remoteIP();
      Serial.print("New connection from: ");
      Serial.println(remoteIP);
      if (remoteIP == desiredIP) {
        Serial.print(playerName);
        Serial.println(" connected!");
        return client;
      } else {
        Serial.print("Connection from ");
        Serial.print(remoteIP);
        Serial.println(" does not match desired IP.");
      }
    }
    delay(100);
  }
}

// Checks for incoming data from both players.
void checkServer() {
  // Check for data from Player 1
  if (Player_1 && Player_1.connected() && Player_1.available()) {
    char data_1 = Player_1.read();

    player1In = (int)data_1;

    Serial.print("Player 1 data (");
    Serial.print(Player_1.remoteIP());
    Serial.print("): ");
    Serial.println(data_1);
  }

  // Check for data from Player 2
  if (Player_2 && Player_2.connected() && Player_2.available() && !SinglePlayer) {
    char data_2 = Player_2.read();

    player2In = (int)data_2;

    Serial.print("Player 2 data (");
    Serial.print(Player_2.remoteIP());
    Serial.print("): ");
    Serial.println(data_2);
  }
}

// Ensures that the client for a given player is still connected.
// If the connection is lost, it waits for a reconnection from the same desired IP.
void ensureClientConnected(WiFiClient &client, const IPAddress &desiredIP, const char *playerName) {
  if (!client.connected()) {
    Serial.print(playerName);
    Serial.println(" disconnected. Waiting for reconnection...");
    client = waitForClientWithIP(desiredIP, playerName);
  }
}

void networkingSetup() {

  Serial.println("Arduino Server Started");
  Serial.println("Setting up WiFi...");

  connectionSetup();

  // Wait for Player 1 (IP 192.168.4.2)
  Player_1 = waitForClientWithIP(desiredPlayer1IP, "Player 1");
  Serial.print("Player 1 connected with IP: ");
  Serial.println(Player_1.remoteIP());

  // Wait for Player 2 (IP 192.168.4.3)
  if (!SinglePlayer) {
    Player_2 = waitForClientWithIP(desiredPlayer2IP, "Player 2");
    Serial.print("Player 2 connected with IP: ");
    Serial.println(Player_2.remoteIP());

    Serial.println("Both players connected. Ready to receive data.");
  } else
    Serial.println("All players connected. Ready to receive data.");
}