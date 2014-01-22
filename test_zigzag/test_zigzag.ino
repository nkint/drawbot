/******************************************************************************

Code for zigzag modern art with 2 stepper and 1 servo.
Uses the motor shield version 2

Alberto, Alessandro, Eva, 15/01/2015

******************************************************************************/


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h> 
#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(200, 2);

Servo myservo;

void setup() {
  Serial.begin(9600);
  Serial.println("Stepper test!");

  AFMS.begin();  
  myMotor1->setSpeed(30);
  myMotor2->setSpeed(30);
  
  myservo.attach(10);
}

void loop() {
  
  myservo.write(100);
  delay(1000);

  myMotor1->step(200, FORWARD, DOUBLE); 
  delay(1000);
  
  myservo.write(-100);
  delay(1000);
  
  myMotor2->step(100, FORWARD, DOUBLE); 
  delay(1000);
}
