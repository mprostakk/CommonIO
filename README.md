# CommonIO

> Arduino library that makes handling **Input** and **Output** easier. There are many useful features for using 
**buttons**, **encoders** and **triggers**.

## Examples
```C++
#include "Arduino.h"
#include <Input.h>
#include <Output.h>
#include <Execute.h>

Input enc1 = Input(0);
Input inp1 = Input(1);
Input inp2 = Input(2, "Input2");

Output out1 = Output(8);
Output out2 = Output(9, true, "Output2");

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
```

## Constructors

### Input(const int pin)
### Input(const int pin, const String name)
#### Description
The constructor defines an input object
#### Syntax
```C++ 
Input(const int pin)
Input(const int pin, const String name)
```
#### Required parameters
**pin: ** Arduino pin number that the input is connected to *(byte)*
##### Optional parameters
**name: ** Name of input used for debugging
#### Example
```C++
#include <Input.h>

Input inp1 = Input(3);
Input inp1 = Input(3, "inp1");
```

### Output(const int pin)
### Output(const int pin, bool debug)
### Output(const int pin, bool debug, const String name)
#### Description
The constructor defines an output object
#### Syntax
```C++ 
Output(const int pin)
Output(const int pin, bool debug)
Output(const int pin, bool debug, const String name)
```
#### Required parameters
**pin: ** Arduino pin number that the output is connected to *(byte)*
##### Optional parameters
**debug: ** If true, prints on serial all usefull information when testing
**name: ** Name of output used for debugging
#### Example
```C++
#include <Output.h>

Output out1 = Output(7);
Output out1 = Output(8, "Output1");
Output out2 = Output(9, true, "Output2");
```

### Execute()
#### Description
The constructor defines an execute object
#### Syntax
```C++ 
Execute()
```
#### Example
```C++
#include <Execute.h>

Execute ex1;
Execute ex2();
```

## Input library function
### setDivider(int divider, const int edgeType);
##### Description
Function used to set divider. When not set, the default value is *1*. 
The divider tells how many *state changes* must appear for *IfTriggered* to be true.
##### Syntax
```C++
inp1.setDivider(int divider, const int edgeType);
```
##### Required parameters
** divider: ** How many state changes there 
##### Optional parameters
** edgeType: ** ( CHANGE, RISING, FALLING ), count only on rising/falling edges. Default ( CHANGE ) - count on every state change
##### Returns
None.
##### Example
```C++
void setup() {
   inp1.setDivider(4);
   inp2.setDivider(10, RISING);
   inp3.setDivider(16, FALLING);
}
```

### SetDebounceTime(unsigned long debounce_time)
##### Description
Sets debounce time for input. If function not used there is no debounce. 
##### Syntax
```C++
inp1.SetDebounceTime(unsigned long debounce_time)
```
##### Required parameters
** debounce_time: ** Debounce time in ms
##### Returns
None.
##### Example
```C++
void setup() {
   // Debounce time in ms
   inp1.SetDebounceTime(200);
}
```

### Read()
##### Description
Reads the input state and more. Adds to counter, checks debounce times and falling/rising times. 
##### Returns
None.
##### Example
```C++
enc1.Read();
inp1.Read();
```

### State()
##### Description
Get current state
##### Returns
Returns *(bool)* **true** or **false**
##### Example
```C++
if(inp1.State()) {
   Serial.println("Input is HIGH");
}
```

### StateDiff()
##### Description
Check if last state is different that current state
##### Returns
Returns **true** if state != last_state or **false** state == last_state
##### Example
```C++
if(inp1.StateDiff()) {
   Serial.println("Input changed state");
}
```

### Reset()
##### Description
Resets times and divider counter.
##### Returns
None.
##### Example
```C++
inp1.Reset();
```

### IfTriggered()
##### Description
Check divider_counter >= divider
##### Returns
Returns **true** if divider_counter >= divider and resets divider_counter
##### Example
```C++
if(inp1.IfTriggered()) {
   Serial.println("Input just triggered");
}
```

### Update()
##### Description
If function IfTriggered is being used. Update() should be necessary at end of *loop*.
##### Returns
None.
##### Example
```C++
inp1.Update();
```

### IfRising() / IfFalling()
##### Description
Check if input just changed from LOW to HIGH or from HIGH to LOW
##### Returns
Returns **true** if and Edge has appeared (Rising or Falling)
##### Example
```C++
if(inp1.IfRising()) {
   Serial.println("Input had an rising edge");
}

if(inp1.IfFalling()) {
   Serial.println("Input had an falling edge");
}
```

### Print()
##### Description
Prints useful information to *Serial* for debugging purposes
##### Returns
None.
##### Example
```C++
inp1.Print();
```

### PressedFor()
### LastRisingEdgeTime()
### LastFallingEdgeTime()
### LastStateDiffTime()
### OnFor()
### OffFor()
### Edge()

## Output library function
### On()
### Off()
### OnForMillis(unsigned long)
### OffForMillis(unsigned long)
### OnForMicros(unsigned long)
### OffForMicros(unsigned long)
### Update()
### isBusy()
### Switch()
### isOn()
### LastTimeWasOn()
### LastTimeWasOff()
### Print()

## Execute library function
### InMillis(unsigned long)
### Check()

## License
[MIT](https://choosealicense.com/licenses/mit/)