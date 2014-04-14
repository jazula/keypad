#include <EEPROM.h>
#include <Keypad.h>

const int WRONG = 13;
const int THIRD = 12;
const int SEC = 11;
const int FIRST = 10;
boolean first = false;
boolean second = false;
boolean third = false;
  boolean firstt = true;
char code[3] = {
  '1', '2', '3'};
char key;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {
    '1','2','3','A'    }
  ,
  {
    '4','5','6','B'    }
  ,
  {
    '7','8','9','C'    }
  ,
  {
    '*','0','#','D'    }
};
byte rowPins[ROWS] = {
  2,3,4,5}; //connect to row pinouts
byte colPins[COLS] = {
  6,7,8,9}; //connect to column pinouts

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  pinMode(WRONG, OUTPUT);
  pinMode(FIRST, OUTPUT);
  pinMode(SEC, OUTPUT);
  pinMode(THIRD, OUTPUT);
  blinkLeds(5, "normal");
  allLeds(false);
  while (true){
    if(keypad.getKey() == '*'){
      break;
    }
  }
  while(!setCode()){   
  }
  
}

void loop(){    
}

boolean guessNumber(){
  int number = 0;
  first = false;
  second = false;
  third = false;
  int lednr;
  while(number < 2){
    if (number == 0){lednr = FIRST;}
    else if (number == 1){lednr = SEC;}
    else if (number == 2){lednr = THIRD;}
    key = NO_KEY;
    while (true){
      key = keypad.getKey();
      if (key == code[number]){
        if (number == 0){first = true;}
        else if (number == 1){second = true;}
        else if (number == 2){third = true;}
      }
      else if ((key != code[number]) && (key != NO_KEY)){
        
      }
    }
  }  
}

boolean setCode(){
  Serial.println("in set code");
  blinkLeds(5, "Good");
  allLeds(false);
  int at = 0;
  int atLed = FIRST;
  key = NO_KEY;
  while(at < 3){
    key = NO_KEY;
    while (key == NO_KEY){
      key = keypad.getKey();
      if (key == '*' || key == '#'){
        key = NO_KEY;
        allLeds(false);
        blinkLeds(10, "error");
        allLeds(false);
        return false;
      }
    }
    digitalWrite(atLed, HIGH);
    atLed = atLed + 1;
    code[at] = key;
    //EEPROM.write(at, key); 
    at++;
  }
  delay(300);
  key = NO_KEY;
  allLeds(false);
  return true;
}

void allLeds(boolean stat){
    if (stat == true){
      digitalWrite(WRONG, HIGH);
      digitalWrite(FIRST, HIGH);
      digitalWrite(SEC, HIGH);
      digitalWrite(THIRD, HIGH);
    }
    else {
      digitalWrite(WRONG, LOW);
      digitalWrite(FIRST, LOW);
      digitalWrite(SEC, LOW);
      digitalWrite(THIRD, LOW);
    }
  }

void blinkLeds(int times, String mode){
  for (int i = 0; i <= times; i++){
    if (mode == "normal"){
      allLeds(false);
      delay(100);
      allLeds(true);
      delay(100);
    }
    else if (mode == "Good"){
      allLeds(false);
      delay(100);
      digitalWrite(FIRST, HIGH);
      digitalWrite(SEC, HIGH);
      digitalWrite(THIRD, HIGH);
      delay(100);
    }
    else if (mode == "error"){
      allLeds(false);
      delay(100);
      digitalWrite(WRONG, HIGH);
      delay(100);
    }

  }
}


