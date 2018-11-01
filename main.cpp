#include<iostream>
#include "Cromosoma.h"
#include "GeneticAlgorithm.h"

int main (int argc, char *argv[]) {
	GeneticAlgorithm ProyectoCO2;
	ProyectoCO2.iniciar();
	return 0;
}

//Funciones de obtener los dos mejores cromosomas y los dos peores
//Imprimir mejor cromosoma y peor cromosoma de la iteracion
//Imprimir mejor cromosoma del proceso
//Evaluar si los hijos son mejores que los peores de l apoblacion
