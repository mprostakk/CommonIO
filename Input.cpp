#include "Arduino.h"
#include "Input.h"

Input::Input(const int pin, const String name = "Wejscie") : name(name), pin(pin)
{
  pinMode(pin, INPUT);
  state_changed = false;
  divider = 1;
  divider_counter = 0;
  Reset();
  counter_type = CHANGE;
  state_changed_type = CHANGE;
  divider_edge = CHANGE;
  is_debounce = false;  
  debounce_time = 25;
  last_debounce_time = 0;
  last_rising_edge_time = last_falling_edge_time = last_state_diff_time = 0;
}

void Input::setDivider(int divider)
{
  if(divider <= 0)
    this->divider = 1;
  else
    this->divider = divider;
}

void Input::setDivider(int divider, const int edgeType)
{
  setDivider(divider);
  if(edgeType >= 1 && edgeType <= 3)
    divider_edge = edgeType;
  else
    divider_edge = CHANGE;
}

void Input::Read()
{
  if(is_debounce)
  {
    state_changed_type = CHANGE;
    bool tmp_state = digitalRead(pin);

    if(tmp_state != debounce_last_state)
    {
      last_debounce_time = millis();
    }

    // almost always true
    if( (millis() - last_debounce_time ) > debounce_time )
    {
      if(tmp_state != state)
      {
        state = tmp_state;
        state_changed = StateChange();
      }
    } 
    debounce_last_state = tmp_state;
  }
  else
  {
    state = digitalRead(pin);
    state_changed = StateChange();
  }
}

void Input::SetDebounceTime(unsigned long debounce_time)
{
  this->debounce_time = debounce_time;
  is_debounce = true;
}

bool Input::IfRising() const
{
  return state_changed_type == RISING;
}

bool Input::IfFalling() const
{
  return state_changed_type == FALLING;
}

const int Input::Edge()
{
  return state_changed_type;
}

unsigned long Input::LastRisingEdgeTime() const
{
  return last_rising_edge_time;
}

unsigned long Input::LastFallingEdgeTime() const
{
  return last_falling_edge_time;
}

unsigned long Input::LastStateDiffTime() const
{
  return last_state_diff_time;
}

bool Input::State() const
{
  return state;
}

bool Input::LastState() const
{
  return last_state;
}

bool Input::StateChange()
{
  if(state != last_state)
  {
    counter++;

    if(last_state == 0 && state == 1)
    {
      state_changed_type = RISING;
      last_rising_edge_time = millis();
    }
    else if(last_state == 1 && state == 0)
    {
      state_changed_type = FALLING;
      last_falling_edge_time = millis();
    }
    last_state_diff_time = millis();
    last_state = state;

    if(divider_edge == CHANGE)
    {
      divider_counter++;
    }
    else
    {
      if(state_changed_type == divider_edge)
        divider_counter++;
    }
    return true;
  }
  else
  {
    state_changed_type = CHANGE;
    return false;
  }
}

bool Input::StateDiff() const
{
  return state_changed;
}

unsigned long Input::OnFor() const
{
  if(state)
    return millis() - last_rising_edge_time;
  return 0;
}

unsigned long Input::OffFor() const
{
  if(!state)
    return millis() - last_falling_edge_time;
  return 0;
}

void Input::Reset()
{
  state = last_state = false;
  counter = divider_counter = 0;
}

void Input::Print() const
{
  Serial.println(name);

  Serial.println(String("State: " + String(state, DEC)));
  Serial.println(String("Last_state: ") + String(last_state, DEC));
  Serial.println(String("Counter: ") + String(counter, DEC));
}

bool Input::IfTriggered() const
{
  if(divider_counter >= divider)
  {
    return true;
  }
  return false;
}

void Input::Update()
{
  if(IfTriggered())
  {
    divider_counter = 0;
  }
}