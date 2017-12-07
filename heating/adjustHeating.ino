
void adjustHeating(){
    if (currentT < expectedT - 0.4){
        digitalWrite(OUTPIN, HIGH);
    }else{
        digitalWrite(OUTPIN, LOW);
    }

}
