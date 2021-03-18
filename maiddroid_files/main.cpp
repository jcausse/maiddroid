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
        return (EXIT_FAILURE);  //Se revisa que el ingreso de datos sea válido
    }
    else {//pase una cantidad correcta de datos, veo que estos sean correctos

        ancho = atoi(argv[1]);
        largo = atoi(argv[2]);//casteo a int
        robotcant = atoi(argv[3]);
        modo = atoi(argv[4]);

        printf("ancho:%d largo:%d robots:%d modo:%d \n", ancho, largo, robotcant, modo);

        if (ancho <= 0 || ancho > ANCHOMAX) {//si es un ancho no valido
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
	float scaleFactor = getScaleFactor(ancho, largo);
    allegroPtrs_t* allegroPtrsStrPtr = allegroInit(ancho, largo, modo, scaleFactor);	//INICIALIZACION DE ALLEGRO
    if (allegroPtrsStrPtr == NULL){
        return EXIT_FAILURE;
    }

    int b, tick=0;
    bool limpio = false;
    Floor* f;
    Robot* robot_p;

    if (modo == 1)
    {
        bool displayClose;
        f = createfloor(largo, ancho);

        robot_p = (Robot*)createrobot(largo, ancho, robotcant);

        while (limpio == false) {

            for (b = 0; b < robotcant; ++b) {
                limpio = movrobot(robot_p, b, largo, ancho, f);//el b es el robot que estoy moviendo
                if (limpio == true) {
                    break;
                }
            }
            ++tick;
            displayClose = visualOutputModo1 (allegroPtrsStrPtr, ancho, largo, robotcant, scaleFactor, f, robot_p);	//ALLEGRO OUTPUT
            if (displayClose) {
                deleteRobot(robot_p);
                allegroDestroy(allegroPtrsStrPtr);
                deletefloor(f);
                return EXIT_SUCCESS;
            }
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

        visualOutputModo2 (allegroPtrsStrPtr,n_robots - 1, tiempos);
        deleteRobot(robot_p);
        allegroDestroy (allegroPtrsStrPtr);
        deletefloor(f);

        return(EXIT_SUCCESS);
    }
    return (EXIT_SUCCESS);
}
///////////////////////////////////////
