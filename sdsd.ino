#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "rupesh";
const char* password = "123456789";

ESP8266WebServer server(80);

int ledPin = D2; // Define the GPIO pin to which the LED is connected

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Initialize LED as off

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, []() {
    String html = "<html><body>";
    html += "<h1>LED Status: ";
    html += (digitalRead(ledPin) == HIGH) ? "On" : "Off";
    html += "</h1></body></html>";
    server.send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
