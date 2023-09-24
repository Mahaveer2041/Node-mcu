#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define ledPin D0
const char *ssid = "RamanLab";
const char *password = "RaMaN@2020";

// GPIO2 (D2) on NodeMCU

ESP8266WebServer server(80);
void handleRoot() {
  String html = "<html><body>";
  html += "<h1>NodeMCU LED Control</h1>";
  html += "<p><a href='/on'>Turn On LED</a></p>";
  html += "<p><a href='/off'>Turn Off LED</a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/plain", "LED is ON");
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/plain", "LED is OFF");
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  

  // Define web server routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);

  server.begin();
}



void loop() {
  server.handleClient();
}
