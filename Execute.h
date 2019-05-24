#ifndef EXECUTE_H
#define EXECUTE_H

class Execute
{
private:
    bool waiting;
    unsigned long lastTime;
    unsigned long time;
public:
    Execute();
    void InMillis(unsigned long);
    bool Check();
};

#endif