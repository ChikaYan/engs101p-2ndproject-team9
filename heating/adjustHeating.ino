
void adjustHeating(float currentT, float expectedT){
    float buffer = 2;
    float heatingLv = 100;

    //calculations about buffer and heatingLv

    if (currentT < expectedT - buffer){
        analogWrite(OUTPIN, heatingLv);
    }else{
        analogWrite(OUTPIN, 0);
    }
}
