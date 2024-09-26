/*-----------------------------------------------------------------------------
Camera Sync Controller
Takes Camera Pulses (Cam Pulse) as input.
Output pulses to alternatively trigger laser 1 (out1) & laser 2 (out2)

Remarks:
Allow 100us buffer time for each cycle. Eg. 1ms -> set PW = 900 us

Pin        321098    
PORTB = B00000000;
-----------------------------------------------------------------------------*/

//Libraries to be included
//Following 3 libraries used by LCD button shield module
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

//LCD button shield module declarations -------------
//Module uses I2C bus, A4/SDA, A5/SCL
//Create 'lcd' object
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
//All possible backlight colours
#define bg_Black  0x0
#define bg_Red    0x1
#define bg_Green  0x2
#define bg_Yellow 0x3
#define bg_Blue   0x4
#define bg_Violet 0x5
#define bg_Teal   0x6 //medium blue-green color, similar to cyan
#define bg_White  0x7
//LCD shield variables
boolean cursorState = false;
boolean blinkState  = false;
uint8_t lcdButtons;

//--------------------------------------------------
//Hardware control pin/s
const byte statusLedPin = 13; //For showing status.
const byte itrPin  =  3; //interrupt pin : 2 or 3 on UNO
const byte out1Pin =  8;
const byte out2Pin =  9;
/* 
Unused: program currently alternate 2 lasers
const byte out3Pin = 10; 
const byte out4Pin = 11; 
*/

//DON'T USE millis() INSIDE ISR !!
//Variable used within ISR must be declared as 'volatile'
//0:Setting mode, 1-4:Acquisition mode
//0:Check PW inputs & update PW accordingly.
//1:Ready to receive Cam Pulse trigger.
//2:Triggered. Check if T1 had elasped.
//3:Required output set High. Check if T2 had elasped.
//4:Required PW generated. Check if Cam Pulses 'stopped'.


volatile byte sysState = 0;
volatile uint32_t trgTickus = 0;

//Other declarations --------------------------------
boolean out1On = false;
const long usStepLarge =   1000;
const long usStepSmall =     50;
const long durT2usMin  =     50;
const long durT2usMax  = 200000;
const long durT1us     =     30;
long       durT2us     =    900;
long       durT1pT2us  = 0; //durT1us + durT2us

const long camPulseNoOpsDur = 1000;
long       camPulseCount    = 0;
long       camPulseRiseTick = 0;
const long selButChkInt = 100;
long       selButTick = 0;
String text;
int i = 0;

////////////////////////////////////////////////////////////////////////////////
void isrD3Rise() {
PORTB = B00000000; //force pin 8-13 low (as it might still be high). Will not occur if user match T2 < camera exposure time. Procced to do in Settings mode
sysState = 2;
trgTickus = micros();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                    Main program (endless loop)
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void loop() {
if (sysState==2){
  //After Cam Pulse detected.
  //If duration T1 elasped, start a pulse on the required pin
  if(micros()-trgTickus > durT1us){  
    if (out1On){
      //PORTB = B00000010; //pin 9 high, pin 8,10-13 low
      PORTB = B00100010; //pin 9 & 13 high, pin 8,10,11,12 low
      out1On = false;
    }
    else {
      //PORTB = B00000001; //pin 8 high, pin 9-13 low
      PORTB = B00100001; //pin 8 & 13 high, pin 9,10,11,12 low
      out1On = true;
    }
    //Cam Pulse -----
    camPulseRiseTick = millis(); //appro. tick when Cam pulse was detected
    camPulseCount++; //Count no. of Cam Pulses
    //Others -----
    sysState = 3;
  }
}//sysState==2
//If generated pulse reached required PW, set output to low.
else if (sysState==3){
  if(micros()-trgTickus > durT1pT2us){//TODO: possible bug. Cycle could take too long. micros()-trgTickus >> durT1pT2us. Increase frequency of checking will solve the issue
    //TODO: possible bug here; what happen when interrupt pin 3 gets called while if statement undone
    //Turn off outputs
    PORTB = B00000000; //set pin 8-13 low
    sysState = 4;
  }
}//sysState==3 //TODO: please remove sysState=3. shift checking inside sysState=2
//Completed generating pulse. If Cam Pulses 'stopped'. Do related stuff.
else if (sysState==4){
  if (camPulseRiseTick > 0){
    if (millis()-camPulseRiseTick > camPulseNoOpsDur){
      isrDisable(); //Disable all ISRs
      //Show no. of Cam Pulses detected
      lcd.setBacklight(bg_Red);
      showLcdLine2("                ");
      delay(500);
      showLcdLine2("FR:" + String(camPulseCount));
      delay(1000);
      lcd.setBacklight(bg_Green);
      //Update these
      resetParam();
      sysState = 1;
      selButTick = millis();
      isrEnable(); //Enable all ISRs
    }
  }
}//sysState==4
//Setting mode.
else if (sysState==0){
  checkButInputs();
}//sysState==0
//Ready to receive Camp Pulse.
//At regular interval, check if user wants to go back to setting mode.
else if (sysState==1){
  if (millis()-selButTick > selButChkInt){
    lcdButtons = lcd.readButtons();
    if (lcdButtons & BUTTON_SELECT) {
      activateSettingMode(); //Activate Setting mode
    }
    else {
      selButTick = millis();
    }
  }
}//sysState==1

}//loop
