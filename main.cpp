#include "mbed.h"
#include "dnn.h"
#include "function.h"
#include "uLCD_4DGL.h"
Serial pc(USBTX, USBRX);
uLCD_4DGL uLCD(D1, D0, D2);
EventQueue entrance;
Thread t_entrance;
Thread t_dnn(osPriorityNormal, 120 * 1024 /*120K stack size*/);
InterruptIn sw2(SW2);
Thread t_taiko;
EventQueue e_taiko;
DigitalOut led (LED_BLUE);



void blink(){
  led=!led;
}
void test2(){
  uLCD.printf("test2\n");
}
int main(){
  led=true;
  t_entrance.start(callback(&entrance,&EventQueue::dispatch_forever));
  t_dnn.start(dnn);
  t_taiko.start(callback(&e_taiko,&EventQueue::dispatch_forever));
  sw2.fall(entrance.event(menu));
  while(1){
    playSong();
    if(!pause){
      blink();
    }
    wait(0.5);
  }
}