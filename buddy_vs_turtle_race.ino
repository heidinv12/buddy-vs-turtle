#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

//global variables
int buzzer = 7;
int buttonOnePin = 8;
int buttonTwoPin = 9;
int buddyPosition = 0;
int turtlePosition = 0;

byte turtle[] = {
  B01110,
  B00110,
  B00110,
  B11111,
  B01110,
  B01110,
  B01010,
  B10010
};

byte buddy[]{
  B00111,
  B00101,
  B00111,
  B11100,
  B11110,
  B11100,
  B01010,
  B01010
};

byte goal[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B01110,
  B00100,
  B00100
};

void setup(){
  lcd.begin(16,2);
  pinMode(buttonOnePin, INPUT);
  pinMode(buttonTwoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  lcd.createChar(0,turtle);
  lcd.createChar(1,buddy);
  lcd.createChar(2,goal);
}

void loop(){
  countDown();
  shiftBuddies();
}

/*
 * Intro sequence. Counts 3
 * down to 1, while triggering
 * the buzzer for every number.
 */
void countDown(){
  for(int i=3; i>0; i--){
    lcd.setCursor(7, 0);
    char a = '0'+ i;
    digitalWrite(buzzer, HIGH);
    lcd.print(a);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    lcd.clear();
  }
}

/** 
* shifts characters on the lcd every time
* a button is pushed.
**/
void shiftBuddies(){
    for(int i=buddyPosition; i<=14; i++){
      // Set current possiton
      lcd.setCursor(buddyPosition, 0);
      lcd.write(byte(0)); 
      lcd.setCursor(turtlePosition,1);
      lcd.write(byte(1));

      // set goal character
      lcd.setCursor(15, 0);
      lcd.write(byte(2)); 
      lcd.setCursor(15,1);
      lcd.write(byte(2)); 

      // Shifts buddy character if 
      // top-button input is set to HIGH
      if(readButton(0)==HIGH){
        lcd.setCursor(buddyPosition,0);
        lcd.print(" ");
        buddyPosition++;
        lcd.setCursor(buddyPosition,0);
        lcd.write(byte(0)); 
        delay(240);
      }

      // Shifts turtle character if 
      // bottom-button input is set to HIGH
      if(readButton(1)==HIGH){
        lcd.setCursor(turtlePosition,1);
        lcd.print(" ");
        turtlePosition++;
        lcd.setCursor(turtlePosition,1);
        lcd.write(byte(1)); 
        delay(230);
      }

      // i is dependent on the possiton of
      // character that ahs made it further
      if (turtlePosition>=buddyPosition){
        i=turtlePosition;
      } else{
        i = buddyPosition;
      }
    }

    // The character that reached last 
    // lcd grid before goal wins
    digitalWrite(buzzer, HIGH);
    if (buddyPosition==14){
      lcd.clear();
      lcd.print("PLAYER 1 WON!!");
    } else{
      lcd.clear();
      lcd.print("PLAYER 2 WON!!");
    }
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(5000);
    lcd.clear();
    
    //reset buddies position
    buddyPosition = 0;
    turtlePosition = 0;
}

/*
 * Reads input value form button
 */
bool readButton(int val){
  bool result;
  if (val==0){
   return digitalRead(buttonOnePin);
  }else if(val==1){
    return digitalRead(buttonTwoPin);
  }
}
