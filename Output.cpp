#include "Arduino.h"
#include "Output.h"

void Output::init()
{
    is_millis = true;
    is_busy = false;
    state = false;
    lastTimeOn = lastTimeOff = millis();
    amountOfTime = 0;
    counter = 0;
    pinMode(pin, OUTPUT);
}

Output::Output(const int pin) : pin(pin), name("")
{
    debug = false;
    init();
}

Output::Output(const int pin, bool debug) : pin(pin), name("")
{
    this->debug = debug;
    init();
}

Output::Output(const int pin, bool debug, const String name) 
    : pin(pin)
    , name(name)
{
    this->debug = debug;
    init();
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
    if(is_busy && debug)
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
    if(is_busy && debug)
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
    if(is_busy && debug)
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
    if(is_busy && debug)
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