void adjustHeating(float expectedT){
    int pauseTime = 10000, lastTime = 10000; // need to be in milliseconds
    int timer = millis(); // time passed since program started

    // calculate pauseTime, lastTime and rawOutput using expectedT
    digitalWrite(OUTPIN, HIGH);
//    if ((timer % (pauseTime + lastTime) <= lastTime)){
//        digitalWrite(OUTPIN, HIGH);
//    }else{
//        digitalWrite(OUTPIN, LOW);
//    }
}
