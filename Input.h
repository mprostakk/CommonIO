#ifndef INPUT_H
#define INPUT_H

class Input
{
private:
  const String name;
  const int pin;

  bool state;
  bool last_state;

  int divider;
  int divider_counter;
  int counter;

  bool state_changed;

  // Debounce variables
  int divider_edge;
  int counter_type;
  int state_changed_type;
  bool debounce_last_state;
  bool is_debounce;
  unsigned long last_debounce_time;
  unsigned long debounce_time;
  
  // Edge times
  unsigned long last_rising_edge_time;
  unsigned long last_falling_edge_time;
  unsigned long last_state_diff_time;
public:
  /*
  pin   - number of pin
  name  - name used in sending data
  (not working) debug - if true, all errors with log on serial port 
  */
  Input(const int pin, const String name);
  // Set divider for encoder
  void setDivider(int divider);
  // Set divider for encoder
  // Second Param is for triggering on edge:
  // CHANGE  - Count for every state change
  // RISING  - Count only rising edges
  // FALLING - Count only falling edged
  void setDivider(int divider, const int);
  // Necessary. Sets state to digitalRead()
  void Read();
  // Get State
  bool State() const;
  // NOT WORKING !!
  // Get Last State
  bool LastState() const;
  // State difference
  // Return true if state != last_state
  bool StateDiff() const;
  // NOT WORKING !!
  // Reset state and time 
  void Reset();
  // Print to serial needed variables for debugging
  void Print() const;
  // Check if divider_counter >= divider
  bool IfTriggered() const;
  // Set a debounce time, makes input work on debounce mode
  void SetDebounceTime(unsigned long);
  // Check if input was pressed
  bool IfRising() const; 
  // Check if input was released
  bool IfFalling() const;
  // Check if input was pressed for an amount of time
  unsigned long PressedFor();
  // Last Rising Edge time in millis
  unsigned long LastRisingEdgeTime() const;
  // Last Falling Edge time in millis
  unsigned long LastFallingEdgeTime() const;
  // Last time when State was changed
  unsigned long LastStateDiffTime() const;
  // How long is an input on for
  // If state is Off, return 0
  unsigned long OnFor() const;
  // How long is an input off for
  // If state in On, return 0
  unsigned long OffFor() const;
  // Update divider_counter
  void Update();
  // NOT WORKING !!
  // Build and return json for Input
  // String GetJson() const;
  
  // Return Edge type of state
  // EdgeTypes::EdgeType Edge();
  const int Edge();
  
private:
  // Check if state was changed, if so, add to counter and change state!
  bool StateChange();
};

/* FLOW:
  - ReadState
  - StateChange 
  - IfTrigger
  - Update
*/

#endif