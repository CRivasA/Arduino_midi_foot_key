#include <MIDI.h>
#include "Controller.h"

int facc = 1;
const int analogInPin = A0;
int sensorValue = 0; 
int outputValue = 0;

MIDI_CREATE_DEFAULT_INSTANCE();
byte NUMBER_BUTTONS = 12;
//---How many potentiometers are connected directly to pins?--
Button BU1(2, 0, 12, 1, 5 );
Button BU2(3, 0, 13, 1, 5 );
Button BU3(4, 0, 14, 1, 5 );
Button BU4(5, 0, 15, 1, 5 );
Button BU5(6, 0, 16, 1, 5 );
Button BU6(7, 0, 17, 1, 5 );
Button BU7(8, 0, 18, 1, 5 );
Button BU8(9, 0, 19, 1, 5 );
Button BU9(10, 0, 20, 1, 5 );
Button BU10(11, 0, 21, 1, 5 );
Button BU11(12, 0, 22, 1, 5 );
Button BU12(13, 0, 23, 1, 5 );
//*******************************************************************
//Add buttons used to array below like this->  Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8};
Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8, &BU9, &BU10, &BU11, &BU12};
//*******************************************************************

void setup() {
  MIDI.begin(MIDI_CHANNEL_OFF);
  //Serial.begin(9600);
}

void loop() {
  
  if (NUMBER_BUTTONS != 0) updateButtons();

}

//*****************************************************************
void updateButtons() {
   sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 0, 1023, 5, 0);
  //Serial.print("sensor = ");
  //Serial.print(sensorValue);
  //Serial.print("\t output = ");
  //Serial.println(outputValue);
  facc = 12*outputValue;
  //Serial.println (ncp);

  // Cycle through Button array
  for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
    byte message = BUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      switch (BUTTONS[i]->Bcommand) {
        case 0: //Note
          MIDI.sendNoteOn(BUTTONS[i]->Bvalue+facc, 127, BUTTONS[i]->Bchannel);
          break;
        case 1: //CC
          MIDI.sendControlChange(BUTTONS[i]->Bvalue*facc, 127, BUTTONS[i]->Bchannel);
          break;
        case 2: //Toggle
          if (BUTTONS[i]->Btoggle == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue+facc, 127, BUTTONS[i]->Bchannel);
            BUTTONS[i]->Btoggle = 1;
          }
          else if (BUTTONS[i]->Btoggle == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue+facc, 0, BUTTONS[i]->Bchannel);
            BUTTONS[i]->Btoggle = 0;
          }
          break;
      }
    }
    //  Button is not pressed
    if (message == 1) {
      switch (BUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(BUTTONS[i]->Bvalue+facc, 0, BUTTONS[i]->Bchannel);
          break;
        case 1:
          MIDI.sendControlChange(BUTTONS[i]->Bvalue+facc, 0, BUTTONS[i]->Bchannel);
          break;}
        }
      }
    }
    
