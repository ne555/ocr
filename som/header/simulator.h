#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <valarray>
#include <cstdio>
#include <iostream>
#include "som.h"

class simulator{
public:
	typedef SOM::value_type value_type;
	typedef SOM::vector vector;
	typedef std::valarray<vector> tensor;

	typedef std::vector<vector> matrix;

	simulator(size_t percepciones, size_t salidas, size_t row, size_t column, FILE *out=NULL);
	void read(std::istream &in);

	void calculate_activation();
	void graph_activation(int clase);

	value_type test();
	void train();

private:
	matrix input, result; //, prev_error, actual_error;
	std::vector<int> label;
	std::vector<tensor> activacion;
	SOM red;

	size_t percepciones, salidas;
	size_t row, column;

	FILE *out;
};

#endif

