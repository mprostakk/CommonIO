#include "Arduino.h"
#include <Input.h>
#include <Output.h>
#include <Execute.h>

/*
Input  Name = Input ( PIN,  NAME )
Output Name = Output( PIN,  NAME,  DEBUG = false)
*/

Input enc1 = Input(0, "Encoder1");
Input inp1 = Input(1, "Input1");
Input inp2 = Input(2, "Input2");

Output out1 = Output(8, "Output1");
Output out2 = Output(9, "Output2", true);

Execute ex1;

void setup()
{
    enc1.setDivider(4, RISING);
    inp1.SetDebounceTime(200);

    Serial.begin(9600);
}

void loop() 
{
    enc1.Read();  
    inp1.Read();
    inp2.Read();

    if(inp1.State())
    {
        Serial.println("inp1 state is HIGH");
    }

    out1.On();
    out2.Off();

    out1.Switch();

    if(enc1.IfTriggered())
    {
        Serial.println("Triggered");
    }

    if(inp1.IfRising())
    {
        Serial.println("inp1 rising edge");
    }

    if(inp1.IfFalling())
    {
        Serial.println("inp1 falling edge");
    }

    if(inp2.Edge() == RISING)
    {
        Serial.println("inp1 rising edge");
    }

    if(inp2.Edge() == FALLING)
    {
        Serial.println("inp1 falling edge");
    }

    if(inp2.IfRising())
    {
        Serial.print(" LastRisingEdgeTime: ");
        Serial.print(inp1.LastRisingEdgeTime());

        Serial.print(" LastFallingEdgeTime: ");
        Serial.println(inp1.LastFallingEdgeTime());

        Serial.print("OnFor: ");
        Serial.print(inp1.OnFor());

        Serial.print(" ,OffFor ");
        Serial.println(inp1.OffFor());
    }


    if(inp1.StateDiff())
    {
        ex1.InMillis(1000);
    }

    if(enc1.IfTriggered())
    {
        out1.OnForMillis(1000);
        out2.OffForMillis(1000);
    }

    if(ex1.Check())
    {
        out1.OnForMillis(1000);
    }

    out1.Update(); // update when output uses (On/Off)for(Millis/Micros)
    out2.Update();

    enc1.Update(); // Update input when IfTriggered is used
}