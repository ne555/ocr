#include <iostream>
#include <cmath>
#include <cstdlib>
#include "util.h"

using namespace std;
static const float EPS = 1E-5;

int randomize (int lower, int upper) {
	return rand() % (upper-lower+1) + lower;
}

float randomize (float lower, float upper) {
	return float(rand())/RAND_MAX * (upper-lower) + lower;
}


bool comparar_vectores (const std::valarray<float> & a, const std::valarray<float> & b){
	// Devuelve true si son "iguales"
	return (abs(a-b)).max() < EPS;
}

vector<float> sumar_vectores (vector<float> & a, vector<float> & b) {
	vector<float> c(a.size());
	if (a.size() != b.size()) {
		cerr << "sumar_vectores: distinto size" << endl;
		throw 1;
	}

	for (int i = 0; i < a.size(); i++) {
		c[i] = a[i] + b[i];
	}
	return c;
}

vector<float> restar_vectores (vector<float> & a, vector<float> & b) {
	vector<float> c(a.size());
	if (a.size() != b.size()) {
		cerr << "restar_vectores: distinto size " << a.size() << ' ' << b.size() << endl;
		throw 1;
	}

	for (int i = 0; i < a.size(); i++) {
		c[i] = a[i] - b[i];
	}
	return c;
}

float multiplicar_vectores (vector<float> & a, vector<float> & b) {
	float accum = 0;
	vector<float> c(a.size());
	if (a.size() != b.size()) {
		cerr << "multiplicar_vectores: distinto size" << endl;
		throw 1;
	}

	for (int i = 0; i < a.size(); i++) {
		accum += a[i] * b[i];
	}

	return accum;
}

vector<float> dividir_vector (vector<float> & a, float divisor) {
	vector<float> b(a.size());
	for (int i = 0; i < a.size(); i++) {
		b[i] = a[i] / divisor;
	}
	return b;
}

float norma2 (const std::valarray<float> &v){
	float accum = (v*v).sum();
	return sqrt(accum);
}

int signo (float a) {
	if (a > 0) return 1;
	else	   return -1;
}

void imprimir_vector (vector<float> & a) {
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
