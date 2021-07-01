/* Arduino Door Security System with the Keypad and LCD
 * Made by Nevin Bullywon
 * June 18 2021
 */

// include all Libraries
#include <Keypad.h>
#include <Servo.h> 
#include <LiquidCrystal.h>

// Locate LED pins
#define redLED 10
#define greenLED 11

// define notes
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_C4  262

Servo servo_0; // define servo
char* password ="7658"; //my password
int pozisyon = 0;
const int openButtonPin = 13;     // location of openbuttonpin
const int closeButtonPin = 12;     // location of closebuttonpin
int openButtonState = 0;         // openbutton is off
int closeButtonState = 0;         // closebutton is off
const byte rows = 4; // numbers of rows on keypad
const byte cols = 4; // numbers of columns on keypad
int pos = 90; // angle of the servo


int melody[] = { // notes in the melody:
  NOTE_C4, NOTE_B3, NOTE_C4};

int noteDurations[] = {
  4, 4, 4};

char keyMap[rows][cols] = { //defining the keys
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[rows] = {1, 2, 3, 4};  // pins of the keypad
byte colPins[cols] = {5, 6, 7, 8};

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows, cols); 
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); // pins of the lcd

void setup () {
  lcd.begin(16,2);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  setLocked (true); //state of the password
  servo_0.attach(0); // servo attached to pin 0
  pinMode(openButtonPin, INPUT); // openbutton as input
  pinMode(closeButtonPin, INPUT);// closebutton as input
}

void loop() {
  char whichKey = myKeypad.getKey(); //define which key is pressed with getKey
  openButtonState = digitalRead(openButtonPin); 
  closeButtonState = digitalRead(closeButtonPin);  
  lcd.print("   Welcome");
  lcd.setCursor(0, 1);
  lcd.print("Enter the Code");

  if (whichKey == '*' || whichKey == '#' || whichKey == 'A' || whichKey == 'B' || whichKey == 'C') { //define invalid keys
    pozisyon=0;
    setLocked (true); //state of the password
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Error!");
    delay(1000);
    lcd.clear();
  }
  if (whichKey == password [pozisyon]) {
    pozisyon ++;
  }
  if (pozisyon == 4) { // if password is correct open the door
    setLocked (false);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*** Verified ***");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Nevin says");
    lcd.setCursor(0, 1);
    lcd.print(" You may come in");
    delay(1000);
	lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Door Opens");
	  
  for (int thisNote = 0; thisNote < 8; thisNote++) {    // iterate over the notes of the melody:
    int noteDuration = 1000 / noteDurations[thisNote];     // to calculate the note duration, take one second divided by the note type.
    tone(9, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30; // time between notes
    delay(pauseBetweenNotes);
    noTone(9); // stop note from playing
  }

 	

  for (pos = 90; pos >= 0; pos -= 1) {   // sweep the servo from 90 to 0 degrees in steps of 1 degrees
    servo_0.write(pos); // servo will move based off pos
    delay(15); // Wait for 15 millisecond(s)
  }
    lcd.clear();
    lcd.print(  "  Door Opened!");


    delay(1000);
  }
  
  if (openButtonState == HIGH) { // openbutton is pressed
    for (pos = 90; pos >= 0; pos -= 1) {  
    servo_0.write(pos); // tell servo to go to position in variable 'pos'
    delay(15); // Wait for 15 millisecond(s)
      }
    lcd.clear();
    lcd.print(  "  Door Opened!");
    
      for (int thisNote = 0; thisNote < 8; thisNote++) {    // iterate over the notes of the melody:
    int noteDuration = 1000 / noteDurations[thisNote];     // to calculate the note duration, take one second divided by the note type.
    tone(9, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30; // time between notes
    delay(pauseBetweenNotes);
    noTone(9); // stop note from playing
  }
    
    delay(1000);
    setLocked (false); //state of the password
  }
  
  if (closeButtonState == HIGH) {  // closebutton is pressed
  for (pos = 0; pos <= 90; pos += 1) {  // sweep the servo from 0 to 90 degrees in steps of 1 degrees
    servo_0.write(pos);     // tell servo to go to position in variable 'pos'
    delay(15); // Wait for 15 millisecond(s)
  }
    lcd.clear();
    lcd.print(  "  Door Closed!");
    delay(1000);
    lcd.clear();


    pozisyon = 0;
    setLocked (true);
    
  }
  
  if (whichKey == 'D') { // the D on the keypad will close the door
     for (pos = 0; pos <= 90; pos += 1) {  // sweep the servo from 0 to 90 degrees in steps of 1 degrees
    servo_0.write(pos);     // tell servo to go to position in variable 'pos'
    delay(15); // Wait for 15 millisecond(s)
  }
    lcd.clear();
    lcd.print(  "  Door Closed!");
    delay(1000);
    pozisyon = 0; // reset to zero so keypad will work again
    setLocked (true); //state of the password
  }
  
}

void setLocked(int locked) { // function to set red or green light on
  if (locked) {
    digitalWrite(redLED, HIGH); // redLED is on 
    digitalWrite(greenLED, LOW);
  }
  else{
    digitalWrite(redLED, LOW); 
    digitalWrite(greenLED, HIGH); //greenLED is on
  }
}                 
