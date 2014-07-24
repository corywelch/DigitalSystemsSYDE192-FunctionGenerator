int led = 13;
int photo = 2;
volatile int state = 2;

void setup(){
  pinMode(led, OUTPUT);  
  attachInterrupt(0, handler, CHANGE);
}

void loop(){
  digitalWrite(led, state-1);
}

void handler(){
  state = (state%2)+1; 
}
