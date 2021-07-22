#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

typedef enum { 
  off,
  on
} gpio17_state;

gpio17_state GPIO_STATE; // *** global variable should only be accessed by getters/setters!!!

int init();
int get_temp();
gpio17_state get_GPIO17_state();
int set_GPIO17_state(gpio17_state state);
int write_to_GPIO17_value(gpio17_state state);

int main(int argc, char* argv[]) {

  printf("usage: \n\t./%s\n", argv[0]);

  if(init() < 0) {
    fprintf(stderr,"Unable to open initialize GPIO 17\n");
 
    return -1;
  }
 
  while(1) {

    printf("Temp: %d C\n", get_temp());

    if(get_temp() >= 50 && !get_GPIO17_state()) {
      printf("Temp is HIGH\n");
      set_GPIO17_state(on);
    }    

    if(get_temp() <= 40 && get_GPIO17_state()) {
      printf("Temp is LOW\n");
      set_GPIO17_state(off);
    }    
    sleep(4);
  }


  return 0;
}

int init() {
  //setup GPIO 17 for output

  set_GPIO17_state(off);
  
  FILE *fd;

  if(!(fd = fopen("/sys/class/gpio/export","w"))) {
    return -1;
  }

  fprintf(fd,"17");
  fclose(fd);

  if(!(fd = fopen("/sys/class/gpio/gpio17/direction","w"))) {
    return -1;
  }

  fprintf(fd,"out");
  fclose(fd);

  return 0;
}

int get_temp() {
  float cputemp, millideg;
  FILE *fd;

  if(!(fd = fopen("/sys/class/thermal/thermal_zone0/temp","r"))) {
    return -1;
  }

  fscanf(fd,"%f",&millideg);
  cputemp = millideg / 1000;

  fclose(fd);
 
  return (int) cputemp;
}

gpio17_state get_GPIO17_state() {

  return GPIO_STATE;
}

int set_GPIO17_state(gpio17_state state) {

  if(write_to_GPIO17_value(state) < 0)
    return -1;

  GPIO_STATE = state;
 
  return 0;
}

int write_to_GPIO17_value(gpio17_state state) {
  FILE *fd;

   printf("Writing %d to gpio\n", (int) state);

  if(!(fd = fopen("/sys/class/gpio/gpio17/value","w"))) {
    return -1;
  }

  fprintf(fd,"%d", (int) state);
  fclose(fd);

  return 0;
}

