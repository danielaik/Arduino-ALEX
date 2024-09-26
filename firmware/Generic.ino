//------------------------------------------------------------------------------
// Generic Functions
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
//Enable all ISRs
void isrEnable() {
attachInterrupt(digitalPinToInterrupt(itrPin), isrD3Rise, RISING);
}

////////////////////////////////////////////////////////////////////////////////
//Disable all ISRs
void isrDisable() {
detachInterrupt(digitalPinToInterrupt(itrPin));
}

////////////////////////////////////////////////////////////////////////////////
//Activate Setting mode
void activateSettingMode() {
isrDisable(); //Disable all ISRs
sysState = 0;
lcd.setBacklight(bg_White);
showLcdLine1("PW:" + String(durT2us));
delay(1000);
}

////////////////////////////////////////////////////////////////////////////////
//Activate Acquisition mode
void activateAcquisitionMode() {
sysState = 1;
lcd.setBacklight(bg_Green);
showLcdLine2("FR:0            ");
delay(1000);
isrEnable(); //Enable all ISRs
}

////////////////////////////////////////////////////////////////////////////////
//Reset parameters
void resetParam() {
  camPulseCount = 0;
  camPulseRiseTick = 0;
  out1On = false;
}

//------------------------------------------------------------------------------
//                           Setup
//------------------------------------------------------------------------------
void setup() {
//Serial.begin(115200);
//Serial.println("Setting up");

pinMode(statusLedPin, OUTPUT);
digitalWrite(statusLedPin, LOW);//initial LED state
pinMode(out1Pin, OUTPUT);
digitalWrite(out1Pin, LOW);
pinMode(out2Pin, OUTPUT);
digitalWrite(out2Pin, LOW);
/* unused pin
pinMode(out3Pin, OUTPUT);
digitalWrite(out3Pin, LOW);
pinMode(out4Pin, OUTPUT);
digitalWrite(out4Pin, LOW);
*/
//Cam Pulse comes into itrPin.
pinMode(itrPin, INPUT);

lcd_Setup();
lcd.clear();
lcd.setBacklight(bg_Green);
//         123456789a123456
showLcdLine1("Laser-Cam Sync");
showLcdLine2("v 1.3.0");
delay(3000);
lcd.clear();

for (i=0; i<3; i++){
  digitalWrite(statusLedPin, HIGH);
  delay(100);
  digitalWrite(statusLedPin, LOW);
  delay(100);
}

updatePW();
showLcdLine2("FR:0            ");
activateSettingMode(); //Activate Setting mode
}
