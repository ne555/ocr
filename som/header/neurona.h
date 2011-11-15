#ifndef NEURONA_H
#define NEURONA_H

#include <valarray>
#include <iostream>

/*
	Perceptron simple
	y = f( w_i x_i )
	w'_i = w_i + gamma*error*x_i

	f = sigmoid
	Salida es un real
*/

class neurona{
public:
	typedef float value_type;
	typedef std::valarray<value_type> vector;

	neurona(int p, value_type alpha); 
	//input es la entrada aumentada (la correspondiente al umbral es siempre 1)
	value_type output(const vector &input) const; 
	void train(const vector &input, value_type delta); 
	void print(std::ostream &out) const;

	void init(); //error prone

private:
	vector weight;
	value_type alpha; 
};

#endif

