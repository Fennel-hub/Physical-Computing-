#include <NewPing.h>

#define trigPin  11
#define echoPin 12
#define maxDistance 400
int LED13 = 13;
NewPing sonar( trigPin, echoPin, maxDistance);

void setup() {
  Serial.begin( 9600 );
}

void loop() {
  if(sonar.ping_cm()<=30){
    digitalWrite(LED13,HIGH);
  }
  else{digitalWrite(LED13,LOW);
  }
  Serial.println( sonar.ping_cm() );
  delay( 100 );
}



/*//led呼吸灯
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
    
}*/
