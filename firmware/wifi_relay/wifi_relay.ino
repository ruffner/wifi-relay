/* ESP8266 WiFi Relay Controller
    Interface with QObject TCP class for remote control
*/

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define RELAY_PIN 2
#define SERIAL_BUF_LEN 10

#define COMMAND_IP   "ip"
#define COMMAND_ID   "id"
#define COMMAND_SSID "ssid"

#define RESPONSE_ON  "ON"
#define RESPONSE_OFF "OFF"
#define RESPONSE_ID  "WIFI RELAY"

/* Set these to your desired credentials. */
const char *ssid = "ESPap";
const char *password = "thereisnospoon";

String serialMessage = "";

ESP8266WebServer server(80);

/* BEGIN ROUTING HANDLERS */
void handleRoot() {
  server.send(200, "text/html", RESPONSE_ID);
}

void handleRelayOn() {
  //digitalWrite(RELAY_PIN, HIGH);

  byte buf[4] = {0xA0, 0x01, 0x01, 0xA2};
  Serial.write(buf, 4);
  
  server.send(200, "text/html", RESPONSE_ON);
}

void handleRelayOff() {
  //digitalWrite(RELAY_PIN, LOW);

  byte buf[4] = {0xA0, 0x01, 0x00, 0xA1};
  Serial.write(buf, 4);
  
  server.send(200, "text/html", RESPONSE_OFF);
}

void handleId() {
  server.send(200, "text/html", RESPONSE_ID);
}
/* end routing handlers */


void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  Serial.setTimeout(100);

  // setup relay pin as output, initially low
  pinMode(RELAY_PIN, OUTPUT);
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/on", handleRelayOn);
  server.on("/off", handleRelayOff);
  server.on("/id", handleId);
  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  server.handleClient();
}
