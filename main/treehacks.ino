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

  Serial.print("x: ");
  Serial.println(analogRead(joyX));
  Serial.print("y: ");
  Serial.println(analogRead(joyY));
  if (analogRead(joyX) < 10) {
    int servoAngle = 0;
  } else if (analogRead(joyX) > 1000 ){
    int servoAngle = 180;
  } else if (analogRead(joyY) < 10) {
    int servoAngle = 135;
  } else if (analogRead(joyY) > 1000) {
    int servoAngle = 45;
  } else {
    int servoAngle = 90;
  }
  int servoAngle = round(analogRead(joyX)/5.6889);

  myservo.write(servoAngle);

  carrier.display.setTextSize(2);
  carrier.display.setTextColor(0x07E0);
  carrier.display.setCursor(40, 130);

  Serial.print("pressure: ");
  Serial.println(pressure);
  

  Serial.print("Mic: ");
  Serial.println(micValue);
  if (micValue > 2) {
    carrier.display.fillScreen(0x0000);
    carrier.display.print("Sound Detected");
  }

  Serial.print("Distance: ");
  Serial.println(RangeInCentimeters);


  int numberbar = round(RangeInCentimeters/2);
  carrier.display.setTextSize(2);
  carrier.display.setTextColor(0xFFFF);
  carrier.display.setCursor(0, 100);

  if (numberbar > 20) {
    numberbar = 20;
  }

  for (int i = 1;i<numberbar;i++) {
  carrier.display.print("|");
  }
// beeps for distance
  // int freqt = round(RangeInCentimeters*5);
  // if (freqt > 500) {
  //   freqt = 500;
  // }

  // carrier.Buzzer.beep();
  // carrier.Buzzer.beep(800, 20);
  // delay(freqt);
  // carrier.Buzzer.beep();
  // carrier.Buzzer.beep(800, 20);
  // delay(freqt);
  // carrier.Buzzer.beep();
  // carrier.Buzzer.beep(800, 20);

  Serial.print("co2");
  Serial.println(co2);

  if (co2 > 400){
    carrier.display.fillScreen(0x0000);
    carrier.display.setTextColor(0xF800);
    carrier.display.setCursor(60, 160);
    carrier.display.print("Co2 > Avg");
  }
  

}