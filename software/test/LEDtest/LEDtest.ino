#define R_PIN A0
#define G_PIN A1
#define B_PIN A2

void setup() {
  // put your setup code here, to run once:
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(300);
  analogWrite(R_PIN, rand() % 255);
  analogWrite(G_PIN, rand() % 255);
  analogWrite(B_PIN, rand() % 255);
  
}
