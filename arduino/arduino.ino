/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Throtte
const int top_rate = 255;
const int full_throtte_distance = 10;
const int no_throttle_distance = 1;
const int throtte_pin = 2;

// debug
const bool enable_serial_debug = false;

int get_throtte_rate(float distance){
  if(distance < no_throttle_distance){
    return 0;
  }
  float actionable_range = (full_throtte_distance - no_throttle_distance);
  float rate = sqrt(top_rate) / actionable_range;
  float throtte_rate = sq((distance - no_throttle_distance) * rate);
  if (throtte_rate > top_rate){
    return top_rate;
  }
  return int(throtte_rate);
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Verae radar");
  // radar serial
  Serial1.begin(19200);
  // throtte pin
  pinMode(throtte_pin, OUTPUT); 

  // Serial debug
  if(enable_serial_debug){
    Serial.begin(19200);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
  }
  

}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  //recvWithStartEndMarkers();
  static float distance = 0;
  //static String distance_str;
  static String inString = "";    // string to hold speed input from serial line
  static bool firstTimeInLoop = true;
  if (firstTimeInLoop) {
    Serial1.write("ou");
    firstTimeInLoop = false;
  }
  if (Serial1.available() > 0) {
    int inChar = Serial1.read();
    // if it's the end of a line....
    if (inChar != '\n' && inChar != '\r') {
      // As long as the incoming byte is not a newline,
      // convert the incoming byte to a char and add it to the string
      inString += (char)inChar;
    }
    else {
      // if you get a newline with a reading, convert it to a float
      if (inString.length() > 1) {  // toss away blank lines
        distance = inString.toFloat();
        //distance = fabs(distance);
        if (distance < 0.1)
          distance = 0.0;
      }
      // clear the string for new input:
      inString = "";
    }
    //distance_str = String(distance);
    lcd.print(distance);
    float throtte_rate = get_throtte_rate(distance);
    Serial.println(throtte_rate);
    analogWrite(throtte_pin, throtte_rate);
  }
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);

  // Switch lights (just to test
  //digitalWrite(42, HIGH);
  //digitalWrite(43, LOW);
  //delay(100); 
  //digitalWrite(42, LOW);
  //digitalWrite(43, HIGH);
  //delay(100); 
}
