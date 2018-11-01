#include "Cromosoma.h"

using namespace std;

Cromosoma::Cromosoma(int tamano, int parametro) {
	tamArr = tamano;
	numeroParametros = parametro;
	binario = new int[tamArr]();
	real = new double[tamArr]();
}

int Cromosoma::getTam(){
	return this->tamArr;
}

//FUNCIONES DE RANDOM
int randBin() {
	static thread_local std::mt19937 binarioRand; 
	std::uniform_int_distribution<int> bin(0,1); // guaranteed unbiased
	return bin(binarioRand); 
}

int randReales(int min,int max) {
	static thread_local std::mt19937 realRand; 
	std::uniform_int_distribution<int> car(min,max); // guaranteed unbiased
	return car(realRand); 
}

double randDoubles(double min,double max) {
	static thread_local std::mt19937 doubleRand; 
	//encontrar el equivalente para doubles
	std::uniform_real_distribution<double> func(min,max); // guaranteed unbiased
	return func(doubleRand); 
}

void Cromosoma::inicializarPoblacion(int minCarros, int maxCarros, double minKM, double maxKM, double minCO2, double maxCO2){

	//Random para valores binarios
	std::mt19937 genRandomBinario(time(0));    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> bin(0,1); // guaranteed unbiased
	
	
	//Random para valores reales de Parametro:Carros
	std::mt19937 genRandomCarros(time(0));    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> car(minCarros,maxCarros); // guaranteed unbiased
//	Rand_Entero randomCarro{300000,417828};
	
	//Random para valores reales de Parametro:Km
	//Rand_double randomKm{15000,30000};
	std::mt19937 genRandomKM(time(0));    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_real_distribution<double> km(minKM,maxKM); // guaranteed unbiased
	
	//Random para valores reales de Parametro:KgCO2
	//Rand_double randomCo2{1.517,9.405};
	std::mt19937 genRandomCO2(time(0));    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_real_distribution<double> co2(minCO2,maxCO2); // guaranteed unbiased
	
	
	//Inicializando Valores de Arreglos
	
	//BINARIO
	for(int i=0;i<tamArr;i++){
		binario[i]= randBin();//bin(rng);
		//cout << binario[i];
	}
	
	//Inicializando el arreglo de reales por parametro
	int inicio = 0;
	//Aleatorio numero de carros
	for(int i=0;i<tamArr/numeroParametros;i++){
		real[inicio] = randReales(minCarros,maxCarros);
		inicio++;
	}
	//Aleatorio numero de KM
	for(int i=0;i<tamArr/numeroParametros;i++){
		real[inicio] = randDoubles(minKM,maxKM);
		inicio++;
	}
	//Aleatorio numero de KG de CO2
	for(int i=0;i<tamArr/numeroParametros;i++){
		real[inicio] =  randDoubles(minCO2,maxCO2);
		inicio++;
	}
	
}
//opcionArreglo= 
//0 Si SE QUIERE OBTIENER de ARREGLO  BINARIO
//1 Si se quiere tomar DE ARREGLO REAL
void Cromosoma::cambiarElemento(int indice, double elemento, int opcionArreglo){
	if(opcionArreglo==0){
		
		binario[indice]=elemento;
	}
	else{
		real[indice]=elemento;
	}
}

//Obtener valor de elemento. 
double Cromosoma::obtenerElemento(int indice, int opcionArreglo){
	if(opcionArreglo==0){
		return binario[indice];
	}
	else{
		return real[indice];
	}
}
//Recorrer elemento binario
void Cromosoma::recorrerBinario(){
	cout<<"Arreglo Binario Aletario"<<endl;
	for(int i=0;i<tamArr;i++){
		cout<<  binario[i];
	}
}
//Recorrer arreglo de reales
void Cromosoma::recorrerReales(){
	cout<<"Arreglo Real Aletario"<<endl;
	for(int i=0;i<tamArr;i++){
		cout<< real[i] <<endl;
	}
}
//Visualizar real binario
void Cromosoma::visualizacionCompleta(ofstream &file){
	cout<<"Arreglo Binario / Real Aletario"<<endl;
	for(int i=0;i<tamArr;i++){
		cout<< binario[i] <<" <--> " <<real[i]<<endl;
		file<< binario[i] <<" <--> " <<real[i]<<"\n";
	}
}



//getters y setters
int* Cromosoma::getBinario(){
	return binario;
}
double* Cromosoma::getReal(){
	return real;
}
int Cromosoma::getTamano(){
	return tamArr;
}
int Cromosoma::getParametros(){
	return numeroParametros;
}

//Promedios de Cromosomas
double* Cromosoma::promedioParametro(){
	int sumaCar; double sumaKm; double sumaCO2;
	sumaCar = sumaKm = sumaCO2 = 0;
	int totalCar; int totalKm; int totalCO2;
	totalCar = totalKm = totalCO2 = 0;
	int index = 0;
	parametros = new double[3];
	
	for(int i=0;i<tamArr/numeroParametros;i++){
		if(binario[index]==1){
			sumaCar = sumaCar +  real[index];
			totalCar++;
		}
		index++;
	}
	//Aleatorio numero de KM
	for(int i=0;i<tamArr/numeroParametros;i++){
		if(binario[index]==1){
			sumaKm= sumaKm + real[index];
			totalKm++;
		}
		index++;
	}
	//Aleatorio numero de KG de CO2
	for(int i=0;i<tamArr/numeroParametros;i++){
		if(binario[index]==1){
			sumaCO2= sumaCO2 + real[index];
			totalCO2++;
		}
		index++;
	}
	
	//Los parametros se dividaran en:
	/*
	CARROS = INDICE 0
	KM = INDICE 1
	CO2 = INDICE 2
	*/
	parametros[0] = sumaCar/totalCar;
	parametros[1] = sumaKm/totalKm;
	parametros[2] = sumaCO2/totalCO2;
	
	return parametros;
	
}

//Funcion fitness en donde evalua la cantidad total de contaminate por cromosoma
double Cromosoma::fitnessCromosoma(){
	this->promedioParametro();
	valorFitness = (parametros[1]*parametros[2])*parametros[0];
	return valorFitness;
}

	void Cromosoma::cambiaBinario(int index,int val){
	this->binario[index] = val;
}

double Cromosoma::getValorFitness(){
	return valorFitness;
}
int Cromosoma::getBinarioAt(int index){
	return this->binario[index];
}
