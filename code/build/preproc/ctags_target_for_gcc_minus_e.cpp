# 1 "f:\\Skytech\\Microsoft\\Cours\\Informatique\\Structure\\6TQ\\Projet laser game\\code\\randomRing\\random.ino"
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
# 25 "f:\\Skytech\\Microsoft\\Cours\\Informatique\\Structure\\6TQ\\Projet laser game\\code\\randomRing\\random.ino" 2

// Matrix led
# 28 "f:\\Skytech\\Microsoft\\Cours\\Informatique\\Structure\\6TQ\\Projet laser game\\code\\randomRing\\random.ino" 2

# 30 "f:\\Skytech\\Microsoft\\Cours\\Informatique\\Structure\\6TQ\\Projet laser game\\code\\randomRing\\random.ino" 2

// --------------------------------------------------------|
//
//                      PIN SETUP
//
//---------------------------------------------------------|

// Matrix led pins 




// --------------------------------------------------------|
//
//                   VARIABLE DECLARATION
//
//---------------------------------------------------------|

// Define the number of devices we have in the chain and the hardware interface



// Hardware SPI connection
MD_Parola matrix = MD_Parola(MD_MAX72XX::FC16_HW, 10, 8 /* 4x2 matrix*|*/);

// Declare NeoPixel strip object
Adafruit_NeoPixel strip(48, 2, ((1<<6) | (1<<4) | (0<<2) | (2)) /*|< Transmit as G,R,B*/ + 0x0000 /*|< 800 KHz data transmission*/);

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
void setup()
{
    // Pin setup
    pinMode(2, 0x1);
    pinMode(3, 0x0);

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
