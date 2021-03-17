#ifndef SIM_H
#define SIM_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
//////////////////////////////////////////////////////////////
#include "struct.h"
#include "const.h"
#include "visual.h"
//////////////////////////////////////////////////////////////
int parseCmdLine(int argc, char* argv[], int(*pCallback) (char*, char*));
//separa parametros/opciones, devuelve la cantidad de opciones y parametros encontrados o un -1 en caso de error
int parseCallback(char* key, char* value);//analiza parametros/opciones
double getRectArea(Rect* r); // calcula el área del rectángulo.
bool isPointInRect(Point* p, Rect* r); //que determina si el punto p está dentro de o en el borde del rectángulo r.
double getDistanceBetweenPoints(Point*, Point*);//calculo la distancia entre 2 puntos
double getAngleBetweenPoitns(Point*, Point*);//calculo el angulo entre dos puntos
Point translatePoint(Point* p, double distance, double angle);//traslada un punto una distancia en cierto angulo
bool isPointEqual(Point* p1, Point* p2);//determina si dos puntos son iguales
Floor* createfloor(long, long);//crea el piso en el heap
void deletefloor(Floor*);//borra el piso del heap
Robot* createrobot(long largo, long ancho, long robotcant);//crea robots en el heap
void deleteRobot(Robot*);//borra el robot
bool movrobot(Robot* robot_p, int robotcant, long largo, long ancho, Floor*);//mueve los robots y se fija que no se salgan del piso


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* SIM_H */
