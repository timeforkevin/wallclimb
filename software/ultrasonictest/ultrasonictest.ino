#include <MicroView.h>

#define MAX_RANGE 500
#define pinEcho A0
#define pinTrig A1

MicroViewWidget *slider;
long duration, distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(pinEcho, INPUT);
  pinMode(pinTrig, OUTPUT);
  
  uView.begin();
  uView.clear(PAGE);
  slider = new MicroViewSlider(0, 0, 0, 500);
  uView.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pinTrig, LOW); 
  delayMicroseconds(2); 

  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10); 
 
  digitalWrite(pinTrig, LOW);
  duration = pulseIn(pinEcho, HIGH, MAX_RANGE*58.2);
  distance = duration/58.2;

  slider->setValue(distance);
  Serial.print(distance);
  Serial.print('\n');
  uView.display();
}
