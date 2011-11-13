/*
	Perceptron multicapa
	Clasifica.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#include "simulator.h"
#include "util.h"

using namespace std;

void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "Usage: program.bin [OPTIONS]\n";
		cerr << "Clasifica entre grupos.\n" << 
		"-a R \t Parametro de velocidad de aprendizaje\n" <<
		"-e string \t Nombre del archivo de entrenamiento\n" << 
		"-m R \t Termino de momento\n" << 
		"-n N \t Indica la cantidad maxima de epocas de entrenamiento\n" <<
		"-p string \t Nombre del archivo de prueba\n" << 
		"-r \t Leer la configuracion desde la entrada estandard\n" << 
		"-s R \t Porcentaje de exito para detener el entrenamiento [0..1]\n" << 
		"-h \t Ayuda del programa\n";
	}

	exit (status);
}

int main(int argc, char **argv){
	//Entrada n p s
	//n = cantidad de ejemplos
	//p = cantidad de percepciones
	//s = cantidad de salidas
	srand( time(NULL) );
	//srand(42);

	//test_serialization(argc==2);
	//return EXIT_SUCCESS;


	int p,s,epoch=1500;
	float success=0.90, alpha=0.7, momentum=0.3;
    const char *train_file=NULL, *test_file=NULL;
	bool serialize = false;
	int option;
	while( (option=getopt(argc, argv, "ra:e:m:n:p:s:h")) != -1 ){
		switch(option){
		case 'a': alpha=convert<float>(optarg); break;
		case 'e': train_file=optarg; break;
		case 'm': momentum=convert<float>(optarg); break;
		case 'n': epoch=convert<int>(optarg); break;
		case 'p': test_file=optarg; break;
		case 'r': serialize=true; break;
		case 's': success=convert<float>(optarg); break;
		case 'h': usage(EXIT_SUCCESS); break;
		default: usage(EXIT_FAILURE);
		}
	}

    /*if (train_file==NULL||test_file==NULL) {
        cerr << "Hay que indicar los archivos de entrenamiento y prueba" << endl;
        return EXIT_FAILURE;
    }*/
	simulator *benchmark;
	if(serialize){
		cerr << "Serializando\n";
		benchmark = new simulator(cin);
	}
	else{
		cin>>p>>s;
		benchmark = new simulator (p,s);

		// Agregar capas
		int capas;
		cin >> capas;
		for (int K = 0; K < capas; K++) {
			int neuronas;
			cin >> neuronas;
			benchmark->addlayer(neuronas,alpha,momentum);
		}
		benchmark->addlayer(s,alpha,momentum);
	}

	if(train_file){
		ifstream train(train_file);
		benchmark->read(train);
		cerr << "Entrenamiento\n";
		cerr << "Epocas " << epoch << "\t alfa " << alpha << "\t momentum " << momentum << '\n';
		int cant = benchmark->train(epoch, success, 0.2);
		if(cant == -1) cerr << "No hubo convergencia" <<endl;
		else cerr << "Convergencia en " << cant << " epocas" << endl;
		ofstream output("train.clase");
		benchmark->classify(output);
	}

	if(test_file){
		ifstream test(test_file);
		benchmark->read(test);
		float rate = benchmark->test();
		cerr << "Con los datos de prueba se obtuvo " << rate << " de acierto" <<endl;

		//mostrar clasificacion
		ofstream output("test.clase");
		benchmark->classify(output);
	}

	benchmark->serialize(cout);
	delete benchmark;
	return EXIT_SUCCESS;
}

