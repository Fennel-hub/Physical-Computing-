//led呼吸灯
void setup(){
    pinMode(13,OUTPUT);
    Serial.begin(9600);
    
 
}
 
void loop(){
    //渐亮
    for (int i = 0; i < 255; i++)
    {
        analogWrite(13,i);
        delay(1);
    }
    //渐暗
    for (int i = 255; i >0; i--)
    {
        analogWrite(13,i);
        delay(1);
    }
    
}
