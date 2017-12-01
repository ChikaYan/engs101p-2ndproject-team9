
void adjustHeating(float expectedT){
    int pauseTime = 10000, lastTime = 10000; // need to be in milliseconds
    int timer = millis(); // time passed since program started

    // calculate pauseTime, lastTime and rawOutput using expectedT

    if ((timer % (pauseTime + lastTime) <= lastTime)){
        digitalWrite(OUTPIN, HIGH);
        Serial.println("on");
    }else{
        digitalWrite(OUTPIN, LOW);
        Serial.println("off");
    }
}
