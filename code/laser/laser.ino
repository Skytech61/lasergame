int buttonShoot = 2;
int buttonReload = 5;
int laser = 3;
int balle = 7;

long timer;
boolean isPressed = false;
byte i = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(buttonShoot, INPUT_PULLUP);
    pinMode(buttonReload, INPUT_PULLUP);
    pinMode(laser, OUTPUT);
    digitalWrite(laser, LOW);
}

void loop()
{
    if(i < balle)
    {
        if(!digitalRead(buttonShoot))
        {
            if(!isPressed)
            {
                i++;
                isPressed = true;
                digitalWrite(laser, HIGH);
                timer = millis();
            }
        }
    }
    else if(i >= balle)
    {
        if(!digitalRead(buttonReload))
        {
            i = 0;
            delay(2000);
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
    
    if((millis() - timer) > 3000 && isPressed)
    {
        digitalWrite(laser, LOW);
    }
}