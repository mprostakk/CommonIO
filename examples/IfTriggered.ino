#include <Input.h>
#include "Arduino.h"

Input enc0 = Input(0, "Encoder0");
Input enc1 = Input(1, "Encoder1");
Input enc2 = Input(2, "Encoder2");

void setup()
{
    // Default divider is 1 and counts on every edge
    enc1.setDivider(4);
    enc2.setDivider(4, RISING); // ( or  FALLING )
}

void loop()
{
    enc0.Read();  
    enc1.Read();  
    enc2.Read();  

    if(enc0.IfTriggered())
    {
        Serial.println("Triggered enc0");
    }

    if(enc1.IfTriggered())
    {
        Serial.println("Triggered enc1");
    }

    if(enc2.IfTriggered())
    {
        Serial.println("Triggered enc2");
    }

    enc0.Update();
    enc1.Update();
    enc2.Update();
}