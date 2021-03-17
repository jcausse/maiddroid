/////////////////////////////////////////////////////////////////
#include"sim.h"
///////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
	int cant, ancho, largo, robotcant, modo;
	srand(time(NULL));
	pCallback p = parseCallback;
	printf("El primer dato es el ancho, el segundo el largo, el tercero la cantidad de robots, y el cuarto el modo, mandar solo parametros \n");
	printf("El modo es 1 para simulacion , y 2 para grafico.\n");
	if (((cant = parseCmdLine(argc, argv, p)) > 4) || ((cant = parseCmdLine(argc, argv, p)) < 3)) {//si pase una cantidad incorrecta de datos
		printf("Parametros incorrectos o insuficientes. \n");
		return (EXIT_FAILURE);
	}
	else {//pase una cantidad correcta de datos, veo que estos sean correctos
		ancho = atoi(argv[1]);
		largo = atoi(argv[2]);//casteo a int
		robotcant = atoi(argv[3]);
		modo = atoi(argv[4]);
		printf("ancho:%d largo:%d robots:%d modo:%d \n", ancho, largo, robotcant, modo);
		if (ancho <= 0 || ancho > ANCHOMAX) {//si es un acho no valido
			printf("Ancho no valido\n");
			return (EXIT_FAILURE);
		}
		if (largo <= 0 || largo > LARGOMAX) {//si es un largo no valido
			printf("Largo no valido\n");
			return (EXIT_FAILURE);
		}
		if (robotcant <= 0) {//cant de robot no valido
			printf("Cantidad de robots no valida\n");
			return (EXIT_FAILURE);
		}
		if (modo < 1 || modo>2) {//si es un modo no valido
			printf("Modo no valido\n");
			return (EXIT_FAILURE);
		}
	}
	allegroPtrs_t* allegroPtrsStrPtr = allegroInit(ancho, largo);	//INICIALIZACION DE ALLEGRO
	int b, tick;
	bool limpio = false;
	Floor* f;
	Robot* robot_p;
	tick = 0;

	if (modo == 1)
	{

		f = createfloor(largo, ancho);

		robot_p = (Robot*)createrobot(largo, ancho, robotcant);

		while (limpio == false) {
			/*for (int i = 0; i < largo; ++i) {
				for (int j = 0; j < ancho; ++j) {
					printf("%d", *((f->tiles) + j + i * ancho));
				}
				printf("\n");
			}
			printf("\n");*/
			for (b = 0; b < robotcant; ++b) {
				//printf("Robot %i; x:%lf y:%lf angulo en radianes:%lf  x:%d  y:%d\n", b, ((robot_p + b)->x), ((robot_p + b)->y), ((robot_p + b)->angle), (int)((robot_p + b)->x), (int)((robot_p + b)->y));
				limpio = movrobot(robot_p, b, largo, ancho, f);//el b es el robot que estoy moviendo			
				if (limpio == true) {
					break;
				}
			}
			++tick;
			visualOutputModo1 (allegroPtrsStrPtr, ancho, largo, robotcant, tick, f, robot_p);	//ALLEGRO OUTPUT
			//printf("ciclo:%d\n", tick);
		}

		for (int i = 0; i < largo; ++i) {
			for (int j = 0; j < ancho; ++j) {
				printf("%d", *((f->tiles) + j + i * ancho));
			}
			printf("\n");
		}

		deleteRobot(robot_p);
		allegroDestroy (allegroPtrsStrPtr);
		deletefloor(f);

		return(EXIT_SUCCESS);
	}

	else if (modo == 2)
	{
		int n_sim = 1, suma=0, a =0, j=0, n_robots = 0;
		bool seguir = 1;
		float tiempos[MAXROBOTS];

		f = createfloor(largo, ancho);
		robot_p = (Robot*)createrobot(largo, ancho, MAXROBOTS);

		for (n_robots = 1;seguir; n_robots++)
		{
			for (n_sim = 1; n_sim <= NUM_SIMUL_MODO_2; n_sim++)
			{
				while (limpio == false) {
					for (b = 0; b < n_robots; ++b) {
						limpio = movrobot(robot_p, b, largo, ancho, f);//el b es el robot que estoy moviendo			
						if (limpio == true) {
							break;
						}
					}
					tick++;
				}
				limpio = false;
				suma = suma + tick;
				tick = 0;
				for (a = 0; a < n_robots; a++)
				{
					(robot_p + a)->x = (rand() % ancho + 0);
					(robot_p + a)->y = (rand() % largo + 0);
					(robot_p + a)->angle = (rand() % 360 + 0);//ahora lo paso a radianes pq math.h usa radianes
					(robot_p + a)->angle = (robot_p->angle * 2 * PI / 360);
				}

				for (a = 0; a < largo; a++) {
					for (j = 0; j < ancho; ++j) {
						*((f->tiles) + j + a * ancho) = SUCIO;
					}
				}
			}
			tiempos[n_robots-1] = (float)((float)suma / NUM_SIMUL_MODO_2);
			suma = 0;
			printf("%f \n", tiempos[n_robots-1]);

			if (n_robots >= 2)
			{
				if ((float)((float)tiempos[n_robots - 2] - (float)tiempos[n_robots - 1]) >= (float)0.1)
					seguir = 1;
				else 
					seguir = 0;
			}
		}
		visualOutputModo2 (n_robots - 1, tiempos);
		printf ("Presione cualquier tecla para terminar el programa\n");
		getchar();

		deleteRobot(robot_p);
		allegroDestroy (allegroPtrsStrPtr);
		deletefloor(f);

		return(EXIT_SUCCESS);
	}
}
///////////////////////////////////////
