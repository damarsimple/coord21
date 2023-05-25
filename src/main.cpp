#include <Arduino.h>
#include <Servo.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

const char *ssid = "TP-Link_81F8";
const char *password = "123456789";

AsyncWebServer server(80);
Servo servo;

void setup()
{
  servo.attach(GPIO_NUM_32);

  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA); // Optional
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println(WiFi.localIP());

  // start server

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Hello, world"); });

  server.on("/servo", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
              int angle = request->getParam(0)->value().toInt();

  

              servo.write(angle);

              Serial.println(angle);

              request->send(200, "text/plain", "OK!"); });

  server.begin();
}

void loop()
{
}