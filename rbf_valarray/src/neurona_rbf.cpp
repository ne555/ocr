#include <cmath>
#include <iostream>
#include <cstdio>
#include "util.h"
#include "neurona_rbf.h"

using namespace std;

neurona_rbf::neurona_rbf(int size, value_type varianza): centroid(size), varianza(varianza) {}

neurona_rbf::value_type neurona_rbf::calcular(const vector &entrada) {
	value_type dist = norma2(entrada-centroid);
	return gaussian(dist/16);
}

bool neurona_rbf::set_centroid (const vector & new_centroid) {
	// Devuelve falso si el nuevo centroide no es distinto al actual
	
	if (comparar_vectores(centroid, new_centroid)) 
		return false; // no cambia
	
	centroid = new_centroid;
	return true;
}

neurona_rbf::value_type neurona_rbf::gaussian (value_type x) {
	return exp(-((x*x)/(2*varianza)));
}
	
neurona_rbf::value_type neurona_rbf::distancia2(const vector & punto) {
	return norma2(centroid-punto);
}

void neurona_rbf::graph() const{
	cout << centroid[0] << ' ' << centroid[1] << endl;
}

void neurona_rbf::imprimir_centroide() {
	for (int K = 0; K < centroid.size(); K++) 
		cout << centroid[K] << " ";
	cout << endl;
}

