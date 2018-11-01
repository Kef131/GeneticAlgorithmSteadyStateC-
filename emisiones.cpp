
	#include <iostream>
	#include <cstdlib>
	
	int inicioParte(int tamArr,int partes, int partReq);
	int finParte();

	class CromosomaA{ 
		
	private:
		int binario[3000];
		int real[3000];
		int tamArr = 3000;
		int partes = 3;
		
	public:
		//constructor
		CromosomaA();
		//inicializa el arreglo binario
		void inicializarBin();
		//inicializa los valores reales en 3 partes, cada uno con un parámetro de mínimo y máximo
		void inicializarReal(int p1[2],int p2[2], int p3[2]);
	};

	void CromosomaA::inicializarBin() {
		
		for(int i=0; i < sizeof(binario); i++){
			int random = rand() % 501;
			binario[i] = ((random % 2) == 0)? 1:0;
		}
	}

	void CromosomaA::inicializarReal(int rangos[3][2]){
		
		int ini=0,fin=0;
		
		int count = 0;
		while(count < this->tamArr) {
			
			ini = inicioParte(this->tamArr,this->partes,count+1);
			fin = finParte(this->tamArr,this->partes,count+1);
			
			for( int i = ini; i < fin; i++) {
				this->real[i] = rand() % rangos[count][0] + rangos[count][1];
			}
			count++;
		}
	}

	int inicioParte(int tamArr,int partes, int partReq){
		
		int index = ((int) tamArr * ((int) partReq - 1)) / (int) partes; 
		
		return (int) index;
	}

	int finParte(int tamArr,int partes, int partReq){
		
		int index = (((int) tamArr * (int) partReq) / (int) partes) -1; 
		
		return (int) index;
	}
