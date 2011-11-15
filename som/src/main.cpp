#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include "simulator.h"
using namespace std;

void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "Usage: program.bin [OPTIONS]\n";
		cerr << "Mapa autoorganizativo\n" << 
		"-e string \t Nombre del archivo de entrenamiento\n" << 
		"-p string \t Nombre del archivo de prueba\n" << 
		"-E float \t Velocidad de aprendizaje (eta)\n" << 
		"-g \t Grafica la evolucion del sistema\n" << 
		"-h \t Ayuda del programa\n";
	}

	exit (status);
}

int main (int argc, char **argv) {
	srand(42);
	
	int entradas, row, column, salidas;
	int option;
    const char *train_file, *test_file;
    float eta = 0.05, success = 0.9;
	FILE *out=NULL;
	while( (option=getopt(argc, argv, "e:p:E:gh")) != -1 ){
		switch(option){
		case 'e': train_file=optarg; break;
		case 'p': test_file=optarg; break;
		case 'g': if(not out) out=popen("./bin/grapher", "w");break;
		case 'E': eta=strtof(optarg, NULL); break;
		case 'h': usage(EXIT_SUCCESS); break;
		default: usage(EXIT_FAILURE);
		}
	}

	cin>>entradas>>salidas>>row>>column;

	ifstream train(train_file), test(test_file);

	simulator benchmark(entradas, salidas, row, column, out);
	benchmark.read(train);
	benchmark.train();

	benchmark.calculate_activation();
	int label;
	while(cin>>label)
		benchmark.graph_activation(label);
	

	if(out) pclose(out);
	return 0;
}


