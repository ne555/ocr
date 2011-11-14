#ifndef NEURONA_H
#define NEURONA_H

#include <valarray>

class neurona {
public:
	typedef float value_type;
	typedef std::valarray<value_type> vector;

	neurona (int cant_entradas, float eta);
	value_type calcular (const vector &entrada);
	void entrenar (const vector & entradas, value_type error);
	void inicializar ();
private:
	value_type eta;
	vector weights;	
};

#endif
