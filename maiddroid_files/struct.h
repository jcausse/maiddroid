#ifndef STRUCT_H
#define STRUCT_H

typedef int(*pCallback) (char*, char*);
typedef struct {
	double x;
	double y;
} Point;
typedef struct {
	Point abajizq;
	Point arribader;
}Rect;
typedef struct {
	int largo;
	int ancho;
	bool* tiles;
}Floor;
typedef struct {
	double x;
	double y;
	double angle;
}Robot;

#endif