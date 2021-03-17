#include "visual.h"

allegroPtrs_t* allegroInit(int ancho, int largo, int modo, float scaleFactor){
    //DECLARACIONES DE ELEMENTOS A UTILIZAR
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
    ALLEGRO_BITMAP * baldosaLimpia = NULL;
    ALLEGRO_BITMAP * baldosaSucia = NULL;
    ALLEGRO_BITMAP * robot = NULL;
    ALLEGRO_FONT * font20 = NULL;

    //INICIALIZACION DE ALLEGRO
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return NULL;
    }
    if (!al_init_image_addon()) {
        fprintf(stderr, "failed to initialize image addon!\n");
        return NULL;
    }
    if(!al_init_primitives_addon()) {
        fprintf(stderr, "failed to initialize allegro graphics!\n");
        return NULL;
    }

    if(!al_init_font_addon()) {
        fprintf(stderr, "failed to initialize allegro fonts!\n");
        return NULL;
    }
    if(!al_init_ttf_addon()) {
        fprintf(stderr, "failed to initialize allegro ttf fonts!\n");
        return NULL;
    }
    font20 = al_load_font("./maiddroid_files/assets/OpenSans-Semibold.ttf",20,0);
    if (!font20) {
        fprintf(stderr, "failed to create font!\n");
        return NULL;
    }
    baldosaLimpia = al_load_bitmap("./maiddroid_files/assets/baldosaLimpia.png");
    if (!baldosaLimpia){
        fprintf(stderr, "failed to load baldosaLimpia.png\n");
        al_destroy_font(font20);
        return NULL;
    }
    baldosaSucia = al_load_bitmap("./maiddroid_files/assets/baldosaSucia.png");
    if (!baldosaSucia){
        fprintf(stderr, "failed to load baldosaSucia.png\n");
        al_destroy_font(font20);
        al_destroy_bitmap(baldosaLimpia);
        return NULL;
    }
    robot = al_load_bitmap("./maiddroid_files/assets/robot.png");
    if (!robot){
        fprintf(stderr, "failed to load robot.png\n");
        al_destroy_font(font20);
        al_destroy_bitmap(baldosaLimpia);
        al_destroy_bitmap(baldosaSucia);
        return NULL;
    }
    eventQueue = al_create_event_queue();
    if (!eventQueue) {
        fprintf(stderr, "failed to create event queue!\n");
        al_destroy_font(font20);
        al_destroy_bitmap(baldosaLimpia);
        al_destroy_bitmap(baldosaSucia);
        al_destroy_bitmap(robot);
        return NULL;
    }
    if(modo==1) {
        display = al_create_display(ancho * al_get_bitmap_width(baldosaLimpia) * scaleFactor, largo * al_get_bitmap_height(baldosaLimpia) * scaleFactor);
        if (!display) {
            fprintf(stderr, "failed to create display!\n");
            al_destroy_font(font20);
            al_destroy_event_queue(eventQueue);
            al_destroy_bitmap(baldosaLimpia);
            al_destroy_bitmap(baldosaSucia);
            al_destroy_bitmap(robot);
            return NULL;
        }
    }
    else if(modo == 2) {
        display = al_create_display(DISPLAY_SIZE + OFFSETX, DISPLAY_SIZE + OFFSETY);
        if (!display) {
            fprintf(stderr, "failed to create display!\n");
            al_destroy_font(font20);
            al_destroy_event_queue(eventQueue);
            al_destroy_bitmap(baldosaLimpia);
            al_destroy_bitmap(baldosaSucia);
            al_destroy_bitmap(robot);
            return NULL;
        }
    }
    al_register_event_source(eventQueue, al_get_display_event_source(display)); //Inicializacion cola de eventos
    //CREACION Y LLENADO DE ESTRUCTURA DE PUNTEROS DE ALLEGRO
    allegroPtrs_t * allegroPtrsStrPtr = (allegroPtrs_t *) malloc (sizeof(allegroPtrs_t));
    if (allegroPtrsStrPtr == NULL){
        fprintf (stderr, "failed to create Allegro pointers structure in heap\n");
        al_destroy_font(font20);
        al_destroy_event_queue(eventQueue);
        al_destroy_bitmap(baldosaLimpia);
        al_destroy_bitmap(baldosaSucia);
        al_destroy_bitmap(robot);
        al_destroy_display(display);
        return NULL;
    }
    allegroPtrsStrPtr->display = display;
    allegroPtrsStrPtr->eventQueue = eventQueue;
    allegroPtrsStrPtr->baldosaLimpia = baldosaLimpia;
    allegroPtrsStrPtr->baldosaSucia = baldosaSucia;
    allegroPtrsStrPtr->robot = robot;
    allegroPtrsStrPtr->font20 = font20;

    return allegroPtrsStrPtr;
}

bool visualOutputModo1 (allegroPtrs_t* allegroPtrsStrPtr, int ancho, int largo, int cantRobots, float scaleFactor, Floor* floor, Robot* robots){
    //DIBUJADO
    int i, j;
    for (i = 0; i < largo; i++){
        for (j = 0; j < ancho; j++){
            if(*((floor->tiles) + (i * ancho) + j) == LIMPIO){
                al_draw_scaled_rotated_bitmap(allegroPtrsStrPtr->baldosaLimpia, 0, 0,
                IMG_SIDE_PX_SIZE * j * scaleFactor, IMG_SIDE_PX_SIZE * i * scaleFactor, scaleFactor, scaleFactor, 0, 0);
            }
            else{
                al_draw_scaled_rotated_bitmap(allegroPtrsStrPtr->baldosaSucia, 0, 0,
                    IMG_SIDE_PX_SIZE * j * scaleFactor, IMG_SIDE_PX_SIZE * i * scaleFactor, scaleFactor, scaleFactor, 0, 0);
            }
        }
    }
    for (i = 0; i < cantRobots; i++) {
        al_draw_scaled_rotated_bitmap(allegroPtrsStrPtr->robot, al_get_bitmap_width(allegroPtrsStrPtr->robot) / 2,
            al_get_bitmap_height(allegroPtrsStrPtr->robot) / 2,
            ((robots + i)->x) * IMG_SIDE_PX_SIZE * scaleFactor, ((robots + i)->y) * IMG_SIDE_PX_SIZE * scaleFactor, 
            scaleFactor, scaleFactor, ((robots + i)->angle) + (PI/2), 0);
    }
    al_flip_display();
    al_rest(0.75);
    ALLEGRO_EVENT ev;   //Registrar eventos de Allegro
    if (al_get_next_event(allegroPtrsStrPtr->eventQueue, &ev)){     //Obtenemos proximo evento
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)                 //Si es de cerrar display
            return true;
    }
    return false;     //Si no se obtuvo un evento o no se obtuvo uno de cerrar display
}

void visualOutputModo2 (allegroPtrs_t* allegroPtrsStrPtr, int timeArrSize, float* tiempo){
    int i=1;
    char maxrobots[10];
    char maxticks[10]="\0";

    ALLEGRO_COLOR rojo = al_map_rgb(255,0,0);
    ALLEGRO_COLOR blanco = al_map_rgb(255,255,255);
    ALLEGRO_COLOR negro = al_map_rgb(0,0,0);

    al_clear_to_color(al_map_rgb(200, 255, 200));

    al_draw_line(OFFSETX/2,DISPLAY_SIZE,DISPLAY_SIZE+OFFSETX/2,DISPLAY_SIZE,negro,1);
    al_draw_line(OFFSETX/2,DISPLAY_SIZE,OFFSETX/2,OFFSETY,negro,1);

    al_draw_text(allegroPtrsStrPtr->font20,negro,(DISPLAY_SIZE+OFFSETX)/2,OFFSETY*0.5/2,ALLEGRO_ALIGN_CENTRE,"Gráfico de Ticks en función de número de robots");
    al_draw_text(allegroPtrsStrPtr->font20,negro,OFFSETX/2,DISPLAY_SIZE+OFFSETX/2*0.2,ALLEGRO_ALIGN_CENTRE,"1");
    al_draw_text(allegroPtrsStrPtr->font20,negro,OFFSETX/4,DISPLAY_SIZE-0.2 * OFFSETY,ALLEGRO_ALIGN_CENTRE,"0");
    al_draw_text(allegroPtrsStrPtr->font20,negro,OFFSETX/2,OFFSETY*0.6,ALLEGRO_ALIGN_CENTRE,"ticks");
    al_draw_text(allegroPtrsStrPtr->font20,negro,DISPLAY_SIZE+OFFSETX/2,DISPLAY_SIZE+OFFSETX/2*0.8,ALLEGRO_ALIGN_CENTRE,"robots");

    sprintf_s(maxrobots,"%i\0",timeArrSize);
    al_draw_text(allegroPtrsStrPtr->font20,negro,DISPLAY_SIZE+OFFSETX/2,DISPLAY_SIZE+OFFSETX/2*0.2,ALLEGRO_ALIGN_CENTRE,maxrobots);

    if(timeArrSize>=11) {
        for(i=1;i<=4;i++) {
            sprintf_s(maxrobots, "%i\0", (int) timeArrSize * i / 5);

            al_draw_text(allegroPtrsStrPtr->font20, negro,
                         (DISPLAY_SIZE + OFFSETX / 2) - ((DISPLAY_SIZE + OFFSETX / 2) - OFFSETX / 2) / 5 * (5-i),
                         DISPLAY_SIZE + OFFSETX / 2 * 0.2, ALLEGRO_ALIGN_CENTRE, maxrobots);
        }
    }
    sprintf_s(maxticks,"%i\0",(int)tiempo[0]);
    al_draw_text(allegroPtrsStrPtr->font20,negro,OFFSETX/4,OFFSETY,ALLEGRO_ALIGN_CENTRE,maxticks);

    for(i=1;i<timeArrSize;i++)
    {
        al_draw_line((i-1)*DISPLAY_SIZE/(timeArrSize-1)+OFFSETX/2,DISPLAY_SIZE-(tiempo[i-1]*(DISPLAY_SIZE-OFFSETY)/tiempo[0]),i*DISPLAY_SIZE/(timeArrSize-1)+OFFSETX/2,DISPLAY_SIZE-(tiempo[i]*(DISPLAY_SIZE-OFFSETY)/tiempo[0]),rojo,1);
    }
    al_flip_display();
    bool closeDisplay = false;
    ALLEGRO_EVENT ev;   //Registrar eventos de Allegro
    while (!closeDisplay) {
        if (al_get_next_event(allegroPtrsStrPtr->eventQueue, &ev)) {     //Obtenemos proximo evento
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)                 //Si es de cerrar display
                closeDisplay = true;
        }
    }
}

void allegroDestroy (allegroPtrs_t* allegroPtrsStrPtr){
    //DESTRUIR LOS RECURSOS UTILIZADOS POR ALLEGRO
    al_destroy_display(allegroPtrsStrPtr->display);
    al_destroy_font(allegroPtrsStrPtr->font20);
    al_destroy_bitmap(allegroPtrsStrPtr->baldosaLimpia);
    al_destroy_bitmap(allegroPtrsStrPtr->baldosaSucia);
    al_destroy_bitmap(allegroPtrsStrPtr->robot);
    al_destroy_event_queue(allegroPtrsStrPtr->eventQueue);
    free(allegroPtrsStrPtr);
}

float getScaleFactor(int ancho, int largo) {
    float a, b;
    if ((ancho <= 9) && (largo <= 5))       //Maximo ancho y alto para mostrar a tama�o completo
        return 1;                           //1 = tama�o completo
    else {
        a = 9.0 / ancho;                    //Escalado en ancho
        b = 5.0 / largo;                    //Escalado en alto
        return ((a <= b) ? a : b);          //Devuelve la menor de ambas escalas
    }
}