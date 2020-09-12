//    Copyright (C) 2020  Skytech
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see https://www.gnu.org/licenses/.
//    https://www.gnu.org/licenses/gpl-3.0.en.html

// --------------------------------------------------------|
//
//                    INCLUDE LIBRARY
//
//---------------------------------------------------------|

// Song
#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>
TMRpcm tmrpcm;

// --------------------------------------------------------|
//
//                      PIN SETUP
//
//---------------------------------------------------------|
#define SD_ChipSelectPin 4
int speakers = 9;
int buttonShoot = 2;
int buttonReload = 5;
int laser = 3;

// --------------------------------------------------------|
//
//                      GAME CONFIG
//
//---------------------------------------------------------|
int bullets = 7; // bullet +1 (8 bullets)
int reloadTimer = 2000; // Time to reload gun
int pressTimer = 3000; // Time you can press shoot button

// --------------------------------------------------------|
//
//                   VARIABLE DECLARATION
//
//---------------------------------------------------------|
long timer;
boolean isPressed = false;
byte i = 0;

// --------------------------------------------------------|
//
//                         START CODE
//
//---------------------------------------------------------|
void setup()
{
    tmrpcm.speakerPin = speakers; // speaker pin;

    Serial.begin(9600);
    if (!SD.begin(SD_ChipSelectPin))
    {
        Serial.println("SD fail");  
        return;
    }
    tmrpcm.play("start.wav");

    pinMode(buttonShoot, INPUT_PULLUP);
    pinMode(buttonReload, INPUT_PULLUP);
    pinMode(laser, OUTPUT);
    digitalWrite(laser, LOW);
}

void loop()
{
    if(i < bullets +1)
    {
        if(!digitalRead(buttonShoot))
        {
            if(!isPressed)
            {
                tmrpcm.play("shoot1.wav");
                i++;
                isPressed = true;
                digitalWrite(laser, HIGH);
                timer = millis();
            }
        }
    }
    else if(i >= bullets +1)
    {
        if(!digitalRead(buttonReload))
        {
            tmrpcm.play("reload.wav");
            i = 0;
            delay(reloadTimer);
        }
    }
    
    if(digitalRead(buttonShoot))
    {
        if(isPressed)
        {
            isPressed = false;
            digitalWrite(laser, LOW);
        }
    }
    
    if((millis() - timer) > pressTimer && isPressed)
    {
        digitalWrite(laser, LOW);
    }
}
