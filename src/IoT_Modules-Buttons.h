#ifndef IOTM_BUTTONS_INCLUDED
#define IOTM_BUTTONS_INCLUDED

//Constants
#include "constants.h"

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class ModulesButton
{
  public:
    ModulesButton(int pin = 0, int _pinMode = 2, String name = "abc");

    int pin;
    int _pinMode; //1 INPUT, 2 OUTPUT, 5 INPUT_PULLUP

    int id;
    String name;
    unsigned long alarm;

    int sleepInterval = IOTM_BUTTONS_SLEEP;
    int samplingInterval = IOTM_BUTTONS_CHECK;

    bool inverted;
    bool state;
    bool ascending;
    bool descending;

    void setPinMode(int _pinMode);
    void handle();

    unsigned long changes[IOTM_BUTTONS_MAX_CHANGE];
    unsigned long phase;
};

class ModulesButtonsCollection
{
  public:
    ModulesButtonsCollection(ModulesButton *holder, int holderSize);

    bool debugEnabled;

    void add(int pin, int _pinMode = 1);
    void add(int pin,  String name);
    void add(int pin, int _pinMode, String name);

    void setPinMode(int _pinMode);
    void setPinMode(int id, int _pinMode);
    void setPinMode(String name, int _pinMode);

    void invert(bool inverted);
    void invert(int id, bool inverted);
    void invert(String name, bool inverted);

    void setSamplingInterval(int samplingInterval);
    void setSamplingInterval(int id, int samplingInterval);
    void setSamplingInterval(String name, int samplingInterval);

    void setSleepInterval(int sleepInterval);
    void setSleepInterval(int id, int sleepInterval);
    void setSleepInterval(String name, int sleepInterval);
    
    ModulesButton get(int id);
    ModulesButton get(String name);
    unsigned long getPhase(int id);
    unsigned long getPhase(String name);
    int getCount();

    bool isOnly(int id, bool state);
    bool isOnly(String name, bool state);

    bool areAll(bool state);
    int howMany(bool state);

    int hasChanged(int id, unsigned long time);
    int hasChanged(String name, unsigned long time);
    int flushChanges();
    int flushChanges(int id);
    int flushChanges(String name);

    void handle();

  private:
    int counter;
    int holderSize;
    ModulesButton *b;

    String textPinMode(int _pinMode);
    void debug(String text);
};
#endif