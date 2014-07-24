int pin=10;
// variable qualifier - variable 'state' will be loaded from RAM
volatile int state=LOW;

void setup(){
pinMode(pin,OUTPUT);
// parameter1 - interrupt (0 or 1)
// parameter2 - name of the interrupt handler function 
// parameter3 - trigger(CHANGE,LOW,RISING or FALLING)
attachInterrupt(0,handler,CHANGE);
}

void loop(){
digitalWrite(pin,state);
}
// interrupt handler function 
void handler(){
state=!state;
}
