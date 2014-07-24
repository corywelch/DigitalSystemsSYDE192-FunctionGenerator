    const int switchPin = 2; // the number of the input pin
    long startTime; // store in starting time here
    long duration; // variable to store how long the timer has been running
    float secduration; // variable to store the duration in seconds
    boolean currentPress;
    boolean isPress;

    void setup()
    {
        Serial.begin(9600);
        currentPress = true;
        isPress = false;
    }

    void loop()
    {
    if(digitalRead(switchPin) == HIGH && currentPress){
        currentPress = false;
        isPress = true;
        startTime = millis();
        Serial.println(" ");
        Serial.println("Timer Started!!");
    }
    if(digitalRead(switchPin) == LOW && isPress){
        Serial.println(".............");
        Serial.println("Timer Stopped");
        duration = millis() - startTime;
        secduration = duration/1000.0;
        Serial.println("Duration(millisec): ");
        Serial.println(duration);
        Serial.println("Duration(sec): ");
        Serial.println(secduration);
        currentPress = true;
        isPress = false;
        Serial.println(".............");
        Serial.println(" ");
    }
}


