#include <Keypad.h>

#include <Wire.h>
#include <math.h>

#define LGHT 0
#define TMP 1

int distance = 200;
int lightSensorLimit = 6;
int tempSensorLimit = 25;

int State = 0; //1(A): távolság beálltása, 2(B): automata, 3(C): kézi vezérlés
bool is_open = true;

void setup()
{
  Wire.begin(1);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);  
  for(int i = 3; i < 10; i++){
    if(i == 8){
      continue;
    }
    pinMode(i,OUTPUT);
  }
  pinMode(LGHT,INPUT);
  pinMode(TMP,INPUT);
}

void loop()
{
  if(State == 2){
    int lightValue = analogRead(LGHT);
    int tempValue = map(((analogRead(TMP) - 20) * 3.04), 0, 1023, -40, 125); //celsius
    autoControl(tempValue, lightValue);
  }

  delay(450);
}


String mdist = "";
String mtemp = "";
String mlight = "";

bool secondInput = false;
void receiveEvent(int howMany){
  while (0 < Wire.available()){
    byte input = Wire.read();
    if(input > 64 && input < 69){ //betűk
    	stateChange(input); 
    }
    if(State == 1){
		setDistance(input);
    }
    if(State == 3){//manual
    	manualControl((char)input);
    }
    if(State == 4) {
    	setLightAndTempLimit(input);	
    }
  } 
}



//48-57-ig számok, 83:* 72:#
void stateChange(byte inputFromWire){
  switch((char)inputFromWire){
   case 'A': //távolság
    State = 1;
    Serial.println("Distance between the two motors:");
    break;
   case 'B': //automata
    State = 2;
    break;
   case 'C': //manual
    State = 3;
    break;
   case 'D':
    State = 4;
    Serial.println("Seting temperature and Light limit");
    break;
   default:
    break;
  }
}
int calculateRotationTime(){
  float circumference = 2*M_PI*5;
  float rotations = distance/circumference;
  float rotationsToSeconds = rotations*1.7;
  float delayInMS = rotationsToSeconds*100;
  return (int)delayInMS;
}


void manualControl(char inputFromWire){
  int d = calculateRotationTime();
  if(inputFromWire == 'H' && is_open){
    curtainIn(d);
    is_open = false;
  }
  else if(inputFromWire == 'S' && !is_open){
    curtainOut(d);
    is_open = true;
  }
}

void autoControl(int tempValue, int lightValue){
  int d = calculateRotationTime();
  	if((tempValue > tempSensorLimit && lightValue > lightSensorLimit) && is_open){
        curtainIn(d);
      	is_open = false;
    }
    else if((tempValue < tempSensorLimit && lightValue < lightSensorLimit) && !is_open){
      	curtainOut(d);
      	is_open = true;
    }
  }

void curtainIn(int d){  
  	digitalWrite(6,LOW);
    digitalWrite(4,HIGH);
    analogWrite(3,1);
        
    digitalWrite(7,HIGH);
    digitalWrite(9,LOW);
    analogWrite(5,1);
  
    delay(d);
  
  	digitalWrite(4,LOW);
    digitalWrite(7,LOW);
}
void curtainOut(int d)
{
    digitalWrite(6,HIGH);
    digitalWrite(4,LOW);
    analogWrite(3,1);
        
    digitalWrite(7,LOW);
    digitalWrite(9,HIGH);
    analogWrite(5,1);
    
    delay(d);
    
    digitalWrite(6,LOW);
    digitalWrite(9,LOW);
}

void setDistance(byte inputCommand){
    if(inputCommand > 47 && inputCommand < 58){ //távolság
    	mdist += (char)inputCommand;
    }
    else if((char)inputCommand == 'H'){
      	Serial.println("Cleared");
    	mdist = "";
    }
    else if((char)inputCommand == 'S'){
    	distance = mdist.toInt();
        Serial.println(distance);
        mdist = "";
    }
}
void setLightAndTempLimit(byte inputCommand) {
	switch(secondInput){
    	case false:
        	if(inputCommand > 47 && inputCommand < 58 && secondInput == false){
      			mtemp += (char)inputCommand;
                Serial.println("Temperature limit: " + mtemp);
    		}
          	else if((char)inputCommand == 'H'){
      			mtemp = "";
            	mlight = "";
          		Serial.println("Limits removed.");
                break;
            }
            else if((char)inputCommand == 'S' && secondInput == false){
            	tempSensorLimit = mtemp.toInt();
                Serial.println("Temperature limit set to: " + tempSensorLimit);
                mtemp = "";
               	secondInput = true;
                break;
    		}
   		case true:
    		if(inputCommand > 47 && inputCommand < 58 && secondInput == true){
      			mlight += (char)inputCommand;
                Serial.println("Light limit: " + mlight);
            }
          	else if((char)inputCommand == 'H'){
      			mtemp = "";
            	mlight = "";
                secondInput = false;
          		Serial.println("Limits removed.");
                break;
            }
            else if((char)inputCommand == 'S' && secondInput == true){
                lightSensorLimit = mlight.toInt();
                Serial.println("Light limit set to: " + lightSensorLimit);
                mlight = "";
                secondInput = false;
                break;
        	}
	}
}

  





