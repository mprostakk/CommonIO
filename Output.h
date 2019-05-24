#ifndef OUTPUT_H
#define OUTPUT_H

class Output
{
private:
  const int pin;
  const String name;

  bool state;
  unsigned long lastTime;
  unsigned long amountOfTime;
  bool is_busy;

  int lastTimeOn;
  int lastTimeOff;
  unsigned int counter;
  
  bool debug;
  bool is_millis;

  void SetHigh();
  void SetLow();
public:
  /*
  pin   - number of pin
  name  - name used in sending data
  debug - if true, all errors with log on serial port 
  */
  Output(const int pin, const String name, bool debug = false);
  // Print to serial needed variables for debugging
  void Print() const;
  // Check if Output is in use
  bool isBusy() const;
  // Check if Output state is HIGH
  bool isOn() const;
  // Necessary for function On to work. Checks if time has passed
  void Update();
  // Turn on Output
  // If OnForMillis was being used, it overwrites it
  void On();
  // Turn on Output for an amount of milliseconds
  void OnForMillis(unsigned long);
  // Turn off Output for an amount of milliseconds
  void OffForMillis(unsigned long);
  // Turn on Output for an amount of microseconds
  void OnForMicros(unsigned long);
  // Turn off Output for an amount of microseconds
  void OffForMicros(unsigned long);
  // Turn off Output
  // If OnForMillis was being used, it overwrites it
  void Off(); 
  // Switch from On to Off, or from Off to On
  void Switch();
  // Rising and falling times
  unsigned long LastTimeWasOn() const;
  unsigned long LastTimeWasOff() const;
};

#endif