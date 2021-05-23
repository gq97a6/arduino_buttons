#include "IoT_Modules-Buttons.h"

//Single button

ModulesButton::ModulesButton(int pin, int _pinMode, String name)
{
}

void ModulesButton::setPinMode(int _pinMode)
{
  if (_pinMode == 1 || _pinMode == 2 || _pinMode == 5)
  {
    pinMode(pin, _pinMode);
    this->_pinMode = _pinMode;
  }
}

void ModulesButton::handle()
{
}

//Array of buttons

ModulesButtonsCollection::ModulesButtonsCollection(ModulesButton *holder, int holderSize)
{
  this->b = holder;
  this->holderSize = holderSize;
}

void ModulesButtonsCollection::add(int pin, int _pinMode)
{
  add(pin, _pinMode, "");
}

void ModulesButtonsCollection::add(int pin, String name)
{
  add(pin, 1, name);
}

void ModulesButtonsCollection::add(int pin, int _pinMode, String name)
{
  if (counter < holderSize)
  {
    b[counter].pin = pin;

    if (_pinMode == 1 || _pinMode == 2 || _pinMode == 5)
    {
      b[counter].setPinMode(_pinMode);
    }
    else
    {
      debug("There is no such pin mode: " + String(_pinMode));
    }

    b[counter].name = name;
    b[counter].id = counter;

    counter++;
  }
  else
  {
    debug("You have reached maximum amount of buttons!");
  }
}

void ModulesButtonsCollection::setPinMode(int _pinMode)
{
  if (_pinMode == 1 || _pinMode == 2 || _pinMode == 5)
  {
    for (int i = 0; i < counter; i++)
    {
      b[i].setPinMode(_pinMode);
    }
  }
  else
  {
    debug("There is no such pin mode: " + String(_pinMode));
  }
}

void ModulesButtonsCollection::setPinMode(int id, int _pinMode)
{
  if (id < counter)
  {
    b[id].setPinMode(_pinMode);
  }
  else
  {
    debug("No button with given id.");
  }
}

void ModulesButtonsCollection::setPinMode(String name, int _pinMode)
{
  if (name == "")
  {
    debug("Empty name given.");
    return;
  }

  for (int i = 0; i < counter; i++)
  {
    if (b[i].name == name)
    {
      b[i].setPinMode(_pinMode);
      return;
    }
  }

  debug("No button with given name.");
}

void ModulesButtonsCollection::invert(bool inverted)
{
  for (int i = 0; i < counter; i++)
  {
    b[i].inverted = inverted;
  }
}

void ModulesButtonsCollection::invert(int id, bool inverted)
{
  if (id < counter)
  {
    b[id].inverted = inverted;
  }
  else
  {
    debug("No button with given id.");
  }
}

void ModulesButtonsCollection::invert(String name, bool inverted)
{
  if (name == "")
  {
    debug("Empty name given.");
    return;
  }

  for (int i = 0; i < counter; i++)
  {
    if (b[i].name == name)
    {
      b[i].inverted = inverted;
      return;
    }
  }

  debug("No button with given name.");
}

void ModulesButtonsCollection::setSamplingInterval(int samplingInterval)
{
  for (int i = 0; i < counter; i++)
  {
    b[i].samplingInterval = samplingInterval;
  }
}

void ModulesButtonsCollection::setSamplingInterval(int id, int samplingInterval)
{
  if (id < counter)
  {
    b[id].samplingInterval = samplingInterval;
  }
  else
  {
    debug("No button with given id.");
  }
}

void ModulesButtonsCollection::setSamplingInterval(String name, int samplingInterval)
{
  if (name == "")
  {
    debug("Empty name given.");
    return;
  }

  for (int i = 0; i < counter; i++)
  {
    if (b[i].name == name)
    {
      b[i].samplingInterval = samplingInterval;
      return;
    }
  }

  debug("No button with given name.");
}

void ModulesButtonsCollection::setSleepInterval(int sleepInterval)
{
  for (int i = 0; i < counter; i++)
  {
    b[i].sleepInterval = sleepInterval;
  }
}

void ModulesButtonsCollection::setSleepInterval(int id, int sleepInterval)
{
  if (id < counter)
  {
    b[id].sleepInterval = sleepInterval;
  }
  else
  {
    debug("No button with given id.");
  }
}

void ModulesButtonsCollection::setSleepInterval(String name, int sleepInterval)
{
  if (name == "")
  {
    debug("Empty name given.");
    return;
  }

  for (int i = 0; i < counter; i++)
  {
    if (b[i].name == name)
    {
      b[i].sleepInterval = sleepInterval;
      return;
    }
  }

  debug("No button with given name.");
}

ModulesButton ModulesButtonsCollection::get(int id)
{
  if (id < counter)
  {
    return b[id];
  }
  else
  {
    debug("No button with given id, returning dummy button.");

    ModulesButton button(0, 5, "");
    return button;
  }
}

ModulesButton ModulesButtonsCollection::get(String name)
{
  if(name == "")
  {
    debug("Empty name given, returning dummy button.");

    ModulesButton button(0, 5, "");
    return button;
  }

  for (int i = 0; i < counter; i++)
  {
    if (b[i].name == name)
    {
      return b[i];
    }
  }

  debug("No button with given name, returning dummy button.");

  ModulesButton button(0, 5, "");
  return button;
}

unsigned long ModulesButtonsCollection::getPhase(int id)
{
  return millis() - get(id).phase;
}

unsigned long ModulesButtonsCollection::getPhase(String name)
{
  return millis() - get(name).phase;
}

int ModulesButtonsCollection::getCount()
{
  return counter;
}

bool ModulesButtonsCollection::isOnly(int id, bool state)
{
  if (id >= counter)
  {
    debug("No button with given id, returning false.");
    return false;
  }

  if (b[id].state == state)
  {
    for (int i = 0; i < counter; i++)
    {
      if (b[i].state == state && i != id)
      {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool ModulesButtonsCollection::isOnly(String name, bool state)
{
  if (name == "")
  {
    debug("Empty name given, returning false.");
    return false;
  }

  if (get(name).state == state)
  {
    for (int i = 0; i < counter; i++)
    {
      if (b[i].state == state && i != get(name).id)
      {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool ModulesButtonsCollection::areAll(bool state)
{
  for (int i = 0; i < counter; i++)
  {
    if (b[i].state != state)
    {
      return false;
    }
  }

  return true;
}

int ModulesButtonsCollection::howMany(bool state)
{
  int c = 0;
  
  for (int i = 0; i < counter; i++)
  {
    if (b[i].state == state)
    {
      c++;
    }
  }

  return c;
}

int ModulesButtonsCollection::hasChanged(int id, unsigned long time)
{
  ModulesButton b = get(id);
  int c = 0;

  for (int i = 0; i < IOTM_BUTTONS_MAX_CHANGE; i++)
  {
    if (b.changes[i] >= millis() - time)
    {
      c++;
    }
  }

  return c;
}

int ModulesButtonsCollection::hasChanged(String name, unsigned long time)
{
  ModulesButton b = get(name);
  int c = 0;

  for (int i = 0; i < IOTM_BUTTONS_MAX_CHANGE; i++)
  {
    if (b.changes[i] >= millis() - time)
    {
      c++;
    }
  }

  return c;
}

int ModulesButtonsCollection::flushChanges()
{
  for (int i = 0; i < counter; i++)
  {
    for (int ii = 0; ii < IOTM_BUTTONS_MAX_CHANGE; ii++)
    {
      b[i].changes[ii] = 0;
    }
  }
}

int ModulesButtonsCollection::flushChanges(int id)
{
  for (int i = 0; i < IOTM_BUTTONS_MAX_CHANGE; i++)
  {
    b[id].changes[i] = 0;
  }
}

int ModulesButtonsCollection::flushChanges(String name)
{
  for (int i = 0; i < IOTM_BUTTONS_MAX_CHANGE; i++)
  {
    b[get(name).id].changes[i] = 0;
  }
}

String ModulesButtonsCollection::textPinMode(int _pinMode)
{
  if (_pinMode = 1)
  {
    return "INPUT";
  }
  else if (_pinMode = 2)
  {
    return "OUTPUT";
  }
  else if (_pinMode = 5)
  {
    return "INPUT_PULLUP";
  }
  else
  {
    return "?";
  }
}

void ModulesButtonsCollection::debug(String text)
{
  if (debugEnabled == true)
  {
    Serial.println();

    Serial.print("ModulesButtons: ");
    Serial.println(text);

    Serial.println();
  }
}

void ModulesButtonsCollection::handle()
{
  for (int i = 0; i < counter; i++)
  {
    //Clear phase after descending slope
    if(b[i].descending) {
      b[i].phase = millis();
    }
    
    //Clear slopes
    b[i].ascending = 0;
    b[i].descending = 0;
    
    //Process data only on demand
    if (b[i].alarm > millis())
    {
      continue;
    }

    bool state;
    if (b[i].inverted) //1. Read state, invert if necessary
    {
      state = !digitalRead(b[i].pin);
    }
    else
    {
      state = digitalRead(b[i].pin);
    }

    int sleep = 0;
    if (b[i].state != state) //2. Slope check
    {
      sleep = b[i].sleepInterval;

      if (state)
      {
        b[i].ascending = 1;
  
        //Shift array
        for (int ii = IOTM_BUTTONS_MAX_CHANGE - 1; ii > 0; ii--)
        {
          b[i].changes[ii] = b[i].changes[ii - 1];
        }

        //Save the change
        b[i].changes[0] = millis();
      }
      else
      {
        b[i].descending = 1;
      }

      //Clear phase before on ascending slope
      if(b[i].ascending) {
        b[i].phase = millis();
      }
    }

    //Sleep after change or wait for next interval.
    if (sleep >= b[i].samplingInterval)
    {
      b[i].alarm = millis() + sleep;
    }
    else
    {
      b[i].alarm = millis() + b[i].samplingInterval;
    }

    //Save state
    b[i].state = state;
  }
}