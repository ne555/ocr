#include <iostream>
#include <algorithm>
#include <limits>
#include <sstream>
#include <cstdio>
#include <valarray>
#include "simulator.h"
#include "util.h"
#include "math_vector.h"

using namespace std;
using math::sign;
using math::sigmoid;

simulator::simulator(size_t percepciones, size_t salidas, size_t row, size_t column, FILE *out):
	percepciones(percepciones),
	salidas(salidas),
	red(percepciones, row, column),
	activacion(salidas, tensor(vector(column), row)),
	row(row), column(column),
	out(out)
{
	if(out)
		fprintf(out, "%lu %lu\n", row, column);
}

void simulator::read(istream &in){
	cerr << "Inicio de la lectura\n";
	size_t patrones;
	in >> patrones;
	in.ignore( numeric_limits<streamsize>::max(), '\n' );
	input.clear(); result.clear();

	input.resize(patrones, vector(percepciones+1));
	result.resize(patrones, vector(-1, salidas+1) );
	label.resize(patrones);

	for(size_t K=0; K<patrones; ++K){
		for(size_t L=0; L<percepciones; ++L)
			in >> input[K][L];

		int clase;
		in>>clase;
		result[K][clase] = 1;
		label[K] = clase;
		
		input[K][percepciones] = 1; //entrada extendida
		result[K][salidas] = 1; //entrada extendida
	}

}


void simulator::train(){
	red.train(input);
}

static simulator::value_type max_number(const simulator::tensor &t){
	simulator::value_type maximo = -numeric_limits<simulator::value_type>::max();
	for(size_t K=0; K<t.size(); ++K)
		maximo = std::max(maximo, t[K].max());
	return maximo;
}

void simulator::calculate_activation(){
//recorrer el input
//sumar la activacion de cada neurona segun la clase a que corresponda
//dividir todas las matrices por el maximo numero (discutible)
//la activacion queda entonces en [0, 1]
	for(size_t K=0; K<input.size(); ++K)
		activacion[label[K]] += red.activacion(input[K]);
		
	for(size_t M=0; M<activacion.size(); ++M)
		for(size_t K=0; K<activacion[M].size(); ++K)
			for(size_t L=0; L<activacion[M][K].size(); ++L)
				if(activacion[M][K][L] > 0)
					activacion[M][K][L] = 0;
				else
					activacion[M][K][L] = 1;

	/*for(size_t K=0; K<activacion.size(); ++K){
		value_type factor = max_number(activacion[K]);
		for(size_t L=0; L<row; ++L)
			activacion[K][L] /= factor;
	}*/

}

void simulator::graph_activation(int clase){
	if(not out) return;
	fprintf(out, "%lu %lu\n", row, column);
	for(size_t K=0; K<row; ++K){
		for(size_t L=0; L<column; ++L)
			fprintf(out, "%f ", activacion[clase][K][L]);
		fprintf(out, "\n");
	}
	fflush(out);
}

