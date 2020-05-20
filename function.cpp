#include "function.h"
#include "DA7212.h"

char *songList[4]={"Hopes and Dreams","Your Best Friend","dog song","chord"};
float sheet[500];
int sheetCount;
DA7212 audio;
DigitalIn sw3 (SW3);
bool pause=false;
int dnn_gesture=0;
bool dnn_pause=false;
int song=0;
int score=0;
bool hit=false;
bool taiko=false;


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
  song=0;
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
  uLCD.locate(0,0);
  uLCD.cls();
  uLCD.printf("current playing:\n");
  uLCD.printf("%s\n",songList[song]);
  uLCD.printf("\n----------\n");
}
void loadSong(){
  pc.printf("\n");
  wait(.5);
  int i=0;
  char buffer[20];
  sheetCount=0;
  uLCD.locate(0,0);
  uLCD.cls();
  uLCD.printf("current loading:\n");
  uLCD.printf("%s\n",songList[song]);
  uLCD.printf("\n----------\n");
  Timer _timer;
  _timer.start();
  _timer.reset();
  pc.printf("%s\n",songList[song]);
  while(_timer.read()<30.0){
        if(pc.readable()){
            char c=pc.getc();
            if(c!='\n'){
                //uLCD.printf("%c",c);
                buffer[i]=c;
                i++;
            }else{
                i=0;
                //uLCD.printf("\n");
                //uLCD.printf("%f---%d\n",stof(buffer),sheetCount);
                sheet[sheetCount]=stof(buffer);
                sheetCount++;
            }
        }
    }    
}
void playNote(float freq,float time){
    int16_t waveform[kAudioTxBufferSize]={0};
    if(freq==0){
      audio.spk.play(waveform, kAudioTxBufferSize);
      wait(time);
      return ;
    }
    for (int i = 0; i < kAudioTxBufferSize; i++){
        waveform[i] = (int16_t) (sin((double)i * 2. * M_PI / (double) (kAudioSampleFrequency / freq))*0.2* ((1<<16) - 1));
    }

    Timer t;
    t.start();
    t.reset();
    while(t.read()<=time){
      if(taiko){
        uLCD.locate(0,5);
        uLCD.printf("socre:%d",score);
        if(hit){
          hit=false;
          if(t.read()<0.5){
            score+=5;
          }else{
            score-=1;
          }
          
        }
      }
      audio.spk.play(waveform, kAudioTxBufferSize);

    }
}
void playSong(){
  for(int i=0;i<sheetCount;i+=2){
    if(pause){
      playNote(0,.1);
      break;
    }
    playNote(sheet[i],sheet[i+1]);
  }
}
void Taiko(){
  taiko=true;
  Timer gm;
  gm.start();
  while(1){
    bool skip=false;
    if(dnn_gesture<3){
      dnn_gesture=3;
      hit=true;
      gm.reset();
      while(gm.read()<0.5){
        if(dnn_gesture<3){
          skip=true;
          break;
        }
      }
      if(!skip){
        hit=false;
      }
    }
    if(!sw2.read()){
      uLCD.printf("taiko end\n");
      break;
    }
  }
  taiko=false;
}
void menu(){
  pause=true;
  int mode=0;
  songDisplay();
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
  bool skip=false;
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
    case 3:
    //uLCD.printf("mode taiko\n");
    entrance.call(Taiko);
    //uLCD.printf("mode taiko end\n");
    skip=true;
    break;
    default:
    uLCD.printf("mode error\n");
    break;
  }
  if(!skip){
    loadSong();
  }
  songDisplay();
  pause=false;
}
void test(){
  uLCD.printf("test456");
}




