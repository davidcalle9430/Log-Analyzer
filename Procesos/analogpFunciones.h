  /*
     Nombre Archivo:
      	secuencial.h
     Realizado por:
      	Erika Jeniffer Harker
      	David Calle
     Objetivo:
      	 Prototipo de las funciones que manipulan el log.
     Fecha Última Modificación:
      	Marzo 21 de 2015
    */

    #ifndef ANALOGPFUNCIONES_H
    #define ANALOGPFUNCIONES_H
	typedef struct{
 		//1 6 7 5 15 11
		int numero_tarea;
		//int submit_time;
		//int tiempo_espera;
		//int tiempo_ejecucion;
		int numero_procesadores;
		float tiempo_promedio_cpu;
		int memoria_usada;
		//int num_proc_solicitados;
		//int tiempo_solicitado;
		//int memoria_solicitada;
		int status;
		//int id_usuario;
		//int id_grupo;
		//int id_aplicacion;
		int numero_cola;
		//int numero_particion;
		//int tarea_anterior;
		//int tiempo_reflexion;
	} Proceso;
	void leerArchivo(char* archivo, Proceso* procesos);
	int NumeroProcesosUnProcesador( int inicio, int fin, Proceso* procesos);
	int NumeroProcesosMasDe64( int inicio, int fin, Proceso* procesos);
	int SumaDeRespuestas (float* respuestas, int cant_procesos);
	void ProcesoUtilizaMasCPU( int inicio, int fin, Proceso* procesos, float respuestas[]);
	void MayorTiempo (float* respuestas, float respuestas_finales[], int cant_procesos, int cant_respuestas);
	int ProcesosInteractivos( int inicio, int fin, Proceso* procesos);
    	int EjecucionCancelada( int inicio, int fin, Proceso* procesos);
    #include "analogpFunciones.c"
    #endif
