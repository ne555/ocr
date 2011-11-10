#include <iostream>
#include <valarray>
#include "neurona.h"
#include "capa.h"
#include "util.h"

using namespace std;

capa::capa(size_t cant_neuronas, size_t cant_entradas, value_type alpha, value_type momentum): 
	cant_entradas(cant_entradas),
	layer(cant_neuronas, neurona(cant_entradas, alpha, momentum) ), 
	delta(cant_neuronas+1), 
	salida(cant_neuronas+1) 
{
	for(size_t K=0; K<layer.size(); ++K) 
		layer[K].init(); 

	salida[cant_neuronas] = 1; //salida extendida
}

void capa::serialize(std::ostream &out) const{
	out << cant_entradas << '\t';
	out << layer.size() << '\n';
	for(size_t K=0; K<layer.size(); ++K)
		layer[K].serialize(out);
}

capa::capa(std::istream &in){
	size_t s;
	in >> cant_entradas;
	in >> s;
	layer.reserve(s);
	delta.resize(s+1); salida.resize(s+1);
	salida[s] = 1;

	for(size_t K=0; K<s; ++K)
		layer.push_back( neurona(in) );
}

void capa::update(const capa::vector &input){
	for(size_t K=0; K<layer.size(); ++K)
		layer[K].train(input,delta[K]);
}

capa::vector capa::output(const capa::vector &input) {
	for(size_t K=0; K<salida.size()-1; ++K) //augmented output
		salida[K] = layer[K].output(input);

	return salida;
}

capa::vector capa::error(const capa::vector &d){
	delta = d*(1-salida*salida)/2;

	vector next(cant_entradas+1);
	for(size_t K=0; K<delta.size()-1; ++K)
		next += layer[K].error(delta[K]);

	return next;
}

size_t capa::size() const{
	return layer.size();
}

