#include "util.h"
#include "neurona.h"

using namespace std;

neurona::neurona (int cant_entradas, value_type eta) {
	weights.resize(cant_entradas + 1); // entrada aumentada
	this->eta = eta;
}

neurona::value_type neurona::calcular (const vector &entrada){
	return signo( (weights*entrada).sum() );
}

void neurona::entrenar (const vector & entradas, value_type error){
	weights += eta * error * entradas;
}

void neurona::inicializar () {
	for (int K = 0; K < weights.size(); K++)
		weights[K] = randomize(-0.5f, 0.5f);
}
