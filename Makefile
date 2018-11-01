GPP=mingw32-g++
CXXFLAGS= -fshow-column -fshow-column -fno-diagnostics-show-caret  -g2  -O0  -std=gnu++11 -D_DEBUG  -std=c++11
LDFLAGS= -static-libstdc++ -static-libgcc  
OBJS=Debug\main.o Debug\Cromosoma.o Debug\GeneticAlgorithm.o 

all: Debug Debug\CO2_GeneticAlgorithm.exe

clean:
	del ${OBJS} Debug\CO2_GeneticAlgorithm.exe

Debug\CO2_GeneticAlgorithm.exe: ${OBJS}
	${GPP} ${OBJS} ${LDFLAGS} -o $@

Debug:
	mkdir Debug

Debug\main.o: main.cpp
	${GPP} ${CXXFLAGS} -c main.cpp -o $@

Debug\Cromosoma.o: Cromosoma.cpp Cromosoma.h
	${GPP} ${CXXFLAGS} -c Cromosoma.cpp -o $@

Debug\GeneticAlgorithm.o: GeneticAlgorithm.cpp GeneticAlgorithm.h Cromosoma.h
	${GPP} ${CXXFLAGS} -c GeneticAlgorithm.cpp -o $@

