#include "function.h"

void menuMotion(int pos){
  uLCD.locate(0,5);
  switch(pos){
    case 0:
      uLCD.printf("->forward\n");
      uLCD.printf("  backward\n");
      uLCD.printf("  change song\n");
      uLCD.printf("  Taiko mode:\n");
      break;
    case 1:
      uLCD.printf("  forward\n");
      uLCD.printf("->backward\n");
      uLCD.printf("  change song\n");
      uLCD.printf("  Taiko mode:\n");
      break;
    case 2:
      uLCD.printf("  forward\n");
      uLCD.printf("  backward\n");
      uLCD.printf("->change song\n");
      uLCD.printf("  Taiko mode:\n");
      break;
    default:
      uLCD.printf("  forward\n");
      uLCD.printf("  backward\n");
      uLCD.printf("  change song\n");
      uLCD.printf("->Taiko mode:\n");
      break;
  }
}
void songMotion(int song){
  uLCD.locate(0,5);
  switch(song){
    case 0:
      uLCD.printf("->Hopes and Dreams\n");
      uLCD.printf("  Your Best Friend\n");
      uLCD.printf("  song2\n");
      uLCD.printf("  song3\n");
      break;
    case 1:
      uLCD.printf("  Hopes and Dreams\n");
      uLCD.printf("->Your Best Friend\n");
      uLCD.printf("  song2\n");
      uLCD.printf("  song3\n");
      break;
    case 2:
      uLCD.printf("  Hopes and Dreams\n");
      uLCD.printf("  Your Best Friend\n");
      uLCD.printf("->song2\n");
      uLCD.printf("  song3\n");
      break;
    default:
      uLCD.printf("  Hopes and Dreams\n");
      uLCD.printf("  Your Best Friend\n");
      uLCD.printf("  song2\n");
      uLCD.printf("->song3\n");
      break;
  }
}
void changeSong(int &song){
  songMotion(0);
  while(1){
    switch(dnn_gesture){
      case 1:
      song=(song+4-1)%4;
      break;
      case 2:
      song=(song+1)%4;
      break;
      default:
      break;
    }
    dnn_gesture=3;
    songMotion(song);
    if(!sw3){
      break;
    }
  }
  uLCD.cls();
}
void songDisplay(){
  uLCD.printf("current playing:\n");
  uLCD.printf("%s\n",songList[song]);
  uLCD.printf("\n----------\n");
}