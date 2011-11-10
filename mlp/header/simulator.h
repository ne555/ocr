#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include "network.h"

	#include <iostream>
class simulator{
public:
	typedef network::value_type value_type;
	typedef network::vector vector;

	typedef std::vector<vector> matrix;
	typedef std::vector<network> container;

	simulator(size_t percepciones, size_t salidas);
	simulator(std::istream&);
	void read(std::istream &in);

	float test();
	int train(size_t cant, float success_rate, float error);

	//agrega al final. La ultima debe ser la network de salida (error prone)
	//solo llamarse luego de cargar los datos
	void addlayer(size_t n, value_type alpha, value_type momentum);

	void serialize(std::ostream&) const;
	void serialize(std::istream&); 
	void classify(std::ostream&);
private:
	bool done(float success, float error);
	static size_t clase(const vector &v);

	matrix input, result;
	network red;

	size_t percepciones, salidas;
};

#endif

