#include <Wire.h>

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'S','0','H','D'}
};

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

byte i = 0;

void setup()
{
	Serial.begin(9600);
  	Wire.begin();
  	for(i = 0; i < 8; i++)
  	{
   		pinMode(i,OUTPUT);
  	}
}

void loop()
{ 
	char keyPressed = kpd.getKey();
  	if(keyPressed){
      	Wire.beginTransmission(1);
  		Wire.write(keyPressed);
		Wire.endTransmission();
    } 
}