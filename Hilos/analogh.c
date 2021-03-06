#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "hilos.h"
/*
  Archivo: 
    analogh.c
  Realizado por: 
    Erika Jeniffer Harker
    David Calle
  Contiene: 
    archivo para probar las las funciones definidas anteriormente.
  Fecha última modificación: 
    marzo 22 de 2015
*/

int main(int argc, char *argv[]){      
  
 	FILE * fp;
  	char *line, *lee, basura;
  	size_t len;
  	ssize_t read;
  	int i,contador, acum_hilos, contador_lineas, cantidad_hilos, aumento, cantidad_lineas,opcion, *responsabilidad_lineas, pos_hilo;
  	float *resultado;
  	double datos[18];
  	Proceso* procesos;
  	Parametro *p;
  	pthread_t *hilos;

  	if (argc != 4) {
        	printf("Cantidad de argumentos incorrectos\n");
        	exit(1);
  	}else if(atoi(argv[2])<=0||atoi(argv[3])<=0){
		printf("Tamano de archivo o  cantidad de hilos incorrecto\n");
     		exit(1);
	}else{
		cantidad_hilos= atoi(argv[3]);
    		cantidad_lineas= atoi(argv[2]);
    		fp = fopen(argv[1], "r");
  		if (fp == NULL){
      			printf("El archivo con el nombre especificado no existe\n");
      			exit(EXIT_FAILURE);
  		}else{
    			contador_lineas=0;
    			len = 0;
    			resultado= malloc(sizeof(int)*3);
    			resultado[0]=0;
    			resultado[1]=0;
    			resultado[2]=0;
    			acum_hilos=0;
    			pos_hilo=0;
    			line = NULL;
    			cantidad_hilos= atoi(argv[3]);
    			cantidad_lineas= atoi(argv[2]);
 
    			responsabilidad_lineas= malloc(sizeof(int)*cantidad_hilos);
    			for (i = 0; i < cantidad_hilos; i++){
      				responsabilidad_lineas[i]=0;
    			}
    			for(i = cantidad_lineas; i >=0; i--){
      				responsabilidad_lineas[pos_hilo]++;
      				pos_hilo++;
      				if(pos_hilo==cantidad_hilos){
        				pos_hilo=0;
      				}
    			}
    			aumento= cantidad_lineas/cantidad_hilos;
    			procesos= (Proceso*)malloc(sizeof(*procesos)*cantidad_lineas);

    			while ( (read = getline(&line, &len, fp)) != -1 ) {        
      				if( line[0]!=';'&&contador_lineas<cantidad_lineas){
        				lee=strtok(line, " \t" );
        				contador=0;
        				while(lee != NULL){ 
          					datos[contador]=atof(lee); 
          					lee=strtok(NULL, " \t");
          					contador++;
        				}
      					procesos[contador_lineas].numero_tarea = datos[0];
      					procesos[contador_lineas].numero_procesadores = datos[4];
      					procesos[contador_lineas].tiempo_promedio_cpu = datos[5];
      					procesos[contador_lineas].memoria_usada = datos[6];
      					procesos[contador_lineas].status = datos[10];
      					procesos[contador_lineas].numero_cola = datos[14];
      					contador_lineas++;
    				}      
    			} 
    		}
  		fclose(fp);
      		while (opcion!=6){
        		acum_hilos=0;
        		printf("1. Número de procesos que se ejecutó únicamente en un procesador.\n ");
        		printf("2. Numero de procesos que se ejecutó en 64 o más procesadores.\n");
        		printf("3. Qué proceso utilizó más CPU (se debe imprimir el identificador del proceso y su uso de CPU y memoria)\n");
        		printf("4. Cantidad de procesos Interactivos encontrados\n");
        		printf("5. Número de procesos cuya ejecución fue cancelada por el administrador\n");
        		printf("6. Salir del sistema \n"); 
        		scanf("%d", &opcion );
        		printf("\e[1;1H\e[2J");
        			if(opcion==1){
          				hilos =  malloc(sizeof(pthread_t)*cantidad_hilos);    
          				p= malloc((sizeof(Parametro)*cantidad_hilos));
          				for (i = 0; i < cantidad_hilos; i++){ 
            					p[i].procesos = procesos;
            					p[i].inicio= acum_hilos;
            					acum_hilos+=responsabilidad_lineas[i];
            					p[i].fin= acum_hilos;
            					p[i].respuesta=&resultado[0];
            					pthread_create(&(hilos[i]), NULL, (void*) NumeroProcesosUnProcesador, (void*) &(p[i]));
          				}
          				for (i = 0; i < cantidad_hilos; i++){ 
            					pthread_join(hilos[i],NULL);
          				}
          				printf("El numero  de procesos que se ejecutó únicamente en un procesador es: %f\n", resultado[0]);
          				free(hilos);
          				free(p);
        			}else if(opcion==2){
          				hilos =  malloc(sizeof(pthread_t)*cantidad_hilos);
          				p= malloc((sizeof(Parametro)*cantidad_hilos));
          				for (i = 0; i < cantidad_hilos; i++){ 
            					p[i].procesos = procesos;
            					p[i].inicio= acum_hilos;
            					acum_hilos+=responsabilidad_lineas[i];
            					p[i].fin= acum_hilos;
            					p[i].respuesta=resultado;
            					pthread_create(&(hilos[i]), NULL, (void*) NumeroProcesosMasDe64, (void*) &(p[i ]));
          				}
          				for (i = 0; i < cantidad_hilos; i++){ 
            					pthread_join(hilos[i],NULL);
          				}
          				printf("El numero  de procesos en más de 64 procesadores es: %f\n", resultado[0]);
          				free(hilos);
          				free(p);
        			}else if(opcion==3){
          				hilos =  malloc(sizeof(pthread_t)*cantidad_hilos);
          				p= malloc((sizeof(Parametro)*cantidad_hilos));
          				for (i = 0; i < cantidad_hilos; i++){ 
            					p[i].procesos = procesos;
            					p[i].inicio= acum_hilos;
            					acum_hilos+=responsabilidad_lineas[i];
            					p[i].fin= acum_hilos;
            					p[i].respuesta=resultado;
            					pthread_create(&(hilos[i]), NULL, (void*) NumeroProcesoUtilizaMasCPU, (void*) &(p[i ]));
          				}
          				for (i = 0; i < cantidad_hilos; i++){ 
            					pthread_join(hilos[i],NULL);
          				}
          				printf("Proceso que utilizó más CPU: %f  ;", resultado[1] );
          				printf("Tiempo de uso de CPU: %f  ;", resultado[0]);
          				printf("Memoria utilizada: %f\n", resultado[2]);
          				free(hilos);
          				free(p);
          
        			}else if(opcion==4){
         				hilos =  malloc(sizeof(pthread_t)*cantidad_hilos);
          				p= malloc((sizeof(Parametro)*cantidad_hilos));
          			for (i = 0; i < cantidad_hilos; i++){ 
            				p[i].procesos = procesos;
            				p[i].inicio= acum_hilos;
            				acum_hilos+=responsabilidad_lineas[i];
            				p[i].fin= acum_hilos;
            				p[i].respuesta=resultado;
            				pthread_create(&(hilos[i]), NULL, (void*) ProcesosInteractivos, (void*) &(p[i ]));
          			}
          			// joineo los hilos
          			for (i = 0; i < cantidad_hilos; i++){ 
            				pthread_join(hilos[i],NULL);
          			}
          			printf("El numero  de procesos nteractivos es de: %f\n", resultado[0]);
          			free(hilos);
          			free(p);
        		}else if(opcion==5){
           			hilos =  malloc(sizeof(pthread_t)*cantidad_hilos);
          			p=malloc((sizeof(Parametro)*cantidad_hilos));
          			for (i = 0; i < cantidad_hilos; i++){ 
            				p[i].procesos = procesos;
            				p[i].inicio= acum_hilos;
            				acum_hilos+=responsabilidad_lineas[i];
            				p[i].fin= acum_hilos;
            				p[i].respuesta=resultado;
            				pthread_create(&(hilos[i]), NULL, (void*) EjecucionCancelada, (void*) &(p[i ]));
          			}
          			// joineo los hilos
          			for (i = 0; i < cantidad_hilos; i++){ 
            				pthread_join(hilos[i],NULL);
          			}
          			printf("El numero  de procesos con ejecución`cancelada es de: %f\n", resultado[0]);
          			free(hilos);
				free(p);
			}
        
        		if(opcion!=6){
          			//reiniciar respuesta
          			for (i = 0; i < 3; i++){
            				resultado[i]=0;
          			}
          			printf("Oprima cualquier tecla para continuar \n" );
          			scanf("%c",&basura);
          			scanf("%c",&basura);
          			printf("\e[1;1H\e[2J"); 
        		}
  
        	}
        	free(procesos);
        	free(resultado);
        	free(responsabilidad_lineas);
    	} 
 }
