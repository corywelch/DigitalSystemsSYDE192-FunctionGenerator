//  
// Code Done for SYDE 192 - Presented to Professor On July 21st 2014
// 
// Code Done by Cory Welch, Sophia Castellarin, and Edrick Wong
// Department of Systems Design Engineering 1B Class (Class of 2018)
// University of Waterloo
//
// This code is allowed to be used by others without our direct permission. Just citation and credit to us is apprecitated.
  
#include <LiquidCrystal.h>

LiquidCrystal lcd(0,1,4,5,6,7);    //need pin 9 and 10 for pwn stuff so we can't use those
int redPin = 18;                    //leds
int bluePin = 19;
int greenPin = 3;
int yellowPin = 2;

int encoderV = 13;                  //home made encoders
int encoder1 = 11;
int encoder0 = 12;

int easterEggCode[] = {1,2,3,4,3,2,3,2,1};  //disable easter egg, coz it's not easter
int inputedCode[]  = {0,0,0,0,0,0,0,0,0};
int buttonPressed;
int spotInCode;
boolean buttonPress;
boolean codeAdded;


int speakerPin = 8; // sound output, maybe human factors and all


//info and vars for the display
long startTime;
long lastUpdate;
int timeInterval;
int period;
float frequency;
char frequencyChar[8];
float dutyCycle;
char dutyCycleChar[4];
int denom;
float freqFactor;

boolean isSine;
boolean isSquare;
boolean isTriangle;
boolean isSaw;

int b;
boolean w;

int wavePosition;
boolean showinfo;
boolean infoShown;
int fUnit;
//0 is mHz, 1 is Hz, 2 is kHz, 3 isMHz

//characters for the display +15%

//Square Characters
byte squarebottom[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B11111,B00000};
byte squaretop[8] = {B00000,B11111,B00000,B00000,B00000,B00000,B00000,B00000};
byte squarerise[8] = {B00000,B00111,B00100,B00100,B00100,B00100,B11100,B00000};
byte squarefall[8] = {B00000,B11100,B00100,B00100,B00100,B00100,B00111,B00000};

byte fullsquarerisebottom[8] = {B00100,B00100,B00100,B00100,B00100,B00100,B11100,B00000};
byte fullsquarerisetop[8] = {B00000,B00111,B00100,B00100,B00100,B00100,B00100,B00100};
byte fullsquarefallbottom[8] = {B00100,B00100,B00100,B00100,B00100,B00100,B00111,B00000};
byte fullsquarefalltop[8] = {B00000,B11100,B00100,B00100,B00100,B00100,B00100,B00100};

//Sine Characters
byte sinebottom[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B11111,B00000};
byte sinetop[8] = {B00000,B11111,B00000,B00000,B00000,B00000,B00000,B00000};
byte sinerise[8] = {B00000,B00000,B00011,B00100,B00100,B11000,B00000,B00000};
byte sinefall[8] ={B00000,B00000,B11000,B00100,B00100,B00011,B00000,B00000};

byte fullsinetop[8] = {B00000,B01110,B10001,B00000,B00000,B00000,B00000,B00000};
byte fullsinebottom[8] = {B00000,B00000,B00000,B00000,B00000,B10001,B01110,B00000};

byte fullsinerisebottom[8] = {B00100,B00100,B01000,B01000,B10000,B00000,B00000,B00000};
byte fullsinerisetop[8] = {B00000,B00000,B00000,B00001,B00010,B00010,B00100,B00100};
byte fullsinefallbottom[8] ={B00100,B00100,B00010,B00010,B00001,B00000,B00000,B00000};
byte fullsinefalltop[8] = {B00000,B00000,B00000,B10000,B01000,B01000,B00100,B00100};

//Triangle Characters
byte trianglebottom[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B10001,B00100};
byte triangletop[8] = {B00100,B10001,B00000,B00000,B00000,B00000,B00000,B00000};
byte trianglerise[8] = {B00000,B00000,B00001,B00010,B01000,B10000,B00000,B00000};
byte trianglefall[8] = {B00000,B00000,B10000,B01000,B00010,B00001,B00000,B00000};

byte fulltrianglebottom[8] = {B00000,B00000,B00000,B00000,B10001,B01010,B00100,B00000};
byte fulltriangletop[8] = {B00000,B00100,B01010,B10001,B00000,B00000,B00000,B00000};

byte fulltrianglerisebottom[8] ={B01000,B00000,B10000,B00000,B00000,B00000,B00000,B00000};
byte fulltrianglerisetop[8] = {B00000,B00000,B00000,B00000,B00000,B00001,B00000,B00010};
byte fulltrianglefallbottom[8] = {B00010,B00000,B00001,B00000,B00000,B00000,B00000,B00000};
byte fulltrianglefalltop[8] = {B00000,B00000,B00000,B00000,B00000,B10000,B00000,B01000};

//Saw Characters
byte sawbottom[8] = {B00000,B00000,B00000,B00001,B00010,B00100,B00100,B11100};
byte sawtop[8] = {B11100,B00100,B00100,B00010,B00001,B00000,B00000,B00000};
byte sawrise[8] = {B00001,B00110,B11000,B00000,B00000,B00000,B00000,B00000};
byte sawfall[8] = {B00000,B00000,B00000,B00000,B00000,B11000,B00110,B00001};

byte fullsawbottom[8] = {B00010,B00010,B00100,B00100,B00100,B00100,B00100,B11100};
byte fullsawtop[8] = {B11100,B00100,B00100,B00100,B00100,B00100,B00010,B00010};

byte fullsawriseleft[8] = {B00000,B00000,B00000,B00000,B00001,B00001,B00010,B00010};
byte fullsawrisetop[8] ={B00011,B01100,B10000,B00000,B00000,B00000,B00000,B00000};
byte fullsawfallbottom[8] = {B00000,B00000,B00000,B00000,B00000,B10000,B01100,B00011};
byte fullsawfallleft[8] = {B00010,B00010,B00001,B00001,B00000,B00000,B00000,B00000};


//wave table uses progmem for faster access, is stored in flash memories
const unsigned char sinewave_data[] PROGMEM = {

  0x80,0x83,0x86,0x89,0x8c,0x8f,0x92,0x95,0x98,0x9c,0x9f,0xa2,0xa5,0xa8,0xab,0xae,

  0xb0,0xb3,0xb6,0xb9,0xbc,0xbf,0xc1,0xc4,0xc7,0xc9,0xcc,0xce,0xd1,0xd3,0xd5,0xd8,

  0xda,0xdc,0xde,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xed,0xef,0xf0,0xf2,0xf3,0xf5,

  0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfc,0xfd,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,

  0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xfd,0xfc,0xfc,0xfb,0xfa,0xf9,0xf8,0xf7,

  0xf6,0xf5,0xf3,0xf2,0xf0,0xef,0xed,0xec,0xea,0xe8,0xe6,0xe4,0xe2,0xe0,0xde,0xdc,

  0xda,0xd8,0xd5,0xd3,0xd1,0xce,0xcc,0xc9,0xc7,0xc4,0xc1,0xbf,0xbc,0xb9,0xb6,0xb3,

  0xb0,0xae,0xab,0xa8,0xa5,0xa2,0x9f,0x9c,0x98,0x95,0x92,0x8f,0x8c,0x89,0x86,0x83,

  0x80,0x7c,0x79,0x76,0x73,0x70,0x6d,0x6a,0x67,0x63,0x60,0x5d,0x5a,0x57,0x54,0x51,

  0x4f,0x4c,0x49,0x46,0x43,0x40,0x3e,0x3b,0x38,0x36,0x33,0x31,0x2e,0x2c,0x2a,0x27,

  0x25,0x23,0x21,0x1f,0x1d,0x1b,0x19,0x17,0x15,0x13,0x12,0x10,0x0f,0x0d,0x0c,0x0a,

  0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x03,0x02,0x01,0x01,0x00,0x00,0x00,0x00,0x00,

  0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x02,0x03,0x03,0x04,0x05,0x06,0x07,0x08,

  0x09,0x0a,0x0c,0x0d,0x0f,0x10,0x12,0x13,0x15,0x17,0x19,0x1b,0x1d,0x1f,0x21,0x23,

  0x25,0x27,0x2a,0x2c,0x2e,0x31,0x33,0x36,0x38,0x3b,0x3e,0x40,0x43,0x46,0x49,0x4c,

  0x4f,0x51,0x54,0x57,0x5a,0x5d,0x60,0x63,0x67,0x6a,0x6d,0x70,0x73,0x76,0x79,0x7c};

unsigned char triangle_data[256];

void triangleWave(){
  for (int i = 0; i < 128; ++i) {
    triangle_data[i] = i*2;
  }
  int value = 255;
  for (int i = 128; i < 256; ++i) {
    triangle_data[i] = value;
    value -= 2;
  }
}

//sg keeps track of the position on the wave table
volatile unsigned long sg = 0;

//time elaspse since startip (millis)
volatile unsigned long  timer2_mil = 0;
//accumulated error since last correction
volatile unsigned char  timer2_frc = 0;
//keeps track of the overflow
volatile unsigned long timer2_overflow_cnt = 0;

//timer ticks every 4 us so overflow occurs every 1.024 microseconds
//we increase millis by one
int MILLIS_INC = 1;
//accumulated error in incrementor, check interrupt code for deets
int FRAC_INC = 3;
//max error we want, we read some article, so we stuck with it
int FRAC_MAX = 125;

//which wave
volatile int mode = 0;    // Mode of the function.
// 0 = square, 1 = sine, 2 = triangle, 3 = saw
float duty = 0.5;

//keeps track of frequency and pwm signal
long freq_pot;
long pwm_pot;

//not used, debug stuff
char initICR1;





void setup() {
  
    cli();  // stop interrupts from occuring during setup

  // stuff for millis
  TCCR2B = _BV(CS21) | _BV(CS20);    // Prescaler of 32
  TIMSK2 = _BV(TOIE2);              // allows us to setup interrupts on overflow of timer 2
  TCNT2 = 0;                        // set the timer value intitially to 0

  // stuff for pwm and frequency
  TCCR1A = _BV(COM1A1) | _BV(COM1B1);    //  allows you to do the top stuff so that you
  TCCR1B = _BV(WGM13) | _BV(CS11);       // can change frequency
  
  initICR1 = ICR1;
  
  ICR1 = 333;        // hard code, written over almost immediatley -> for testing

  //fills triangle wave table
  triangleWave();

  sei();  // Enable interrupts
  
  
  //Serial.begin(9600);
  lcd.clear();
  lcd.begin(16, 2); 
  startTime = fti();
  lastUpdate = 0.0;
  timeInterval = 300;
  period = 2000;//mseconds
  
  
  //used for animation and crap.
  
  spotInCode = 0;
  buttonPressed = 0;
  buttonPress = false;
  codeAdded = false;
  
  wavePosition = 0;
  showinfo = true;
  infoShown = false;
  
  isSquare = true;
  isSine = false;
  isTriangle = false;
  isSaw = false;
  
  
  //setup all the leds on startup
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  
  //setup all the encoders on startup
  pinMode(encoderV, INPUT);
  pinMode(encoder1, INPUT);
  pinMode(encoder0, INPUT);
  
  
  lcd.createChar(2,squarebottom);
  lcd.createChar(3,squaretop);
  lcd.createChar(4,squarerise);
  lcd.createChar(5,squarefall);
  
  
  lcd.createChar(6,fullsquarerisebottom);
  lcd.createChar(7,fullsquarerisetop);
  lcd.createChar(0,fullsquarefallbottom);
  lcd.createChar(1,fullsquarefalltop);
  
  digitalWrite(bluePin, HIGH);
  


  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  

  startupScreen();
  
  
}

void loop(){
  
  //values from the two pots
  freq_pot = analogRead(A0);
  pwm_pot = analogRead(A2);

  //maps the analog input of pot to frequency
  freq_pot = map(freq_pot, 0, 1023, 0, 10000);
  duty = pwm_pot/1000.0;
  ICR1 = freq_pot;
  // }
  
  if(duty != dutyCycle/100){
    infoShown = false;
  }
  
  if(ICR1*1.0 != period*1.0){
    period = ICR1*1.0;
    infoShown = false;
  }


  if (mode == 3){
    pinMode(9, INPUT);
    pinMode(10, OUTPUT);
  }
  else{
    pinMode(9, OUTPUT);
    pinMode(10, INPUT);  
  }
  
  
  //sets to sine wave
  if(digitalRead(encoderV) == HIGH && digitalRead(encoder1) == LOW && digitalRead(encoder0) == LOW){
      tone(speakerPin,523,50);
      isSine = true;
      isSquare = false;
      isTriangle = false;
      isSaw = false;
      mode = 1;
      buttonPressed = 1;
      buttonPress = true;
      digitalWrite(redPin, HIGH);
      digitalWrite(bluePin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, LOW);
  }
  //sets to square wave
  else if(digitalRead(encoderV) == HIGH && digitalRead(encoder1) == HIGH && digitalRead(encoder0) == LOW){
      tone(speakerPin,587,50);
      isSine = false;
      isSquare = true;
      isTriangle = false;
      isSaw = false;
      mode = 0;
      buttonPressed = 2;
      buttonPress = true;
      digitalWrite(redPin, LOW);
      digitalWrite(bluePin, HIGH);
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, LOW);
  }
  //sets to triangle wave
  else if(digitalRead(encoderV) == HIGH && digitalRead(encoder1) == LOW && digitalRead(encoder0) == HIGH){
      tone(speakerPin,659,50);
      isSine = false;
      isSquare = false;
      isTriangle = true;
      isSaw = false;
      mode = 2;
      buttonPressed = 3;
      buttonPress = true;
      digitalWrite(redPin, LOW);
      digitalWrite(bluePin, LOW);
      digitalWrite(greenPin, HIGH);  
      digitalWrite(yellowPin, LOW);  
  }
  //sets to basass wave
  else if(digitalRead(encoderV) == HIGH && digitalRead(encoder1) == HIGH && digitalRead(encoder0) == HIGH){
      tone(speakerPin,784,50);
      isSine = false;
      isSquare = false;
      isTriangle = false;
      isSaw = true;
      mode = 3;
      buttonPressed = 4;
      buttonPress = true;
      digitalWrite(redPin, LOW);
      digitalWrite(bluePin, LOW);
      digitalWrite(greenPin, LOW); 
      digitalWrite(yellowPin, HIGH);
  }
  else{
    buttonPress = false;
    codeAdded = false;
  }
  
  if(buttonPress && !codeAdded){
      codeAdded = true;
      if(spotInCode < 10){
          inputedCode[spotInCode] = buttonPressed;
          spotInCode++;
      }
      else{
          for(int c = 0; c < 9; c++){
              inputedCode[c] = inputedCode[c+1];
          }
          inputedCode[9] = buttonPressed;
      }
    /*    
  Serial.print("Inputed Code: ");
  Serial.print(inputedCode[0]);
  Serial.print(" ");
  Serial.print(inputedCode[1]);
  Serial.print(" ");
  Serial.print(inputedCode[2]);
  Serial.print(" ");
  Serial.print(inputedCode[3]);
  Serial.print(" ");
  Serial.print(inputedCode[4]);
  Serial.print(" ");
  Serial.print(inputedCode[5]);
  Serial.print(" ");
  Serial.print(inputedCode[6]);
  Serial.print(" ");
  Serial.print(inputedCode[7]);
  Serial.print(" ");
  Serial.println(inputedCode[8]);
  */
  }

  //easteregg, plays the superman theme if the hobbit theme is inputted with the buttons
  if(easterEggCode[0] == inputedCode[0] && easterEggCode[1] == inputedCode[1] && easterEggCode[2] == inputedCode[2] && easterEggCode[3] == inputedCode[3] && easterEggCode[4] == inputedCode[4] && easterEggCode[5] == inputedCode[5] && easterEggCode[6] == inputedCode[6] && easterEggCode[7] == inputedCode[7] && easterEggCode[8] == inputedCode[8]){
      easterEgg();
      for(int x = 0; x < 10; x++){
          inputedCode[x] = 0;
      }
  }
  
  //frequency that will be displayed on the screen
  frequency = abs((int)(1000000.0/period));
  if(frequency > 1000){
    frequency = (int)(frequency/1000.0);
    fUnit = 2; //kHz

  }
  else{
    fUnit = 1; //Hz
  }
  
  //Serial.println(frequency);
  itoa(frequency,frequencyChar,10); //prints frequency
  
  dutyCycle = duty * 100; //duty cycle
  //Serial.println(dutyCycle);
  itoa(dutyCycle,dutyCycleChar,10); //prints duty cyclt
  
    //stuff for animation on screen
    if(fti() - lastUpdate >= timeInterval){
        lastUpdate = fti();
        if(showinfo){
            if(isSquare){
              
              lcd.createChar(2,squarebottom);
              lcd.createChar(3,squaretop);
              lcd.createChar(4,squarerise);
              lcd.createChar(5,squarefall);
              
              printShort(wavePosition);
              
            }
            else if(isSine){
                lcd.createChar(2,sinebottom);
                lcd.createChar(3,sinetop);
                lcd.createChar(4,sinerise);
                lcd.createChar(5,sinefall);
 
                printShort(wavePosition);
            }
            else if(isTriangle){
                lcd.createChar(2,trianglebottom);
                lcd.createChar(3,triangletop);
                lcd.createChar(4,trianglerise);
                lcd.createChar(5,trianglefall);
                
                printShort(wavePosition);
            }
            else if(isSaw){
                lcd.createChar(2,sawbottom);
                lcd.createChar(3,sawtop);
                lcd.createChar(4,sawrise);
                lcd.createChar(5,sawfall);
                
                printShort(wavePosition);
            }
            if(!infoShown){
                lcd.setCursor(0,1);
                lcd.write("F:");
                lcd.write(frequencyChar);

                switch(fUnit){
                  case 1:
                      lcd.setCursor(5,1);
                      lcd.write(" Hz");
                  break;
                  case 2:
                      lcd.setCursor(3,1);
                      lcd.write("  kHz");
                  break;
              
                }
                lcd.setCursor(8,1);
                lcd.write(" DCy:");
                lcd.write(dutyCycleChar);
                lcd.write("%");
                infoShown = true;
            }
        }
        else{
          if(isSquare){
              lcd.createChar(2,squarebottom);
              lcd.createChar(3,squaretop);
              lcd.createChar(4,squarerise);
              lcd.createChar(5,squarefall);
  
              lcd.createChar(6,fullsquarerisebottom);
              lcd.createChar(7,fullsquarerisetop);
              lcd.createChar(0,fullsquarefallbottom);
              lcd.createChar(1,fullsquarefalltop);
              
              printFull(wavePosition);
          }
          else if(isSine){
              lcd.createChar(4,sinerise);
              lcd.createChar(5,sinefall);
  
              lcd.createChar(6,fullsinerisebottom);
              lcd.createChar(7,fullsinerisetop);
              lcd.createChar(0,fullsinefallbottom);
              lcd.createChar(1,fullsinefalltop);
  
              lcd.createChar(2,fullsinebottom);
              lcd.createChar(3,fullsinetop);
              
              printFull(wavePosition);
          }
          else if(isTriangle){
              lcd.createChar(6,fulltrianglerisebottom);
              lcd.createChar(7,fulltrianglerisetop);
              lcd.createChar(0,fulltrianglefallbottom);
              lcd.createChar(1,fulltrianglefalltop);
              
              lcd.createChar(2,fulltrianglebottom);
              lcd.createChar(3,fulltriangletop);
            
              printFull(wavePosition);
          }
          else if(isSaw){
              lcd.createChar(6,fullsawriseleft);
              lcd.createChar(7,fullsawrisetop);
              lcd.createChar(0,fullsawfallbottom);
              lcd.createChar(1,fullsawfallleft);
              
              lcd.createChar(2,fullsawbottom);
              lcd.createChar(3,fullsawtop);
            
              printFullSaw(wavePosition);
          }
          infoShown = false;
        }
        wavePosition++;
        if(wavePosition == 4){
            wavePosition = 0;
        }
    }
}
//prints half waves
void printShort(int startPoint){
      lcd.setCursor(0,0);
      switch (startPoint){
          case 0:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(2));
                  lcd.write(byte(4));
                  lcd.write(byte(3));
                  lcd.write(byte(5));
              }
              break;
          case 1:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(4));
                  lcd.write(byte(3));
                  lcd.write(byte(5));
                  lcd.write(byte(2));
              }
              break;
          case 2:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(3));
                  lcd.write(byte(5)); 
                  lcd.write(byte(2));
                  lcd.write(byte(4)); 
              }
              break;
          case 3:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(5));
                  lcd.write(byte(2));
                  lcd.write(byte(4));
                  lcd.write(byte(3));                     
               }
               break;     
      }
}
//prints full waves
void printFull(int startPoint){
      lcd.clear();
      lcd.setCursor(0,0);
      switch (startPoint){
          case 0:        
              for (int i = 0; i < 4; i++){
                  lcd.write(" ");
                  lcd.write(byte(7));
                  lcd.write(byte(3));
                  lcd.write(byte(1));
              }
              break;
          case 1:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(7));
                  lcd.write(byte(3));
                  lcd.write(byte(1));
                  lcd.write(" ");
              }
              break;
          case 2:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(3));
                  lcd.write(byte(1)); 
                  lcd.write(" ");
                  lcd.write(byte(7)); 
              }
              break;
          case 3:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(1));
                  lcd.write(" ");
                  lcd.write(byte(7));
                  lcd.write(byte(3));                     
               }
               break;     
      }
      lcd.setCursor(0,1);
      switch (startPoint){
          case 0:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(2));
                  lcd.write(byte(6));
                  lcd.write(" ");
                  lcd.write(byte(0));
              }
              break;
          case 1:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(6));
                  lcd.write(" ");
                  lcd.write(byte(0));
                  lcd.write(byte(2));
              }
              break;
          case 2:        
              for (int i = 0; i < 4; i++){
                  lcd.write(" ");
                  lcd.write(byte(0)); 
                  lcd.write(byte(2));
                  lcd.write(byte(6)); 
              }
              break;
          case 3:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(0));
                  lcd.write(byte(2));
                  lcd.write(byte(6));
                  lcd.write(" ");                     
               }
               break;     
      }
}
void printFullSaw(int startPoint){
      lcd.clear();
      lcd.setCursor(0,0);
      switch (startPoint){
          case 0:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(6));
                  lcd.write(byte(7));
                  lcd.write(byte(3));
                  lcd.write(" ");
              }
              break;
          case 1:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(7));
                  lcd.write(byte(3));
                  lcd.write(" ");
                  lcd.write(byte(6));
              }
              break;
          case 2:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(3));
                  lcd.write(" "); 
                  lcd.write(byte(6));
                  lcd.write(byte(7)); 
              }
              break;
          case 3:        
              for (int i = 0; i < 4; i++){
                  lcd.write(" ");
                  lcd.write(byte(6));
                  lcd.write(byte(7));
                  lcd.write(byte(3));                     
               }
               break;     
      }
      lcd.setCursor(0,1);
      switch (startPoint){
          case 0:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(2));
                  lcd.write(" ");
                  lcd.write(byte(1));
                  lcd.write(byte(0));
              }
              break;
          case 1:        
              for (int i = 0; i < 4; i++){
                  lcd.write(" ");
                  lcd.write(byte(1));
                  lcd.write(byte(0));
                  lcd.write(byte(2));
              }
              break;
          case 2:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(1));
                  lcd.write(byte(0)); 
                  lcd.write(byte(2));
                  lcd.write(" "); 
              }
              break;
          case 3:        
              for (int i = 0; i < 4; i++){
                  lcd.write(byte(0));
                  lcd.write(byte(2));
                  lcd.write(" ");
                  lcd.write(byte(1));                     
               }
               break;     
      }
}
//startup screen
void startupScreen(){
    char Function[9] = "Function";
    char Generator[10] = "Generator";
    int delayTime = 100;
    lcd.clear();
    lcd.setCursor(0,0);
    for(int i = 0; i < 8; i++){
        lcd.write(Function[i]);
        wait(delayTime);
    }
    lcd.setCursor(0,1);
    for(int i = 0; i < 9; i++){
        lcd.write(Generator[i]);
        wait(delayTime);
    }    
    for(int i = 0; i < 20; i++){
        wait(delayTime);
    }
    lcd.clear();
    char by[5] = "By: ";
    for(int i = 0; i < 4; i++){
        lcd.write(by[i]);
        wait(delayTime);
    }
    char Cory[5] = "Cory";
    for(int i = 0; i < 4; i++){
        lcd.write(Cory[i]);
        wait(delayTime);
    }
    lcd.write(",");
    wait(delayTime);
    lcd.write(" ");
    wait(delayTime);
    char Edrick[7] = "Edrick";
    for (int i = 0; i < 6; i++){
        lcd.write(Edrick[i]);
        wait(delayTime);
    }
    lcd.setCursor(0,1);
    lcd.write("&");
    wait(delayTime);
    lcd.write(" ");
    wait(delayTime);
    char Sophia[7] = "Sophia";
    for(int i = 0; i < 6; i++){
        lcd.write(Sophia[i]);
        wait(delayTime);
    }  
    for(int i = 0; i < 20; i++){
        wait(delayTime);
    }
    
}
//not used
void easterEgg(){
    //Serial.println("Easter Egg!!!!!!");
    
    ICR1 = initICR1;//not used
    
    int beat = 600;
    int halfBeat = beat/2;
    int tQuarterBeat = beat * 3 /4;
    int quarterBeat = beat/4;
    int tripBeat = beat/3;
    
    int c1 = 262;
    int g1 = 392;
    int c2 = 523;
    int d2 = 587;
    int e2 = 659;
    int f2 = 698;
    int g2 = 784;
    int gS2 = 831;
    int a2 = 880;
    int b2 = 988;
    int c3 = 1047;
    
    int notes[] = {g1,g1,c1,g1,g1,c2,g1,c1,g1,g1,c1,g1,g1,e2,d2,d2,g1,g1,c1,g1,g1,c2,g1,c1,c2,c2,c2,d2,d2,d2,gS2,g2,c2,g1,g1,g1,c2,c2,g2,g2,a2,g2,f2,g2,g1,g1,g1,c2,c2,g2,g2,a2,f2,d2,a2,g2,c2,c2,c2,c2,b2,g2,c2,c2,c2,b2,g2,c2,c2,c2,b2,a2,b2,c3,c2};
    int length[] = {beat,tripBeat,tripBeat,tripBeat,beat*2,beat,beat,beat*2,beat,tripBeat,tripBeat,tripBeat,beat*2,tQuarterBeat,quarterBeat,beat*3,beat,tripBeat,tripBeat,tripBeat,beat*2,beat,beat,beat*2,halfBeat,halfBeat,beat,halfBeat,halfBeat,beat+halfBeat,beat,halfBeat,beat,halfBeat,halfBeat,halfBeat,beat,halfBeat,2*beat + halfBeat,halfBeat,halfBeat,halfBeat,halfBeat,beat*4,halfBeat,halfBeat,halfBeat,beat,halfBeat,2*beat + halfBeat,halfBeat,halfBeat,halfBeat,halfBeat,halfBeat,beat*3+halfBeat,halfBeat,halfBeat,halfBeat,halfBeat,3*beat,beat+halfBeat,halfBeat,halfBeat,halfBeat,3*beat,beat+halfBeat,halfBeat,halfBeat,halfBeat,halfBeat,halfBeat,beat*2,beat*5};
    float tempo[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0.9,0.8,0.8,0.8,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
    
    wait(1000);
    lcd.clear();
    
    for(int x = 0; x < sizeof(notes)/sizeof(int); x++){
        lcd.write("A");
        tone(speakerPin,notes[x],length[x]*tempo[x]-50);        
        delay(length[x]*tempo[x]);
        noTone(speakerPin);

    }
    wait(1000);
    lcd.clear();
    infoShown = false;
    
    
    ICR1 = 333;
}

void wait(long x){
    long t = fti() + x;
   while (t > fti()){
    w = true;
   }
  w = false; 
}


unsigned long fti(){
  unsigned long m;
  uint8_t oldSREG = SREG;    // Get the register that holds all the event stuff

  cli();            // disable interrupts
  m = timer2_mil;         // get the time because that is the point of this function
  SREG = oldSREG;   // Set that register to how it was before...
  // shh, nothing happened here, carry on.

  return m;      // return the time scaled to milliseconds
}

ISR(TIMER2_OVF_vect){
  sg++;    // keeps track of stuff on wave table 

  unsigned long m = timer2_mil;    // gets the current time
  unsigned char f = timer2_frc;    // gets current error

  m += MILLIS_INC;         // increases time by 1 since math
  f += FRAC_INC;          // increments error
  if (f >= FRAC_MAX) {    // checks how much error there is, if it is over the dmax allowable error
    f -= FRAC_MAX;        // resets error counter
    m += 1;                // corrects for error
  }

// sets all the variables according to the above algorithm
  timer2_frc = f;              
  timer2_mil = m;
  timer2_overflow_cnt++;

  switch (mode){
    case(0):  // square wave
    OCR1A = ICR1*duty;
    break; 
    case(1):  // sine wave
    gen_sine();
    break;
    case(2):  // triangle wave
    gen_triangle();
    break;
    case(3):  // badass wave
    OCR1B = 0x7f;
    break;
  }  

}

void gen_triangle(){
  if (sg >= 258) {
    sg = -1;
  }
  else {
    OCR1A = triangle_data[sg];
  }
}

void gen_sine(){
  if (sg >= 256) {
    sg = -1;
  }
  else {
    OCR1A = pgm_read_byte(&sinewave_data[sg]);
  }
}
