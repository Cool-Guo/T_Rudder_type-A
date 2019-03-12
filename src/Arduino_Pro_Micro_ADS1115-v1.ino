//------------------------------------------------------------
// T_Rudder_type-A
// MCU: Arduino Pro Micro
// ADC: ADS1115
// Sersor: A1324LUA-T
// bin.guo@siid.ac.cn
// 2019-02-21 - V1
//------------------------------------------------------------

#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include "Joystick.h"

#define DELAY_TIME 10

// Rudder Setting
int16_t maxValue = 21400; // Input param
int16_t minValue = 1640;  // Input param

// ADS1115 Setting
Adafruit_ADS1115 ads;  
int16_t adc0; // Input from rudder
float multiplier = 0.1875F; // ADS1115  @ +/- 6.144V gain (16-bit results) 

// USB Joystick library Setting. Only using rudder axis
Joystick_ Joystick(0x12, 
  JOYSTICK_TYPE_JOYSTICK, 0, 0,
  false, false, false, false, false, false,
  true, false, false, false, false); 

void originalOut(int16_t value)
{
  if (value<minValue){
    Joystick.setRudder(minValue);
  }else if (value>maxValue){
    Joystick.setRudder(maxValue);
  }else{
    Joystick.setRudder(value);
  }
}  

void setup() {
  //Serial.begin(9600); //For setting the maxValue and minValue
  
  Joystick.setRudderRange(minValue, maxValue);
  Joystick.begin();
  ads.begin();
}

void loop() {
  adc0 = ads.readADC_SingleEnded(0);
  //Serial.print("AIN0: "); Serial.println(adc0); //For setting the maxValue and minValue
  //Serial.print("("); Serial.print(adc0 * multiplier); Serial.println("mV)");  //For setting the maxValue and minValue
  //Serial.println(" ");  //For setting the maxValue and minValue
  //convertRudder(adc0);  //For setting the maxValue and minValue
  originalOut(adc0);
  delay(DELAY_TIME);
}
