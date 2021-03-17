#ifndef VISUAL_H
#define VISUAL_H

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include "const.h"
#include "struct.h"

#define IMG_SIDE_PX_SIZE 200    //Tamaño (en pixeles) de cada lado de las imagenes (son cuadradas)

typedef struct{
    ALLEGRO_DISPLAY * display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_BITMAP * baldosaLimpia;
    ALLEGRO_BITMAP * baldosaSucia;
    ALLEGRO_BITMAP * robot;
}allegroPtrs_t;

allegroPtrs_t * allegroInit(int ancho, int largo); //Allegro initialization. Returns pointer to allegroPtrs_t
void visualOutputModo1 (allegroPtrs_t* allegro_ptrs, int ancho, int largo, int cantRobots, int numTick, Floor* floor, Robot* robots);
void visualOutputModo2 (int timeArrSize, float* tiempo);
void allegroDestroy (allegroPtrs_t * allegroPtrsStrPtr);

#endif