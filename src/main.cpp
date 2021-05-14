#include <Arduino.h>

#define SERIAL_BAUDS 115200

#ifndef LED_BUILTIN
  #define LED_BUILTIN PC13
#endif

#define LED_PIN LED_BUILTIN
#define LED_TIME 1000
unsigned long ledTimer = 0;
bool blinkState = false;

//
// encoder control variables
//

#include "encoder.h"

#ifndef ENCODER_MOTOR_H
#define ENCODER_MOTOR_H

#define bodyEncoderSignal FALLING
#define bodyEncoderInputSignal INPUT_PULLUP

// encoder FrontLeftMotor
//#define bodyEncoderFrontLeftInt 0
#define bodyEncoderFrontLeftFunction bodyEncoderFrontLeftCounter
#define bodyEncoderFrontLeftPin PB15 // A pin the interrupt pin
#define bodyEncoderFrontLeftSignal bodyEncoderSignal
#define bodyEncoderFrontLeftInputSignal bodyEncoderInputSignal

// encoder FrontRightMotor
//#define bodyEncoderFrontRightInt 1
#define bodyEncoderFrontRightFunction bodyEncoderFrontRightCounter
#define bodyEncoderFrontRightPin PB14 // A pin: the interrupt pin
#define bodyEncoderFrontRightSignal bodyEncoderSignal
#define bodyEncoderFrontRightInputSignal bodyEncoderInputSignal

#endif

// encoder rotation direction
bool bodyEncoderFrontLeftDirection; 
bool bodyEncoderFrontRightDirection;

// encoder pulses
volatile signed long bodyEncoderFrontLeftTotalPulses = 0;
volatile signed long bodyEncoderFrontRightTotalPulses = 0;

//
// encoder control
//

void bodyEncoderFrontLeftCounter() {
  if(bodyEncoderFrontLeftDirection)
    bodyEncoderFrontLeftTotalPulses ++;
  else
    bodyEncoderFrontLeftTotalPulses ++;
}

void bodyEncoderFrontRightCounter() {
  if(bodyEncoderFrontRightDirection)
    bodyEncoderFrontRightTotalPulses ++;
  else
    bodyEncoderFrontRightTotalPulses --;
}

//
// setup function
// 

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(SERIAL_BAUDS);

  delay(250);

  // encoders definition
  bodyEncoderFrontLeftDirection = 1;
  attachInterrupt(bodyEncoderFrontLeftPin, bodyEncoderFrontLeftCounter, bodyEncoderFrontLeftSignal);

  bodyEncoderFrontRightDirection = 1;
  attachInterrupt(bodyEncoderFrontRightPin, bodyEncoderFrontRightCounter, bodyEncoderFrontRightSignal);

}

//
// loop function
// 

void loop()
{

  // activity led
  if(millis() > ledTimer) {
    ledTimer = millis() + LED_TIME;
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
 
    Serial.print(bodyEncoderFrontLeftTotalPulses);
    Serial.print(" ");
    Serial.println(bodyEncoderFrontRightTotalPulses);
  }

}