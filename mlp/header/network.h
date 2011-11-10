#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "capa.h"
	#include <iostream>

class network{
public:
	typedef capa::value_type value_type;
	typedef capa::vector vector;

	typedef std::vector<vector> matrix;
	typedef std::vector<capa> container;

	network(size_t percepciones, size_t salidas);
	network(std::istream&);

	vector output(const vector &input);
	void train(const vector &input, const vector &expected);

	//agrega al final. La ultima debe ser la capa de salida (error prone)
	//solo llamarse luego de cargar los datos
	void addlayer(size_t n, value_type alpha, value_type momentum);

	void serialize(std::ostream&) const;
	void serialize(std::istream&); 
private:
	container red;
	matrix cache_input, cache_delta; //para obtimizar el entrenamiento
	size_t cant_entradas, cant_salidas;
};

#endif
