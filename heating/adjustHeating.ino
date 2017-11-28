
void adjustHeating(float expectedT){
    int pauseTime = 2000, lastTime = 500; // need to be in milliseconds
    int timer = millis(); // time passed since program started

    // calculate pauseTime, lastTime and rawOutput using expectedT

    if ((timer % (pauseTime + lastTime) <= lastTime)){
        digitalWrite(OUTPIN, HIGH);
    }else{
        digitalWrite(OUTPIN, LOW);
    }
}
