#ifndef FUNCTION_H
#define FUNCTION_H
#include "uLCD_4DGL.h"
extern uLCD_4DGL uLCD;
extern DigitalIn sw3;
extern int dnn_gesture;
extern int song;
extern char *songList[4];

void menuMotion(int pos);
void songMotion(int song);
void changeSong(int &song);
void songDisplay();

#endif