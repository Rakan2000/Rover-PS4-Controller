#include <Arduino.h>
#include <ArduinoJson.h>

#define JSON_CAPACITY 200
#define period 1000

#define led 2

const int left_pwm_pin = 13;
const int left_dir_pin = 12;
const int right_pwm_pin = 26;
const int right_dir_pin = 25;

const int left_forward_dir = 1;
const int right_forward_dir = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);

    pinMode(right_pwm_pin, OUTPUT);
    pinMode(left_pwm_pin, OUTPUT);
    pinMode(right_dir_pin, OUTPUT);
    pinMode(left_dir_pin, OUTPUT);

    digitalWrite(left_dir_pin, left_forward_dir);
    digitalWrite(right_dir_pin, right_forward_dir);
}

void loop()
{

  StaticJsonDocument<JSON_CAPACITY> doc;
  auto now = millis();

  if (Serial.available() > 0)
  {
    String receivedData = Serial.readStringUntil('\n');
    DeserializationError error = deserializeJson(doc, receivedData);

    if (!error)
    {
      // Successfully parsed JSON, now extract the speed value
      if (doc.containsKey("left_motor"))
      {
        int speed = doc["left_motor"];
        analogWrite(led, speed);
        // int steering_angle = doc["steering-angle"];
        // Serial.println("Speed: " + String(speed));
        // Serial.println("Steering: " + String(steering_angle));
      }
    }
    else
    {
      Serial.println("JSON parsing failed!");
    }
  }
  // auto velocity = 100.0 * sin(2 * PI * now / period);
  // float angle = 2 * PI * now / period;
  // const float radius = 20.0;
  // float x_position = radius * cos(angle);
  // float y_position = radius * sin(angle);

  doc.clear();
  // doc["time"] = now;
  // doc["velocity"] = velocity;
  // doc["x"] = x_position;
  // doc["y"] = y_position;

  // serializeJson(doc, Serial);
  // Serial.println();

  delay(100);
}
