#ifndef CROMOSOMA_H
#define CROMOSOMA_H
#include <iostream>
#include <random>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;
class Cromosoma {
private:
	//Arreglo de numeros binarios que representan el uso de cada valor en el arreglo de reales
	int *binario;
	//Arreglo de valores que representan los valores de los parametros par ala funcion de fitness
	double *real;
	//Tamaño total de los arreglos
	int tamArr;
	//Numero de Parametros que tendra el arreglo
	int numeroParametros;
	//valor de fitness
	double valorFitness;
	//Arreglo donde se almacenaran los valores finales para evaluar en la funcion fitness
	double* parametros;

	
protected:
	
public:
	//Constructor con los parametros de tamaño y parametros
	Cromosoma(int tamano, int parametro);

	//Inicilizar aleatoriamente los arreglos
	void inicializarPoblacion(int, int, double, double, double, double );

	//Cambiar elemento. EN opcion arreglo se escoge 0 si se desea cambiar el arreglo binario, o 1 si se desea cambiar el arreglo real
	void cambiarElemento(int indice, double elemento, int opcionArreglo);
	//Obtener valor de elemento. EN opcion arreglo se escoge 0 si se desea obtener el arreglo binario, o 1 si se desea obtener el arreglo real
	double obtenerElemento(int indice, int opcionArreglo );
	//Recorrer elemento binario
	void recorrerBinario();
	//Recorrer arreglo de reales
	void recorrerReales();
	//Visualizar la relacion de arreglso Binario-Real
	void visualizacionCompleta( ofstream &file);
	
	void visualizacionCompleta();
	//getters y setters
	int* getBinario();
	double* getReal();	
	int getTamano();
	int getParametros();
	double getValorFitness();
	//Promedio de parametros:
	double* promedioParametro();
	//Mediana de parametros
	
	//Regresar el tamaño del arreglo
	int getTam();
	
	//funcion de aptitud

	
	double fitnessCromosoma();
	

	//Cambia valor de un índice especificado por el valor especificado en el arreglo binario.
	void cambiaBinario(int,int);
	//Obtiene el valor del array binario en un índice especificado
	int getBinarioAt(int);
	
	
};

#endif

