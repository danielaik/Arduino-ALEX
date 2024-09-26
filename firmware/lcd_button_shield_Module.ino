//------------------------------------------------------------------------------
// Declarations & Functions related to Adafruit RGB Character LCD Shield
//------------------------------------------------------------------------------
//lcd.clear();
//lcd.setCursor(0,0); //set cursor to col 0, line 0 (1st line)
//lcd.setCursor(0,1); //set cursor to col 0, line 1 (2nd line)
//lcd.print("123456789a123456");
//         123456789a123456

////////////////////////////////////////////////////////////////////////////////
//Show text on LCD line 1, eg PW
void showLcdLine1(String text) {
lcd.setCursor(0,0); //set cursor to col 0, line 0 (1st line)
lcd.print(text);
}

////////////////////////////////////////////////////////////////////////////////
//Show text on LCD line 2, eg FR
void showLcdLine2(String text) {
lcd.setCursor(0,1); //set cursor to col 0, line 1 (2nd line)
lcd.print(text);
}

////////////////////////////////////////////////////////////////////////////////
//Check button inputs & update variables, display accordingly...
void checkButInputs() {
boolean durChanged = false;
//Check if any of the 5 button pressed
lcdButtons = lcd.readButtons();
if (lcdButtons) {//At least 1 of the but pressed
  if (lcdButtons & BUTTON_UP) {
    durChanged = true;
    durT2us = durT2us + usStepLarge;
    if (durT2us > durT2usMax){
      durT2us = durT2usMax;  }
  }
  if (lcdButtons & BUTTON_DOWN) {
    durChanged = true;
    durT2us = durT2us - usStepLarge;
    if (durT2us < durT2usMin){
      durT2us = durT2usMin;  }
  }
  if (lcdButtons & BUTTON_LEFT) {
    durChanged = true;
    durT2us = durT2us - usStepSmall;
    if (durT2us < durT2usMin){
      durT2us = durT2usMin;  }
  }
  if (lcdButtons & BUTTON_RIGHT) {
    durChanged = true;
    durT2us = durT2us + usStepSmall;
    if (durT2us > durT2usMax){
      durT2us = durT2usMax;  }
  }
  if (durChanged){
    updatePW();}
  if (lcdButtons & BUTTON_SELECT) {
    activateAcquisitionMode(); //Activate Acquisition mode
  }
}//if (lcdButtons)
}

////////////////////////////////////////////////////////////////////////////////
//Update PW related variables, Show PW on LCD...
void updatePW() {
durT1pT2us = durT1us + durT2us; 
showLcdLine1("PW:             ");
showLcdLine1("PW:" + String(durT2us)); 
delay(200);
}

////////////////////////////////////////////////////////////////////////////////
void lcd_Setup() {
//set up the LCD's number of columns and rows: 
lcd.begin(16, 2);
//lcd.setBacklight(bg_White);
lcd.setBacklight(bg_Black);

//Cursor position is always to the right of the most recently printed char.
//('lcd.print()' command). 
//Cursor setting
//visible : seen as an underscore
//blink   : an alternating black/white square at cursor position
//**cursor visible only if 'lcd.print()' command NOT continuously issued**
lcd.noCursor(); //turns cursor off
//lcd.cursor();   //turns cursor on
lcd.noBlink();  //turns off cursor blink
//lcd.blink();    //turns on cursor blink
}
