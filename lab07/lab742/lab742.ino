int poll = 4;
int i = 0;
int j = 0;
volatile int state = 1;

void setup(){
  pinMode(poll, INPUT);
  attachInterrupt(0, handler, CHANGE);
  
  Serial.begin(9600);
}

void loop(){
  
    j = 0;
    
    //Polling pin 4
    // Detect high
    if (digitalRead(poll) == HIGH){      
      // notify user
      Serial.println("Polling found pin 4 to be HIGH");
      delay(500);
      
      // setup so that the program needs to count to 15
      while (j<16){
        // checks for no interrupt
        if ((state-1) == 0){
          // starts counting
          for (j; j<16; j++){
            // again checks for interrupt
            if ((state-1) == 1){
              // notifys user that there is an interrupt
              Serial.println("Interrupt Detected stop counting");
              // waits for change in the interrupt variable
              while ((state-1) == 1){
                delay(100); 
              }
            }
            // prints out the state of the for loop
            Serial.println(j);
            delay(500);
          }
        }
      }
      // notifys user that we are checking polling again after counting to 15
      Serial.print("Check polling");
      
    // when polling pin is low
    }else{
      Serial.println("Polling LOW detected stop program");
      // don't do anything until the pin is high
      while (digitalRead(poll) == LOW){
        delay(10);
      } 
    }
    
    Serial.println(i);
    i++;
  
}

void handler(){
  // changes state
  state = (state%2)+1;
  delay(1000); 
}
