/*
  IoT Smart Waste Monitoring System
  Author: Daniel Ibrahim

  Simulation-based smart waste monitoring system using:
  - ESP32
  - HC-SR04 ultrasonic sensor
  - 16x2 I2C LCD
  - ThingSpeak cloud monitoring

  NOTE:
  Replace YOUR_THINGSPEAK_WRITE_API_KEY with your private
  ThingSpeak Write API key only when running the project locally.
  Do not publish a real API key to GitHub.
*/

#include <Wire.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 5
#define ECHO_PIN 18

const float BIN_DEPTH = 50.0;
int batteryLevel = 50;

const char* THINGSPEAK_API_KEY = "YOUR_THINGSPEAK_WRITE_API_KEY";
const char* THINGSPEAK_SERVER = "api.thingspeak.com";

const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

WiFiClient client;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.init();
  lcd.backlight();

  connectToWiFi();

  lcd.setCursor(0, 0);
  lcd.print("Smart Bin");

  lcd.setCursor(0, 1);
  lcd.print("WiFi Connected");

  delay(1500);
  lcd.clear();
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  float distance = duration / 58.0;

  if (distance > BIN_DEPTH) {
    distance = BIN_DEPTH;
  }

  if (distance < 0) {
    distance = 0;
  }

  float fillLevel =
      ((BIN_DEPTH - distance) / BIN_DEPTH) * 100.0;

  String status;
  String priority;
  int priorityValue;

  if (fillLevel < 50) {
    status = "AVAILABLE";
    priority = "LOW";
    priorityValue = 1;
  }
  else if (fillLevel < 80) {
    status = "NEARLY FULL";
    priority = "MEDIUM";
    priorityValue = 2;
  }
  else {
    status = "FULL";
    priority = "HIGH";
    priorityValue = 3;
  }

  Serial.println("SMART BIN MONITOR");
  Serial.println("----------------------");

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Fill Level: ");
  Serial.print(fillLevel);
  Serial.println("%");

  Serial.print("Status: ");
  Serial.println(status);

  Serial.print("Collection Priority: ");
  Serial.println(priority);

  Serial.print("Battery: ");
  Serial.print(batteryLevel);
  Serial.println("%");

  if (fillLevel >= 80) {
    Serial.println("ALERT: COLLECTION REQUIRED");
  }

  if (batteryLevel <= 15) {
    Serial.println("ALERT: LOW BATTERY");
  }

  Serial.println("----------------------");

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Fill: ");
  lcd.print((int)fillLevel);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print(status);

  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Battery: ");
  lcd.print(batteryLevel);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Priority: ");
  lcd.print(priority);

  sendToThingSpeak(
    fillLevel,
    distance,
    batteryLevel,
    priorityValue
  );

  delay(20000);
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void sendToThingSpeak(
  float fillLevel,
  float distance,
  int batteryLevel,
  int priorityValue
) {
  if (client.connect(THINGSPEAK_SERVER, 80)) {
    String url = "/update?api_key=";
    url += THINGSPEAK_API_KEY;

    url += "&field1=";
    url += String(fillLevel);

    url += "&field2=";
    url += String(distance);

    url += "&field3=";
    url += String(batteryLevel);

    url += "&field4=";
    url += String(priorityValue);

    client.print(
      String("GET ") + url + " HTTP/1.1\r\n" +
      "Host: " + THINGSPEAK_SERVER + "\r\n" +
      "Connection: close\r\n\r\n"
    );

    Serial.println("Data sent to ThingSpeak");

    client.stop();
  }
  else {
    Serial.println("ThingSpeak connection failed");
  }
}
