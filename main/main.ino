#define joyX A2
#define joyY A3
#include <Servo.h>
#include <Arduino_MKRIoTCarrier.h>
#include "Ultrasonic.h"


MKRIoTCarrier carrier;
Servo myservo;

Ultrasonic ultrasonic(A0);

void setup() {
  myservo.attach(1);
  carrier.noCase();
  carrier.begin();
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  float pressure = carrier.Pressure.readPressure();
  int micValue = constrain(analogRead(A1), 0, 100);
  long RangeInCentimeters = ultrasonic.MeasureInCentimeters();
  float co2 = carrier.AirQuality.readCO2();
  int servoAngle = map(analogRead(joyX), 0, 1024, 0, 180);
  myservo.write(servoAngle);

  carrier.display.print("PRESSURE: ");
  carrier.display.print(pressure);
  carrier.display.print(" kPa    ");
  carrier.display.print("\t");

  carrier.display.print("MIC: ");
  carrier.display.print(micValue);
  carrier.display.print("    ");
  carrier.display.print("\t");

  carrier.display.print("SONA: ");
  carrier.display.print(RangeInCentimeters);
  carrier.display.print(" CM    ");

  carrier.display.print("ANGLE: ");
  carrier.display.print(servoAngle);
  carrier.display.println();
}
