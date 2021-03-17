#include "visual.h"

allegroPtrs_t* allegroInit(int ancho, int largo){
    bool error = false;

    //DECLARACIONES DE ELEMENTOS A UTILIZAR
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
    ALLEGRO_BITMAP * baldosaLimpia = NULL;
    ALLEGRO_BITMAP * baldosaSucia = NULL;
    ALLEGRO_BITMAP * robot = NULL;

    //INICIALIZACION DE ALLEGRO
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        error = true;
    }
    if (!al_init_image_addon()) {
        fprintf(stderr, "failed to initialize image addon!\n");
        error = true;
    }
    baldosaLimpia = al_load_bitmap("./maiddroid_files/assets/baldosaLimpia.png");
    if (!baldosaLimpia){
        fprintf(stderr, "failed to load baldosaLimpia.png\n");
        error = true;
    }
    baldosaSucia = al_load_bitmap("./maiddroid_files/assets/baldosaSucia.png");
    if (!baldosaSucia){
        fprintf(stderr, "failed to load baldosaSucia.png\n");
        al_destroy_bitmap(baldosaLimpia);
        error = true;
    }
    robot = al_load_bitmap("./maiddroid_files/assets/robot.png");
    if (!baldosaSucia){
        fprintf(stderr, "failed to load robot.png\n");
        al_destroy_bitmap(baldosaLimpia);
        al_destroy_bitmap(baldosaSucia);
        error = true;
    }
    display = al_create_display(ancho * al_get_bitmap_width(baldosaLimpia), largo * al_get_bitmap_height(baldosaLimpia));
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_bitmap(baldosaLimpia);
        al_destroy_bitmap(baldosaSucia);
        al_destroy_bitmap(robot);
        error = true;
    }
    eventQueue = al_create_event_queue();
    if (!eventQueue) {
        fprintf(stderr, "failed to create event queue!\n");
        al_destroy_display(display);
        al_destroy_bitmap(baldosaLimpia);
        al_destroy_bitmap(baldosaSucia);
        al_destroy_bitmap(robot);
        error = true;
    }
    if (error == true){
        return NULL;
    }

    //CREACION Y LLENADO DE ESTRUCTURA DE PUNTEROS DE ALLEGRO
    allegroPtrs_t * allegroPtrsStrPtr = (allegroPtrs_t *) malloc (sizeof(allegroPtrs_t));
    if (allegroPtrsStrPtr == NULL){
        fprintf (stderr, "failed to create Allegro pointers structure in heap\n");
        return NULL;
    }
    allegroPtrsStrPtr->display = display;
    allegroPtrsStrPtr->eventQueue = eventQueue;
    allegroPtrsStrPtr->baldosaLimpia = baldosaLimpia;
    allegroPtrsStrPtr->baldosaSucia = baldosaSucia;
    allegroPtrsStrPtr->robot = robot;

    return allegroPtrsStrPtr;
}

void visualOutputModo1 (allegroPtrs_t* allegroPtrsStrPtr, int ancho, int largo, int cantRobots, int numTick, Floor* floor, Robot* robots){
    //DIBUJADO
    int i, j;
    for (i = 0; i < largo; i++){
        for (j = 0; j < ancho; j++){
            if(*((floor->tiles) + (i * ancho) + j) == LIMPIO){
                al_draw_bitmap(allegroPtrsStrPtr->baldosaLimpia, IMG_SIDE_PX_SIZE * j, IMG_SIDE_PX_SIZE * i, 0);
            }
            else{
                al_draw_bitmap(allegroPtrsStrPtr->baldosaSucia, IMG_SIDE_PX_SIZE * j, IMG_SIDE_PX_SIZE * i, 0);
            }
        }
    }
    al_flip_display();
    al_rest(1);
}

void visualOutputModo2 (int timeArrSize, float* tiempo){
}

void allegroDestroy (allegroPtrs_t* allegroPtrsStrPtr){
    //DESTRUIR LOS RECURSOS UTILIZADOS POR ALLEGRO
    al_destroy_display(allegroPtrsStrPtr->display);
    al_destroy_bitmap(allegroPtrsStrPtr->baldosaLimpia);
    al_destroy_bitmap(allegroPtrsStrPtr->baldosaSucia);
    al_destroy_event_queue(allegroPtrsStrPtr->eventQueue);
    free(allegroPtrsStrPtr);
}