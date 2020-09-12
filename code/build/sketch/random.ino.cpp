#include <Arduino.h>
#line 1 "f:\\Skytech\\Microsoft\\Cours\\Informatique\\Structure\\6TQ\\Projet laser game\\code\\randomRing\\random.ino"
//    Copyright (C) 2020  Tuncay
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

// NeoPixel ring
#include <Adafruit_NeoPixel.h>

// Matrix led
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// --------------------------------------------------------|
//
//                      PIN SETUP
//
//---------------------------------------------------------|

// Matrix led pins 
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// --------------------------------------------------------|
//
//                   VARIABLE DECLARATION
//
//---------------------------------------------------------|

// Define the number of devices we have in the chain and the hardware interface
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8 // 4x2 matrix*/

// Hardware SPI connection
MD_Parola matrix = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Declare NeoPixel strip object
Adafruit_NeoPixel strip(48, 2, NEO_GRB + NEO_KHZ800);

// NeoPixel colors
uint32_t red = strip.Color(255, 0, 0); // 20 points
uint32_t yellow = strip.Color(255, 255, 0); // 10 points
uint32_t blue = strip.Color(0, 0, 255); // 5 points
uint32_t green = strip.Color(0, 255, 0); // 1 points

// NeoPixel array for random
uint32_t colors[] = {red, yellow, blue, green};

// Point's color 
byte scoreData[] = {1, 5, 10, 20};

byte i = 1;
byte score = 0;

// Declare any variable
long timer;
int color;
int cible;

boolean print = false;
boolean touch = false;

// --------------------------------------------------------|
//
//                         START CODE
//
//---------------------------------------------------------|
#line 86 "f:\\Skytech\\Microsoft\\Cours\\Informatique\\Structure\\6TQ\\Projet laser game\\code\\randomRing\\random.ino"
void setup();
#line 100 "f:\\Skytech\\Microsoft\\Cours\\Informatique\\Structure\\6TQ\\Projet laser game\\code\\randomRing\\random.ino"
void loop();
#line 86 "f:\\Skytech\\Microsoft\\Cours\\Informatique\\Structure\\6TQ\\Projet laser game\\code\\randomRing\\random.ino"
void setup()
{
    // Pin setup
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);

    // Initialise
    matrix.begin();
    strip.begin();
    strip.show();
    Serial.begin(9600);
    randomSeed(analogRead(0));
}

void loop()
{
    if(i <= 100) // Number of turns
    {
        //Serial.println(i);
        if(!print)
        {
            // Generate random seed
            cible = random(0, 5); 
            color = random(0, 4);

            // Show random led with random color during x second
            strip.fill(colors[color], (cible*8), 8);
            strip.show();
    
            timer = millis();
            print = true;
            //Serial.println("cible allume: " + String(cible, DEC) + " couleurs: " + String(color, DEC));
        }
        else
        {
            if(millis() - timer >= 5000 or touch)
            {
                // After color clearing wait x second
                strip.clear();
                strip.show();
                i++;
            
                print = false;
                touch = false;
                delay(1000);
            }
            else if(digitalRead(cible+3)) // If targets are hit add points
            {
                touch = true;
                score += scoreData[color];
            }
        }
    }
    else // Game ended
    {
        matrix.print("SCORE : " + String(score));
        //Serial.println("score : " + String(score, DEC));
        delay(4000);
    }
}
