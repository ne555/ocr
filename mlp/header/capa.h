#ifndef CAPA_H
#define CAPA_H

#include <valarray>
#include <vector>
#include "neurona.h"

	#include <iostream>
class capa{
public:
	typedef neurona::value_type value_type;
	typedef neurona::vector vector;

	typedef std::valarray<vector> matrix;
	typedef std::vector<neurona> container;
	
	void update(const vector &input);
	vector output(const vector &input);
	vector error(const vector &delta);

	capa(size_t n, size_t in, value_type alpha, value_type momentum);
	capa(std::istream&);
	size_t size() const;

	void serialize(std::ostream&) const;
	void serialize(std::istream&); 
private:
	size_t cant_entradas;
	container layer;
	vector delta, salida;
};

#endif

