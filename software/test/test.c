
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]) {
  int colour = strtol(argv[1], NULL, 16);

  int r = (colour >> 16) & 0xFF;
  int g = (colour >> 8) & 0xFF;
  int b = colour & 0xFF;
  //analogWrite(R_PIN, 0xFF - r);
  printf("Red: ");
  printf(0xFF - r);
  printf("\n");
  //analogWrite(G_PIN, 0xFF - g);
  printf("Green: ");
  printf(0xFF - g);
  printf("\n");
  //analogWrite(B_PIN, 0xFF - b);
  printf("Blue: ");
  printf(0xFF - b);
  printf("\n");
  printf("\n");
}
