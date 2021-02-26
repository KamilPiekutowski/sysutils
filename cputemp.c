#include <stdio.h>

int main()
{

  float systemp, millideg;
  FILE *thermal;

  thermal = fopen("/sys/class/thermal/thermal_zone0/temp","r");
  n = fscanf(thermal,"%f",&millideg);
  fclose(thermal);
  systemp = millideg / 1000;

  printf("CPU temperature is %f degrees C\n",systemp);
}
