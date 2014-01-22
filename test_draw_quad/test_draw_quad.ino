/******************************************************************************

Code for drawing a quadrilateral shape with 2 stepper.
It implements a state machine. Quite stupid.
Uses the motor shield version 2

Alberto, Alessandro, Eva, 15/01/2015

******************************************************************************/


#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"


Adafruit_MotorShield AFMSbot(0x61);
Adafruit_MotorShield AFMStop(0x60);

Adafruit_StepperMotor *myStepper1 = AFMStop.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(200, 2);

// wrappers
void forwardstep1() {  
  myStepper1->onestep(FORWARD, INTERLEAVE);
}
void backwardstep1() {  
  myStepper1->onestep(BACKWARD, INTERLEAVE);
}
void forwardstep2() {  
  myStepper2->onestep(FORWARD, INTERLEAVE);
}
void backwardstep2() {  
  myStepper2->onestep(BACKWARD, INTERLEAVE);
}

AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);

int state = 0;
boolean m1_arrived=true, m2_arrived=true;

void setup()
{  
  AFMSbot.begin();
  AFMStop.begin();
   
  stepper1.setMaxSpeed(900.0);
  stepper1.setAcceleration(500.0);
  stepper1.moveTo(1000);
    
  stepper2.setMaxSpeed(900.0);
  stepper2.setAcceleration(500.0);
  stepper2.moveTo(1000);
  
  Serial.begin(9600);
  Serial.println("hello");
}

void loop()
{
    if (stepper1.distanceToGo() == 0) {
      m1_arrived = true;	
    }

    if (stepper2.distanceToGo() == 0) {
      m2_arrived = true;
    }
    
    if(m1_arrived==true && m2_arrived==true) {
      changeState();  
    }
      
    stepper1.run();
    stepper2.run();
}

void changeState() {
  if(state==0) {
    Serial.println("state from 0 to 1");
    stepper1.moveTo(1000);
    stepper2.moveTo(1000);
    state++;
  }else if(state==1) {
    Serial.println("state from 1 to 2");
    stepper1.moveTo(2000);
    stepper2.moveTo(0);
    state++;
  }else if(state==2) {
    Serial.println("state from 1 to 2");
    stepper1.moveTo(1000);
    stepper2.moveTo(-1000);
    state++;
  }else if(state==3) {
    Serial.println("state from 1 to 2");
    stepper1.moveTo(0);
    stepper2.moveTo(0);
    state++;
  }
    
  m1_arrived = false;
  m2_arrived = false;
}

