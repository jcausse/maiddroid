#ifndef VISUAL_H
#define VISUAL_H

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "const.h"
#include "struct.h"

#define IMG_SIDE_PX_SIZE 200    //Tamaño (en pixeles) de cada lado de las imagenes (son cuadradas)
#define OFFSETY 80
#define OFFSETX 80
#define DISPLAY_SIZE 550

typedef struct{
    ALLEGRO_DISPLAY * display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_BITMAP * baldosaLimpia;
    ALLEGRO_BITMAP * baldosaSucia;
    ALLEGRO_BITMAP * robot;
    ALLEGRO_FONT * font20;
}allegroPtrs_t;

allegroPtrs_t * allegroInit(int ancho, int largo, int modo, float scaleFactor); //Allegro initialization. Returns pointer to allegroPtrs_t
bool visualOutputModo1 (allegroPtrs_t* allegro_ptrs, int ancho, int largo, int cantRobots, float scaleFactor, Floor* floor, Robot* robots);
void visualOutputModo2 (allegroPtrs_t* allegro_ptrs, int timeArrSize, float* tiempo);
void allegroDestroy (allegroPtrs_t * allegroPtrsStrPtr);
float getScaleFactor (int ancho, int largo);

#endif