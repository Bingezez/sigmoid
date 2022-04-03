#include <stdio.h>
#include <math.h>

float basic(float z){
  float b = 1;
  if (z <= -2.0){return 0;}
  if (z >= -2.0 && z <= -1.0 ){b = 4/3*pow((1 + z),1/3); return b;}
  if (z >= -1.0 && z <= 0.0 ){b = 2/3*(1 + 6 * z * z * (1 + z)); return b;}
  if (z >= 0.0 && z <= 1.0 ){b = 2/3*(1 + 6 * z * z * (1 - z)); return b;}
  if (z >= 1.0 && z <= 2.0 ){b = 4/3*pow((1 - z),1/3); return b;}
  if (z >= 2.0){return 0;}
}


void main(){
  float a;
  a = basic(0.4);
  printf("%f\n", a);
}
