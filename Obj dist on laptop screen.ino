***PROCESSING CODE***

import processing.serial.*;  
Serial myPort;  
String data="" ;
PFont  myFont;  
void setup()
{
size(1366,900); // size of processing window
background(0);// setting background color to black
myPort = new Serial(this, "COM3", 9600);
myPort.bufferUntil('\n');
}
void draw()
{
  background(0);
  textAlign(CENTER);
  fill(255);
  text(data,820,400);
  textSize(100);
  fill(#4B5DCE);
  text("              Distance :        cm",450,400);
   noFill();
   stroke(#4B5DCE);
}
void serialEvent(Serial myPort)
{
 
  data=myPort.readStringUntil('\n');
} 


***ARDUINO CODE****


#include <Mouse.h>


const int trigpin= 8;

const int echopin= 7;

long duration;

int distance;

void setup()

{

  pinMode(trigpin,OUTPUT);

  pinMode(echopin,INPUT);

  Serial.begin(9600);

 

}

void loop()

{

  digitalWrite(trigpin,HIGH);

  delayMicroseconds(10);

  digitalWrite(trigpin,LOW);

  duration=pulseIn(echopin,HIGH);

  distance = duration*0.034/2;

  Serial.println(distance);

}
