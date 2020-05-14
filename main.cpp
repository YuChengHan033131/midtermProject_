#include "mbed.h"
#include "dnn.h"
#include "function.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);
Serial pc(USBTX, USBRX);
EventQueue entrance;
Thread t_entrance;
EventQueue e_dnn;
Thread t_dnn(osPriorityNormal, 120 * 1024 /*120K stack size*/);
InterruptIn sw2(SW2);
DigitalIn sw3 (SW3);
DigitalOut led (LED_BLUE);

bool pause=false;
int dnn_gesture=0;
bool dnn_pause=false;
int song=0;
char *songList[4]={"Hopes and Dreams","Your Best Friend","song2","song3"};
void menu(){
  pause=true;
  int mode=0;
  songDisplay();
  menuMotion(0);
  while(1){
    switch(dnn_gesture){
      case 1:
      mode=(mode+4-1)%4;
      break;
      case 2:
      mode=(mode+1)%4;
      break;
      default:
      break;
    }
    dnn_gesture=3;
    menuMotion(mode);
    if(!sw3){
      break;
    }
  }
  uLCD.cls();
  switch(mode){
    case 0:
    song=(song+1)%4;
    break;
    case 1:
    song=(song-1+4)%4;
    break;
    case 2:
    changeSong(song);
    break;
    default:
    //Taikp
    break;
  }
  songDisplay();
  
  pause=false;
}

void blink(){
  led=!led;
}

int main(){
  led=true;
  t_entrance.start(callback(&entrance,&EventQueue::dispatch_forever));
  t_dnn.start(dnn);
  sw2.fall(entrance.event(menu));
  //pc.printf("start\n");
  //pc.printf("---%d---\n",dnn());
  //dnn();
  while(1){
    if(!pause){
      blink();
      //playSong
    }
    wait(0.5);
    
  }
}