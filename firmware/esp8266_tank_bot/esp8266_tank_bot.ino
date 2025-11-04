/*
  ESP8266 Tank Bot — basit HTTP kontrol:
  /move?dir=fwd|back|left|right|stop&spd=0..1023
  Örn: http://<ip>/move?dir=fwd&spd=700
*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "config.h"

ESP8266WebServer server(80);
uint16_t speedPWM = DEFAULT_PWM;

void setMotors(int in1, int in2, int in3, int in4, uint16_t leftPWM, uint16_t rightPWM) {
  digitalWrite(IN1, in1); digitalWrite(IN2, in2);
  digitalWrite(IN3, in3); digitalWrite(IN4, in4);
  analogWrite(EN_LEFT, leftPWM);
  analogWrite(EN_RIGHT, rightPWM);
}

void stopMotors() { setMotors(0,0,0,0,0,0); }

void fwd()   { setMotors(1,0,1,0, speedPWM, speedPWM); }
void back()  { setMotors(0,1,0,1, speedPWM, speedPWM); }
void left()  { setMotors(0,1,1,0, speedPWM, speedPWM); } // sol geri, sağ ileri
void right() { setMotors(1,0,0,1, speedPWM, speedPWM); }

void handleMove() {
  String dir = server.hasArg("dir") ? server.arg("dir") : "stop";
  if (server.hasArg("spd")) {
    int s = server.arg("spd").toInt();
    speedPWM = constrain(s, 0, 1023);
  }
  if (dir == "fwd") fwd();
  else if (dir == "back") back();
  else if (dir == "left") left();
  else if (dir == "right") right();
  else stopMotors();

  String msg = "dir=" + dir + ", spd=" + String(speedPWM);
  server.send(200, "text/plain", msg);
}

void handleRoot() {
  String html =
    "<h2>ESP8266 Tank Bot</h2>"
    "<p><a href='/move?dir=fwd'>Forward</a> | "
    "<a href='/move?dir=back'>Back</a> | "
    "<a href='/move?dir=left'>Left</a> | "
    "<a href='/move?dir=right'>Right</a> | "
    "<a href='/move?dir=stop'>Stop</a></p>"
    "<form action='/move'>"
    "Speed (0-1023): <input name='spd' value='"+String(speedPWM)+"'/> "
    "<input type='hidden' name='dir' value='fwd'/>"
    "<button type='submit'>Set & Fwd</button>"
    "</form>";
  server.send(200, "text/html", html);
}

void setupPins() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(EN_LEFT, OUTPUT); pinMode(EN_RIGHT, OUTPUT);
  stopMotors();
}

void setup() {
  setupPins();
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) { delay(400); }

  server.on("/", handleRoot);
  server.on("/move", handleMove);
  server.begin();

  // PWM frekansı ve çözünürlüğü ESP8266'da sabittir (analogWrite 0..1023).
}

void loop() {
  server.handleClient();
  // Güvenlik: bağlantı yoksa bir süre sonra durdur (opsiyonel)
  static unsigned long tLast = millis();
  if (server.client() && server.client().connected()) tLast = millis();
  if (millis() - tLast > 10000) stopMotors(); // 10 sn komut yoksa dur
}
