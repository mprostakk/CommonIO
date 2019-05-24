#include "Arduino.h"
#include "Output.h"

Output::Output(const int pin, const String name, bool debug = false) 
    : pin(pin)
    , name(name)
    , is_busy(false)
    , is_millis(true)
    , debug(debug)
{
    state = false;
    lastTimeOn = lastTimeOff = millis();
    amountOfTime = 0;
    counter = 0;
    pinMode(pin, OUTPUT);
}

void Output::SetHigh()
{
    if(state == false)
    {
        digitalWrite(pin, HIGH);
        state = true;
    }
    else if(debug)
    {
        Serial.println(name + ": Tried to set HIGH while HIGH");
    }
    counter++;
    lastTimeOn = millis();
}

void Output::SetLow()
{
    if(state)
    {
        digitalWrite(pin, LOW);
        state = false;
    }
    else if(debug)
    {
        Serial.println(name + ": Tried to set LOW while LOW");
    }
    counter++;
    lastTimeOff = millis();
}

void Output::Print() const
{
    Serial.println(name);

    Serial.println(String("state: " + String(state, DEC)));
    Serial.println(String("is_busy: " + String(is_busy, DEC)));
    Serial.println(String("lastTime: " + String(lastTime, DEC)));
    Serial.println(String("amountOfTime: ") + String(amountOfTime, DEC));
    Serial.println(String("LastTimeWasOn: ") + String(LastTimeWasOn(), DEC));
    Serial.println(String("LastTimeWasOff: ") + String(LastTimeWasOff(), DEC));
}

bool Output::isBusy() const
{
    return is_busy;
}

bool Output::isOn() const
{
    return state;
}

void Output::On()
{
    if(is_busy)
    {
        is_busy = false;
        if(debug)
            Serial.println(name + String(": Used On() while OnForMillis() was being used"));
    }
    SetHigh();
}

void Output::OnForMillis(unsigned long amountOfTime)
{
    is_millis = true;
    if(state && debug)
    {
        Serial.println(name + String(": Tried to use OnForMillis while set to HIGH"));
    }
    if(is_busy)
        Serial.println(name + String(" is busy."));

    SetHigh();
    is_busy = true;
    lastTime = millis();
    this->amountOfTime = amountOfTime; 
}

void Output::OffForMillis(unsigned long amountOfTime)
{
    is_millis = true;
    if(state == false && debug)
    {
        Serial.println(name + String(": Tried to use OffForMillis while set to LOW"));
    }
    if(is_busy)
        Serial.println(name + String(" is busy."));

    SetLow();
    is_busy = true;
    lastTime = millis();
    this->amountOfTime = amountOfTime; 
}

void Output::OnForMicros(unsigned long amountOfTime)
{
    is_millis = false;
    if(state && debug)
    {
        Serial.println(name + String(": Tried to use OnForMicros while set to HIGH"));
    }
    if(is_busy)
        Serial.println(name + String(" is busy."));

    SetLow();
    is_busy = true;
    lastTime = micros();
    this->amountOfTime = amountOfTime;
}

void Output::OffForMicros(unsigned long amountOfTime)
{
    is_millis = false;
    if(state == false && debug)
    {
        Serial.println(name + String(": Tried to use OffForMillis while set to LOW"));
    }
    if(is_busy)
        Serial.println(name + String(" is busy."));
    
    SetLow();
    is_busy = true;
    lastTime = micros();
    this->amountOfTime = amountOfTime; 
}

void Output::Off()
{
    if(is_busy)
    {
        is_busy = false;
        if(debug)
            Serial.println(name + String(": Used Off() while OnForMillis() was being used"));
    }
    SetLow();
}

void Output::Switch()
{
    if(state)
        SetLow();
    else
        SetHigh();
}

void Output::Update()
{
    unsigned long tm = is_millis ? millis() : micros();

    if (is_busy 
        && amountOfTime 
        && tm - lastTime >= amountOfTime)
    {
        is_busy = false;
        Switch();
    }
}

unsigned long Output::LastTimeWasOn() const
{
    return millis() - lastTimeOn;
}

unsigned long Output::LastTimeWasOff() const
{
    return millis() - lastTimeOff;
}