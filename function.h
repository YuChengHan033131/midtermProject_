#ifndef FUNCTION_H
#define FUNCTION_H
#include "uLCD_4DGL.h"
#include"mbed.h"
extern uLCD_4DGL uLCD;
extern DigitalIn sw3;
extern int dnn_gesture;
extern int song;
extern bool pause;
extern int score;
extern bool hit;
extern bool taiko;
extern Serial pc;
extern EventQueue e_taiko;
extern EventQueue entrance;
extern InterruptIn sw2;

void menuMotion(int pos);
void songMotion(int song);
void changeSong(int &song);
void songDisplay();
void loadSong();
void playNote(float freq,float time);
void playSong();
void Taiko();
void menu();
void test();
#endif