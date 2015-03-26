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
    #ifndef SECUENCIAL_H
    #define SECUENCIAL_H
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
	void leerArchivo (char* nombre_archivo, Proceso* procesos, int total_lineas);
    	int NumeroProcesosUnProcesador(Proceso* procesos, int total_lineas);// prototipo de las funciones
    	int NumeroProcesosMasDe64(Proceso* procesos, int total_lineas);
    	void ProcesoUtilizaMasCPU(Proceso* procesos, int total_lineas, float resultado[3]);
    	int ProcesosInteractivos (Proceso* procesos, int total_lineas);
    	int EjecucionCancelada (Proceso* procesos, int total_lineas);
   // #include "secuencial.c"
    #endif
