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

const int runButton = 45;
const int selectModeButton = 43;
const int upButton = 47;
const int downButton = 49;
const int leftButton = 51;
const int rightButton = 53;
const int jogSpeed = 4000;
const int cueSpeed = 4000;

const int high_pos = 66000;
const int low_pos = 50000;
const int left_pos = 0;
const int right_pos = 172000;

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

long nextLiftPos;
long nextTrackPos;

void setup()
{  
   pinMode(upButton, INPUT_PULLUP);
   pinMode(downButton, INPUT_PULLUP);
   pinMode(leftButton, INPUT_PULLUP);
   pinMode(rightButton, INPUT_PULLUP);
   pinMode(runButton, INPUT_PULLUP);
   
   lift.setMaxSpeed(jogSpeed);
   lift.setAcceleration(1000);
   
   track.setMaxSpeed(jogSpeed);
   track.setAcceleration(2000);
   
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
  runButtonState = digitalRead(runButton);
  
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

  if (runButtonState == LOW){
    //button down, changed?
    if (runButtonState != lastRunButton){
      Serial.println("Run cue");
      track.setMaxSpeed(cueSpeed);
      lift.setMaxSpeed(cueSpeed);
      track.moveTo(175000);
      lift.moveTo(66000);
      Serial.println("Setting cue targets");
    } else {
      if (lift.distanceToGo() == 0)
      {
        if (lift.currentPosition() == 66000){
          nextLiftPos = 50000;
        } else {
          nextLiftPos = 66000;
        }
        lift.moveTo(nextLiftPos);
        Serial.println("Reset lift target");
        Serial.println(nextLiftPos);
      }
      if (track.distanceToGo() == 0){
        if (track.currentPosition() == 175000){
          nextTrackPos = 0;
        } else {
          nextTrackPos = 175000;
        }
        track.moveTo(nextTrackPos);
        Serial.println("Reset track target");
        Serial.println(nextTrackPos);
      }
      track.run();
      lift.run();
    }
  } else {
    //button up, changed?
    if (runButtonState != lastRunButton){
      stopTrack();
      stopLift();
    }
  }
  
  lastDownButton = downButtonState;
  lastUpButton = upButtonState;
  lastLeftButton = leftButtonState;
  lastRightButton = rightButtonState;
  lastRunButton = runButtonState;
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
