#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include "Cromosoma.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include <random>


using namespace std;

class GeneticAlgorithm {
private:
	//Tamaño de la poblacion

	int  TAMANO_POBLACION=300;

	//Tamaño del cromosoma, divido en tres segementos: 100 por cada parametro
	int LONGITUD=1500;
	
	//Tasa de Mutacion
	double MUTACION=0.8;
	
	//Mascara de Cruza en porcentaje basado en Uniform Crossover
	double CRUZA=0.5;
	
	//Valor de Carros Limite
	int LIMITEMINAUTOS = 300000;
	int LIMITEMAXAUTOS = 417828;
	
	//Valor de KM limite
	double LIMITEMINKM=15000;
	double LIMITEMAXKM=30000;
	
	//Valor de CO2 limite
	double LIMITEMINCO2=0.107;
	double LIMITEMAXCO2=0.737;
	
	//Numero de repeticiones
	int ITERACIONES=1500;

	//Mejores de la poblacion. Se guarda la pocision
	int bestWorst[4];
	
	
	ofstream myfile;
	
	
	

	
protected:
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();
			
	//Proceso del algortimo genetico steady state
	void iniciar();
	//Funcion de cruza entre dos cromosomas
	vector<Cromosoma> cruzaUniforme(Cromosoma , Cromosoma );
	//Mascara de bits necesaria para la cruza
	int* crearMascara();
	//Mutacion de cromosoma
	void mutacion(Cromosoma *especimen);
	//Funciones random
	int randBin();
	int randMascara();
	
	//Ordernar Mejores y Peores
	void ordernarBestWorst(  vector<Cromosoma> *poblacion );
	//Evaluacion de mejores y peores
	void evaluarMejorPeorPoblacion(vector<Cromosoma> *poblacion );
	
	void actualizarPocisionMejorPeor(int pocisionEliminada, int opcionPeor);
		

};

#endif


