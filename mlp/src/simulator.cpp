#include <iostream>
#include <sstream>
#include <cstdio>
#include <valarray>
#include <limits>
#include "simulator.h"
#include "capa.h"
#include "util.h"
#include "math_vector.h"

using namespace std;
using math::sign;
using math::sigmoid;

simulator::simulator(size_t percepciones, size_t salidas):
	percepciones(percepciones),
	salidas(salidas),
	red(percepciones, salidas)
	{}

void simulator::addlayer(size_t n, value_type alpha, value_type momentum){
	red.addlayer(n,alpha,momentum);
}

void simulator::serialize(std::ostream &out) const{
	red.serialize(out);
	out << percepciones << ' ' << salidas << '\n';	
}
	
simulator::simulator(std::istream &in): red(in){ //crash
	in >> percepciones >> salidas;
}

void simulator::read(std::istream &in){
	cerr << "Inicio de la lectura\n";
	int patrones;
	in >> patrones;
	in.ignore( numeric_limits<streamsize>::max(), '\n' );
	input.clear(); result.clear();
	label.clear();

	input.resize(patrones, vector(percepciones+1));
	result.resize(patrones, vector(-1, salidas+1) );
	label.resize(patrones);

	for(size_t K=0; K<patrones; ++K){
		for(size_t L=0; L<percepciones; ++L)
			in >> input[K][L];

		int clase;
		in>>clase;
		label[K] = clase;
		result[K][clase] = 1;
		
		input[K][percepciones] = 1; //entrada extendida
		result[K][salidas] = 1; //entrada extendida
	}

	cerr << "Fin de la lectura\n";
}

bool simulator::done(float success, float tol){
	float acierto = test();
	return acierto>success;
}

float simulator::test(){ //devolver el error en las salidas
	int acierto=0;
	for(size_t K=0; K<input.size(); ++K){
		vector sal=red.output(input[K]);
		if( clase(sal) == clase(result[K]) )
			acierto++;
	}
	cerr <<  acierto << ' ' << float(acierto)/input.size() << '\n';
	return float(acierto)/input.size();
}

int simulator::train(size_t cant, float success_rate, float error_umbral){
	cerr << "inicio del entrenamiento\n";

	for(size_t epoch=0; epoch<cant; ++epoch){
		for(size_t K=0; K<input.size(); ++K)
			red.train(input[K], result[K]);
		
		cerr << "T " << epoch << ' ' ;
		if( done(success_rate, error_umbral) )
			return epoch+1;
	}
	return -1;
}

void simulator::classify(std::ostream &output){
	for(size_t K=0; K<input.size(); ++K){
		vector sal=red.output(input[K]);
		output << clase(sal) << '\n';
	}
}

size_t simulator::clase(const vector &v){
	int how_much = 0, index;
	for(size_t K=0; K<v.size()-1; ++K)
		if(v[K]>0){
			how_much++;
			index=K;
		}
	if(how_much == 1) return index;
	return v.size()-1;
}

