// =============================================
// 3-Digit Stopwatch
// Button A2
// 1 press = start
// 2 press = pause
// 3 press = reset to 000
// =============================================

const byte segmentPins[8] = {2,3,4,5,6,7,8,13};
const byte digitPins[3]   = {9,10,12};
const byte buttonPin = A2;

#define SEG_ON  HIGH
#define SEG_OFF LOW
#define DIG_ON  HIGH
#define DIG_OFF LOW


const byte digitMap[10][7] = {

{SEG_OFF,SEG_OFF,SEG_OFF,SEG_OFF,SEG_OFF,SEG_OFF,SEG_ON }, //0
{SEG_ON ,SEG_OFF,SEG_OFF,SEG_ON ,SEG_ON ,SEG_ON ,SEG_ON }, //1
{SEG_OFF,SEG_OFF,SEG_ON ,SEG_OFF,SEG_OFF,SEG_ON ,SEG_OFF}, //2
{SEG_OFF,SEG_OFF,SEG_OFF,SEG_OFF,SEG_ON ,SEG_ON ,SEG_OFF}, //3
{SEG_ON ,SEG_OFF,SEG_OFF,SEG_ON ,SEG_ON ,SEG_OFF,SEG_OFF}, //4
{SEG_OFF,SEG_ON ,SEG_OFF,SEG_OFF,SEG_ON ,SEG_OFF,SEG_OFF}, //5
{SEG_OFF,SEG_ON ,SEG_OFF,SEG_OFF,SEG_OFF,SEG_OFF,SEG_OFF}, //6
{SEG_OFF,SEG_OFF,SEG_OFF,SEG_ON ,SEG_ON ,SEG_ON ,SEG_ON }, //7
{SEG_OFF,SEG_OFF,SEG_OFF,SEG_OFF,SEG_OFF,SEG_OFF,SEG_OFF}, //8
{SEG_OFF,SEG_OFF,SEG_OFF,SEG_OFF,SEG_ON ,SEG_OFF,SEG_OFF}  //9

};


const unsigned int DIGIT_ON_US = 2000;
const unsigned int BLANK_US    = 150;



unsigned long startMillis = 0;
unsigned long pausedMs = 0;

bool running = false;
byte pressCount = 0;



bool lastReading = HIGH;
bool stableState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;



void setup()
{

for(byte i=0;i<8;i++)
{
pinMode(segmentPins[i],OUTPUT);
digitalWrite(segmentPins[i],SEG_OFF);
}

for(byte i=0;i<3;i++)
{
pinMode(digitPins[i],OUTPUT);
digitalWrite(digitPins[i],DIG_OFF);
}

pinMode(buttonPin,INPUT_PULLUP);

}



void loop()
{

handleButton();

unsigned long totalMs;


if(running)
totalMs = millis() - startMillis;

else
totalMs = pausedMs;



unsigned long totalSec = totalMs / 1000;

if(totalSec>599)
totalSec=599;



byte minutes = totalSec/60;
byte seconds = totalSec%60;

byte middleDigit = seconds/10;
byte rightDigit  = seconds%10;



if(minutes==0 && seconds<=9)
{

showDigit(rightDigit,2,false);
showDigit(rightDigit,2,false);
showDigit(rightDigit,2,false);

}

else if(minutes==0 && seconds>=10)
{

showDigit(middleDigit,1,false);
showDigit(rightDigit ,2,false);

}

else
{

showDigit(minutes    ,0,true);
showDigit(middleDigit,1,false);
showDigit(rightDigit ,2,false);

}

}




void handleButton()
{

bool reading = digitalRead(buttonPin);


if(reading != lastReading)
{
lastDebounceTime = millis();
lastReading = reading;
}



if((millis()-lastDebounceTime) > debounceDelay)
{

if(reading != stableState)
{

stableState = reading;


if(stableState == LOW)
{

pressCount++;



// 1 press = start
if(pressCount==1)
{

startMillis = millis() - pausedMs;
running = true;

}


// 2 press = pause
else if(pressCount==2)
{

pausedMs = millis() - startMillis;
running = false;

}


// 3 press = reset
else if(pressCount>=3)
{

pausedMs = 0;
running = false;
pressCount = 0;

}

}

}

}

}




void showDigit(byte value, byte digitIndex, bool dotOn)
{

allDigitsOff();
allSegmentsOff();

delayMicroseconds(BLANK_US);

setSegments(value,dotOn);

digitalWrite(digitPins[digitIndex],DIG_ON);

delayMicroseconds(DIGIT_ON_US);

digitalWrite(digitPins[digitIndex],DIG_OFF);

}



void setSegments(byte value, bool dotOn)
{

for(byte i=0;i<7;i++)
digitalWrite(segmentPins[i], digitMap[value][i]);

digitalWrite(segmentPins[7], dotOn ? SEG_OFF : SEG_ON);

}



void allDigitsOff()
{

for(byte i=0;i<3;i++)
digitalWrite(digitPins[i],DIG_OFF);

}



void allSegmentsOff()
{

for(byte i=0;i<8;i++)
digitalWrite(segmentPins[i],SEG_OFF);

}