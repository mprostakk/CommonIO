#include "Arduino.h"
#include "Execute.h"

Execute::Execute() : waiting(false)
{
    time = lastTime = millis();   
}

void Execute::InMillis(unsigned long time)
{
    this->time = time;
    lastTime = millis();
    waiting = true;
}

bool Execute::Check()
{
    if(waiting &&  millis() - lastTime >= time)
    {
        waiting = false;
        return true;
    }
    return false;
}