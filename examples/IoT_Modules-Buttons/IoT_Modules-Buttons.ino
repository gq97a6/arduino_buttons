#include <IoT_Modules-Buttons.h>

ModulesButton buttonsHolder[4]; //Create holder for buttons of desired size
ModulesButtonsCollection buttons(buttonsHolder, 4); //Pass holder and its size

void setup()
{
  //optional debug mode can be enabled 
  //for errors to be displayed in serial monitor
  //Serial.begin() is required
  Serial.begin(115200);
  buttons.debugEnabled = true; 

  //first add buttons
  buttons.add(16); //just pin
  buttons.add(17, "red"); //named button with default inputMode
  buttons.add(18, INPUT); //inputMode to be applied
  buttons.add(19, INPUT, "green"); //named button

  //apply pinMode to all or one button, default = INPUT
  buttons.setPinMode(INPUT_PULLUP);
  buttons.setPinMode(0, INPUT_PULLUP);
  buttons.setPinMode("red", INPUT_PULLUP); //applies only to first button with that name

  //turn on inverted mode for one or all buttons (!digitalRead()) default = false
  buttons.invert(false); //to all
  buttons.invert(0, true); //by id
  buttons.invert("red", true); //applies only to first button with that name

  //every 'samplingInterval' milliseconds, status of button is refreshed, default = 10
  buttons.setSamplingInterval(10); //to all
  buttons.setSamplingInterval(0, 10); //by id
  buttons.setSamplingInterval("red", 10); //applies only to first button with that name
  
  //after changing the state, button "sleeps", for 'sleepInterval' milliseconds, default = 100
  //that prevents sudden changes, if 'sleepInterval' < than 'samplingInterval', 'samplingInterval' is applied instead
  buttons.setSleepInterval(100); //to all
  buttons.setSleepInterval(0, 100); //by id
  buttons.setSleepInterval("red", 100); //by name
}

void loop()
{
  buttons.handle(); //NEEDS TO BE CALLED IN LOOP <----------------------------------------------------- !!!
  
  ModulesButton buttonA = buttons.get(0);
  ModulesButton buttonB = buttons.get("red");
  
  bool foo;
  foo = buttonA.inverted; //isInverted
  foo = buttonA.state; //state of button
  foo = buttonA.ascending; //onAscending slope
  foo = buttonA.descending; //onDescending slope
  
  foo = buttons.isOnly(0, HIGH); //isOnly button that is e.g HIGH, by id
  foo = buttons.isOnly("red", HIGH); //isOnly button that is e.g HIGH, by name
  foo = buttons.areAll(LOW); //areAll buttons e.g LOW
  
  int bar;
  bar = buttons.getCount(); //how many buttons where added
  bar = buttons.howMany(HIGH); //how many buttons are e.g HIGH

  //is calculated based by saved changes, default = 20
  bar = buttons.hasChanged(0, 5000); //how many times buttons state has been ascending in last 5000 milliseconds, by id
  bar = buttons.hasChanged("red", 5000); //by name
  
  unsigned long foobar;
  foobar = buttons.getPhase(0); //how long, in milliseconds, is current state, by id
  foobar = buttons.getPhase("red"); //how long, in milliseconds, is current state, by name

  buttons.flushChanges(); //flush saved changes for all buttons
  buttons.flushChanges(0); //flush, by id
  buttons.flushChanges("red"); //flush, by name

  //e.g of using flushChanges()
  if (buttons.hasChanged("red", 5000) == 5)
  {
    buttons.flushChanges("red");
    Serial.println("Pressed 5 times.");
  }

  delay(10000);
}
