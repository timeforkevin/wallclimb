
#ifdef MICROVIEW
#include <MicroView.h>
MicroViewWidget *slider;
#endif

#define MAX_RANGE 500
#define pinEcho1 8
#define pinTrig1 9
#define pinEcho2 10
#define pinTrig2 11
#define pinEcho3 12
#define pinTrig3 13

long duration, distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(pinEcho1, INPUT);
  pinMode(pinTrig1, OUTPUT);
  pinMode(pinEcho2, INPUT);
  pinMode(pinTrig2, OUTPUT);
  pinMode(pinEcho3, INPUT);
  pinMode(pinTrig3, OUTPUT);

#ifdef MICROVIEW
  uView.begin();
  uView.clear(PAGE);
  slider = new MicroViewSlider(0, 0, 0, 500);
  uView.display();
#endif
}

void loop() {
  // Ultrasonic 1
  digitalWrite(pinTrig1, LOW); 
  delayMicroseconds(2); 

  digitalWrite(pinTrig1, HIGH);
  delayMicroseconds(10); 
 
  digitalWrite(pinTrig1, LOW);
  duration = pulseIn(pinEcho1, HIGH, MAX_RANGE*58.2);
  distance = duration/58.2;

  Serial.print("right: ");
  Serial.print(distance);

  // Ultrasonic 2
  digitalWrite(pinTrig2, LOW); 
  delayMicroseconds(2); 

  digitalWrite(pinTrig2, HIGH);
  delayMicroseconds(10); 
 
  digitalWrite(pinTrig2, LOW);
  duration = pulseIn(pinEcho2, HIGH, MAX_RANGE*58.2);
  distance = duration/58.2;

  Serial.print("  front: ");
  Serial.print(distance);

  // Ultrasonic 3
  digitalWrite(pinTrig3, LOW); 
  delayMicroseconds(2); 

  digitalWrite(pinTrig3, HIGH);
  delayMicroseconds(10); 
 
  digitalWrite(pinTrig3, LOW);
  duration = pulseIn(pinEcho3, HIGH, MAX_RANGE*58.2);
  distance = duration/58.2;

  Serial.print("  left: ");
  Serial.print(distance);
  Serial.print('\n');
#ifdef MICROVIEW
  slider->setValue(distance);
  uView.display();
#endif
}
