#ifndef LED_H
#define LED_H

#define R_PIN A0
#define G_PIN A1
#define B_PIN A2

void initLED() {
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

// Colour as Hex Triplet 0xABCDEF
// Red: AB
// Green: CD
// Blue: EF
void writeLEDColour(unsigned long int colour) {
  unsigned long int r = (colour >> 16) & 0xFF;
  unsigned long int g = (colour >> 8) & 0xFF;
  unsigned long int b = colour & 0xFF;
  analogWrite(R_PIN, (0xFF - r));
  analogWrite(G_PIN, (0xFF - g));
  analogWrite(B_PIN, (0xFF - b));
}

#endif