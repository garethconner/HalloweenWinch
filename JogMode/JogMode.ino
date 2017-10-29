// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

AccelStepper lift(AccelStepper::DRIVER); // step & direction on 2, 3
AccelStepper track(AccelStepper::DRIVER, 4, 5);  // step & direction on 4, 5

const int runCueButton = 43;
const int selectModeButton = 45;
const int upButton = 47;
const int downButton = 49;
const int leftButton = 51;
const int rightButton = 53;
const int jogSpeed = 4000;

int runButtonState;
int selectButtonState;
int downButtonState;
int upButtonState;
int leftButtonState;
int rightButtonState;

int lastRunButton;
int lastSelectButton;
int lastUpButton;
int lastDownButton;
int lastLeftButton;
int lastRightButton;

void setup()
{  
   pinMode(upButton, INPUT_PULLUP);
   pinMode(downButton, INPUT_PULLUP);
   pinMode(leftButton, INPUT_PULLUP);
   pinMode(rightButton, INPUT_PULLUP);
   
   lift.setMaxSpeed(4000);
   lift.setAcceleration(1000);
   
   track.setMaxSpeed(4000);
   track.setAcceleration(1000);
   
   Serial.begin(115200);
   Serial.println("working!");
   
  lastRunButton = HIGH;
  lastSelectButton = HIGH;
  lastUpButton = HIGH;
  lastDownButton = HIGH;
  lastLeftButton = HIGH;
  lastRightButton = HIGH;
}

void loop()
{ 
  downButtonState = digitalRead(downButton);
  upButtonState = digitalRead(upButton);
  leftButtonState = digitalRead(leftButton);
  rightButtonState = digitalRead(rightButton);
  
  if (downButtonState == LOW){
    //button down, is this new?
    if (lastDownButton == HIGH){
      Serial.println("Lift set rev speed");
      lift.setSpeed(-jogSpeed); 
    } else {
      lift.runSpeed();
    }
  } else {
    //button up, changed?
    if (lastDownButton == LOW){
      stopLift();
    }
  }
  
  if (upButtonState == LOW){
    //button down, changed?
    if (lastUpButton == HIGH){
      Serial.println("Lift set fwd speed");
      lift.setSpeed(jogSpeed);
    } else{
      lift.runSpeed();
    }
  } else {
    //button up, changed?
    if (lastUpButton == LOW){
      stopLift();
    }
  }
  
  if (leftButtonState == LOW){
    //button down, changed?
    if (leftButtonState != lastLeftButton){
      Serial.println("Track set rev speed");
      track.setSpeed(-jogSpeed);  
    } else {
      track.runSpeed();  
    }
  } else {
    //button up, changed?
    if (leftButtonState != lastLeftButton){
      stopTrack();
    }  
  }
  
  if (rightButtonState == LOW){
    //button down, changed?
   if (rightButtonState != lastRightButton){
     Serial.println("Track set fwd speed");
     track.setSpeed(jogSpeed);
   } else {
     track.runSpeed();
   }
  } else {
    //button up, changed?
   if (rightButtonState != lastRightButton){
     stopTrack();
   }
  }
  
  
  lastDownButton = downButtonState;
  lastUpButton = upButtonState;
  lastLeftButton = leftButtonState;
  lastRightButton = rightButtonState;
}

void stopTrack(){
  track.stop();
  Serial.println("Track stopped.");
  Serial.println(track.currentPosition());
}

void stopLift(){
  lift.stop();
  Serial.println("Lift stopped.");
  Serial.println(lift.currentPosition()); 
}
