#include "GeneticAlgorithm.h"



using namespace std;

GeneticAlgorithm::GeneticAlgorithm() {
	bestWorst[0] = 0;
	bestWorst[1] = 1;
	bestWorst[2] = 2;
	bestWorst[3] = 3;
}

GeneticAlgorithm::~GeneticAlgorithm() {
	
}

void GeneticAlgorithm::iniciar(){
	myfile.open ("cromosomas.txt");
	//Crear Poblacion Inicial
	vector<Cromosoma> poblacion;

	//PROCESO DE INICIALIZACION DE POBLACION
	double fitnessLocal;
	for(int i=0; i<TAMANO_POBLACION;i++){
		//Inicializar poblacion de individuos aleatorios
		poblacion.push_back( Cromosoma(LONGITUD, 3) );
		b  vvvxxxpoblacion.at(i).inicializarPoblacion(LIMITEMINAUTOS, LIMITEMAXAUTOS, LIMITEMINKM, LIMITEMAXKM, LIMITEMINCO2, LIMITEMAXCO2);
		//Evaluar los fitness de cada Cromosoma
		poblacion.at(i).fitnessCromosoma();
	}
	
	//EVALUAR MEJOR Y PEORES DE LA poblacion
	
	//Ordenar el arreglo de MejoresPeores
	this->ordernarBestWorst( &poblacion);
	
	//Evaluar el mejor Elemento de la poblacion
	this->evaluarMejorPeorPoblacion(&poblacion);
	

	
	//Mientras no se acabae las iteracciones
	int count = 0;
	while(count < ITERACIONES){
		myfile<< "Iteracion: " << count+1<< " \n";
		//creacion de receptores de descendientes
		vector<Cromosoma> hijos;
		
		//Seleccionar los dos mejores cromosomas
		Cromosoma best1 = poblacion.at(bestWorst[0]);
		Cromosoma best2 = poblacion.at(bestWorst[1]);
		
		//Cruzar estos dos mejores cromosomas
		hijos = cruzaUniforme(best1, best2);
		
//		cout <<"Padres"<<endl;
//		cout <<fixed<< best1.getValorFitness()/1000000 << endl;
//		cout <<fixed<< best2.getValorFitness() /1000000<< endl;
//		
//	
//		cout <<"Hijos"<<endl;
//		cout <<fixed<< hijos.at(0).getValorFitness() /1000000<< endl;
//		cout <<fixed<< hijos.at(1).getValorFitness() /1000000<< endl;
//		
		//Mutar cada hijo
		
//		cout <<"Hijos normales" << endl;
//		
//		cout <<fixed <<   hijos.at(0).getValorFitness()/1000000<<endl;
//		cout <<fixed <<   hijos.at(1).getValorFitness()/1000000;
//		
//		cout << endl;
		
		mutacion(&hijos.at(0));
		mutacion(&hijos.at(1));
		
		//Se inicializan los nuevos valores de fitness
		hijos.at(0).fitnessCromosoma();
		hijos.at(1).fitnessCromosoma();
		
//		cout <<"Hijos mutados" << endl;
//		cout <<fixed <<   hijos.at(0).getValorFitness()/1000000<<endl;
//		cout <<fixed <<   hijos.at(1).getValorFitness()/1000000;
//		
//		cout << endl;
//		
//		cout << "=============================";
//		cout << endl << endl;
//	
		//cout <<"Mutaciones"<<endl;
		//cout <<fixed<< mut1.getValorFitness() /1000000<< endl;
		//cout <<fixed<< mut2.getValorFitness() /1000000<< endl;
		
		
		
		//Obtener los dos peores resultados de la poblacion y compararlo con el resultado de los hijos
		Cromosoma worst1 = poblacion.at(bestWorst[3]);
		Cromosoma worst2 = poblacion.at(bestWorst[2]);
		
		//cout <<"Peores"<<endl;
		//cout <<fixed<< worst1.getValorFitness()/1000000 << endl;
		//cout <<fixed<< worst2.getValorFitness() /1000000<< endl;
		
		//Si los hijos son peores que los peores (MAYOR VALOR)se eliminan
		if( hijos.at(1).getValorFitness() > worst1.getValorFitness() ){
			hijos.erase(hijos.begin() +1);
		}
		else if( hijos.at(1).getValorFitness() > worst2.getValorFitness() ){
			hijos.erase(hijos.begin()+1);
		}
		if( hijos.at(0).getValorFitness() > worst1.getValorFitness() ){
			hijos.erase(hijos.begin());
		}
		else if( hijos.at(0).getValorFitness() > worst2.getValorFitness() ){
			hijos.erase(hijos.begin());
		}
		
		//Si sobrevivieorn lso dos hijos, se eliminan los peores y se insertan los hijos
		int pocision;
		if(hijos.size()==2){
			poblacion.at(bestWorst[2]) = hijos.at(0);
			poblacion.at(bestWorst[3]) = hijos.at(1);
		}

		else if(hijos.size()==1){
			//El mejor individuo es el menos peor (no el peor peor)
			poblacion.at(bestWorst[2]) = hijos.at(0);
		}
		
		this->ordernarBestWorst(&poblacion);
		
		this->evaluarMejorPeorPoblacion(&poblacion);
		
		
		//cout <<"========================="<<endl;
		
		count++;
		myfile<<fixed<< "Mejor Cromosoma:  "  << " FITNESS-> "<< poblacion.at(bestWorst[0]).getValorFitness()/1000000 << " toneladas CO2\n";
		myfile<<fixed<< "Peor Cromosoma: "  << " FITNESS-> "<< poblacion.at(bestWorst[3]).getValorFitness()/1000000 << " toneladas CO2\n";
	}
//	cout<<"El mejor de la corrida"<<endl;
	myfile<<fixed<< "El mejor de la corrida: " << " FITNESS-> "<< poblacion.at(bestWorst[0]).getValorFitness()/1000000 << " toneladas CO2\n";
	poblacion.at(bestWorst[0]).visualizacionCompleta(myfile);
	myfile.close();
}

		

	//Imprimir el  mejor y el peor cromosomas de la iteracion
	
	//Imprimir el  mejor cromosomas de la iteracion
	
	// Pocision Mejor Peor
void GeneticAlgorithm::actualizarPocisionMejorPeor(int pocisionEliminada, int opcionPeor){
	if(opcionPeor==3){
		if(pocisionEliminada < bestWorst[0])
			bestWorst[0]--;
	   if(pocisionEliminada < bestWorst[1])
			bestWorst[1]--;
		if(pocisionEliminada < bestWorst[2])
			bestWorst[2]--;
		
	}
	else if(opcionPeor==2){
		if(pocisionEliminada < bestWorst[0])
			bestWorst[0]--;
		if(pocisionEliminada < bestWorst[1])
			bestWorst[1]--;
	    if(pocisionEliminada < bestWorst[3])
			bestWorst[3]--;	
		
	}
}
	
//FUNCIONES DE RANDOM
int GeneticAlgorithm::randBin() {
	static thread_local std::mt19937 binarioRand; 
	std::uniform_int_distribution<int> bin(0,1); // guaranteed unbiased
	return bin(binarioRand); 
}

int GeneticAlgorithm::randMascara() {
	static thread_local std::mt19937 binarioMasc; 
	std::uniform_int_distribution<int> binM(0,LONGITUD-1); // guaranteed unbiased
	return binM(binarioMasc); 
}

vector<Cromosoma> GeneticAlgorithm::cruzaUniforme(Cromosoma padre, Cromosoma madre){
	//Crear Mascara de CRUZA
	int* mascaraCruza = crearMascara();
	
	//Creacion de dos hijos vacios
	vector<Cromosoma> hijos;
	hijos.push_back( Cromosoma(LONGITUD,3));
	hijos.push_back( Cromosoma(LONGITUD,3));
	
	
	//Seteo de hijos
	for(int i=0; i<LONGITUD; i++){
		if(mascaraCruza[i] == 1){
			hijos.at(0).cambiarElemento(i,padre.obtenerElemento(i,0) ,0);
			hijos.at(0).cambiarElemento(i,padre.obtenerElemento(i,1) ,1);
			hijos.at(1).cambiarElemento(i,madre.obtenerElemento(i,0) ,0);
			hijos.at(1).cambiarElemento(i,madre.obtenerElemento(i,1) ,1);
		}
		else{
			hijos.at(0).cambiarElemento(i,madre.obtenerElemento(i,0) ,0);
			hijos.at(0).cambiarElemento(i,madre.obtenerElemento(i,1) ,1);
			hijos.at(1).cambiarElemento(i,padre.obtenerElemento(i,0) ,0);
			hijos.at(1).cambiarElemento(i,padre.obtenerElemento(i,1) ,1);
		}
	}
	
	hijos.at(0).fitnessCromosoma();
	hijos.at(1).fitnessCromosoma();
	
	return hijos;

}
	

int* GeneticAlgorithm::crearMascara(){
	//Se crea la mascara deacuerdo a la longitud del arreglo
	int* mascaraCruza = new int[LONGITUD]();
	//Se obtienve el numero de bits activos
	int bitActivos = round(LONGITUD*CRUZA);

	//Mientras no se haya acompletado la cantida de bits activos
	// obtener aleatoriamente un indice del arreglo y convertirlo a 1
	//asi hasta obtener el numero de bits activos
	while(bitActivos > 0){
		int ind = randMascara();
		if( mascaraCruza[ind] == 0){
			mascaraCruza[ind] = 1;
			bitActivos--;
		}
	}
	return mascaraCruza;
}

bool yaCambiado(vector<int> &indexes,int index);
int randMutIndx(int min,int max);

void GeneticAlgorithm::mutacion(Cromosoma *especimen) {
	
	/*
		*Mutar binarios
	*/

	int tamArr = especimen->getTam();
	int index = randMutIndx(0,tamArr);

	
	vector<int> indexes;
	for(int i =0 ; i < (int) round(MUTACION * LONGITUD); i++){	
		int index  = randMutIndx(0,tamArr);
		
//		if(i != 0){
//			while(yaCambiado(indexes,index)){
//				index  = randMutIndx(0,tamArr);
//			}
//		}
	
		indexes.push_back(index);
		int val    = abs(especimen->getBinarioAt(index) - 1);
		especimen->cambiaBinario(index,val);
		
	}	
}


//Evaluar si el indice obtenido ya se ha cambiado
bool yaCambiado(vector<int> &indexes,int index) {
	for (std::vector<int>::iterator it = indexes.begin() ; it != indexes.end(); ++it){
		if(index == *it)
			return true;
	}
	return false;
}

//Aleatorios para mutación
int randMutIndx(int min,int max) {
	
	static thread_local std::mt19937 realRand; 
	std::uniform_int_distribution<int> indx(min,max); // guaranteed unbiased
	return indx(realRand); 
}


//Ordernar Mejores y Peores
void GeneticAlgorithm::ordernarBestWorst( vector<Cromosoma> *poblacion  ){
	
	//ordernar bestWosrt de menor a mayor
	int aux = 0;
	for(int i=1;i< 4;i++){
		for(int j=0;j< (4-i);j++){
			if(poblacion->at(bestWorst[j]).getValorFitness() > poblacion->at(bestWorst[j+1]).getValorFitness()){
				aux  		   = bestWorst[j];
				bestWorst[j]   = bestWorst[j+1];
				bestWorst[j+1] = aux;
			}
		}	
	}

}

//Evaluar si la poblacion tiene 
void GeneticAlgorithm::evaluarMejorPeorPoblacion( vector<Cromosoma> *poblacion){
	for(int i=4; i< TAMANO_POBLACION; i++){
		
		double inFitness = poblacion->at(i).getValorFitness();
		
		//Si es mejor que el primero de los bestWorst, se vuelve el mejor, el mejor se vuelve el segundo mejor
		if(inFitness < poblacion->at(bestWorst[0]).getValorFitness())
		{ 
			bestWorst[1] = bestWorst[0]; 
			bestWorst[0] = i;
		}
		
		else if(inFitness  < poblacion->at(bestWorst[1]).getValorFitness() && inFitness > poblacion->at(bestWorst[0]).getValorFitness() )
				bestWorst[1] = i;
				
		else if(inFitness > poblacion->at(bestWorst[3]).getValorFitness())
		{
			bestWorst[2] = bestWorst[3];
			bestWorst[3] = i;
		}
		
		else if(inFitness > poblacion->at(bestWorst[2]).getValorFitness() && inFitness < poblacion->at(bestWorst[3]).getValorFitness() )
				bestWorst[2] = i;
		
//		
//		cout <<fixed<< poblacion->at(bestWorst[0]).getValorFitness()/1000 <<endl;
//		cout <<fixed<< poblacion->at(bestWorst[1]).getValorFitness()/1000 <<endl;
//		cout <<fixed<< poblacion->at(bestWorst[2]).getValorFitness()/1000 <<endl;
//		cout <<fixed<< poblacion->at(bestWorst[3]).getValorFitness()/1000 <<endl;
//		
//		cout << endl;
	}
}

