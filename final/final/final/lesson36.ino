
/*  PulseSensor Starter Project and Signal Tester
 *  The Best Way to Get Started  With, or See the Raw Signal of, your PulseSensor.com™ & Arduino.
 *
 *  Here is a link to the tutorial
 *  https://pulsesensor.com/pages/code-and-guide
 *
 *  WATCH ME (Tutorial Video):
 *  https://www.youtube.com/watch?v=RbB8NSRa5X4
 *
 *
-------------------------------------------------------------
1) This shows a live human Heartbeat Pulse.
2) Live visualization in Arduino's Cool "Serial Plotter".
3) Blink an LED on each Heartbeat.
4) This is the direct Pulse Sensor's Signal.
5) A great first-step in troubleshooting your circuit and connections.
6) "Human-readable" code that is newbie friendly."

*/


//  Variables
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int led13 = 13;   //  The on-board Arduion LED

int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.


#include <PulseSensorPlayground.h>
#include "DFRobotDFPlayerMini.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
//Uncomment next 2 lines if you're using an Uno ->
//#include "SoftwareSerial.h"
SoftwareSerial mySoftwareSerial(2, 3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;


#include "TimerOne.h"
#define TrigPin 11
#define EchoPin 12

int Value_cm;
int js=0;

void setup()
{
   pinMode(led13,OUTPUT);         // pin that will blink to your heartbeat!
   Serial.begin(9600);         // Set's up Serial Communication at certain speed.
   
 //Serial Port begin
  Timer1.initialize(100);
  Timer1.attachInterrupt(blinkLED); // blinkLED to run every 0.15 seconds
  Serial.begin(9600);
  
  pinMode(led13, OUTPUT);
  digitalWrite(led13, LOW);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

// The Main Loop Function
void loop()
{
  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.
  Serial.println(Signal);                    // Send the Signal value to Serial Plotter.
  
  Value_cm=getddistance(TrigPin,EchoPin); 
  if(Value_cm>100)
    Value_cm=100;
	Serial.println(Value_cm);

 if(Signal > Threshold)
 {                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     
     digitalWrite(led13,LOW);
   } else {
     digitalWrite(led13,HIGH);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   }

 
  delay(100);
  
}


void blinkLED(void)
{
  js++;
  if(js>100)
    js=0;
  if(js< 100-Value_cm)
  {
    digitalWrite(led13, 1);
  }
  else
  {
    digitalWrite(led13, 0);
  }
}

float getddistance(int Trig,int Echo)
{
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  digitalWrite(Trig, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  //读取一个引脚的脉冲（HIGH或LOW）。例如，如果value是HIGH，pulseIn()会等待引脚变为HIGH，开始计时，再等待引脚变为LOW并停止计时。
  //返回脉冲的长度，单位微秒。如果在指定的时间内无脉冲函数返回。
  //此函数的计时功能由经验决定，长时间的脉冲计时可能会出错。计时范围从10微秒至3分钟。（1秒=1000毫秒=1000000微秒）
  //接收到的高电平的时间（us）* 340m/s / 2 = 接收到高电平的时间（us） * 17000 cm / 1000000 us = 接收到高电平的时间 * 17 / 1000  (cm)  
  return float( pulseIn(Echo, HIGH) * 17 )/1000; //将回波时间换算成cm  
  
}
