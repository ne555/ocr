#include "rbf.h"
#include "util.h"

#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

RBF::RBF (int n_entradas, int neuronas_capa_gaussiana, int neuronas_capa_salida, value_type eta){
	capa_gaussiana.resize(neuronas_capa_gaussiana, neurona_rbf(n_entradas, 1) ); 
	capa_salida.resize(
			neuronas_capa_salida, 
			neurona(neuronas_capa_gaussiana, eta) // inicializacion de la neurona
	);
	ncg = neuronas_capa_gaussiana;
	ncs = neuronas_capa_salida;
	entradas = n_entradas;

	// Inicializar los pesos de las neuronas de salida
	for (int K = 0; K < neuronas_capa_salida; K++)
		capa_salida[K].inicializar();
}

RBF::vector RBF::calcular_intermedio (const vector & entrada){
	vector intermedio(ncg+1);

	for (int K = 0; K < ncg; K++)
		intermedio[K] = capa_gaussiana[K].calcular(entrada);
	
	intermedio[ncg] = 1; // entrada aumentada
	return intermedio;
}

RBF::vector RBF::calcular_salida_con_intermedio (const vector & intermedio){
	vector salida(ncs);

	for (int K = 0; K < ncs; K++)
		salida[K] = capa_salida[K].calcular(intermedio);

	return salida;
}

RBF::vector RBF::calcular_salida (const vector & entrada){
	vector inter = calcular_intermedio(entrada);
	return calcular_salida_con_intermedio(inter);
}

void RBF::read (std::istream &in) {
	cerr << "Inicio de la lectura\n";
	int patrones;
	in >> patrones;
	in.ignore( numeric_limits<streamsize>::max(), '\n' );
	input.clear(); result.clear();
	input.resize(patrones, vector(entradas));
	result.resize(patrones, vector(-1,ncs) );

	for(size_t K=0; K<patrones; ++K){
		for(size_t L=0; L<entradas; ++L)
			in >> input[K][L];

		int clase;
		in>>clase;
		result[K][clase] = 1;
	}

	cerr << "Fin de la lectura\n";
}

void RBF::inicializar () {
	int ind;

	for (int K = 0; K < ncg; K++) {
		ind = randomize(0, input.size() - 1);
		capa_gaussiana[K].set_centroid(input[ind]);
	}
}

void RBF::entrenar_capa_gaussiana () {
	int ind;
	bool cambio;

	cerr << "Entrenar capa gaussiana\n";

	while (true) {
		cerr << '.';

		matrix centroides_acumulados(ncg, vector(entradas));
		std::vector<int> cantidad_centroides(ncg, 0);

		for (int K = 0; K < input.size(); K++) {
			ind = centroide_mas_cerca(input[K]);
			centroides_acumulados[ind] += input[K];
			cantidad_centroides[ind]++;
		}

		cambio = false;
		for (int K = 0; K < ncg; K++) 
			if (cantidad_centroides[K] != 0) {
				centroides_acumulados[K] /= cantidad_centroides[K];
				// si el centroide cambia, actualizo la bandera
				if (capa_gaussiana[K].set_centroid(centroides_acumulados[K])) 
					cambio = true;
			}

		if (!cambio) break;
	}
	//TODO calcular varianza
}

int RBF::entrenar_capa_salida (int cant_epocas, value_type acierto_minimo){
	vector intermedio(ncg+1), salida_obtenida(ncs);
	int epoca, aciertos;

	cerr << "Entrenar capa salida\n";

	for (epoca = 1; epoca <= cant_epocas; epoca++) {
		aciertos = 0;

		for (int K = 0; K < input.size(); K++) { // por cada patron de entrenamiento
			intermedio = calcular_intermedio(input[K]);
			salida_obtenida = calcular_salida_con_intermedio(intermedio);

			for (int L = 0; L < ncs; L++) 
				capa_salida[L].entrenar(intermedio, result[K][L] - salida_obtenida[L]);
			
		}

		cerr << "T " << epoca << ' ';
		if ( prueba() >= acierto_minimo) break;
	}

	if (epoca <= cant_epocas) { // si convergio
		return epoca;
	}
	else {
		return -1;
	}
}

RBF::value_type RBF::prueba (){
	int aciertos = 0;
	vector salida(ncs);
	for (int i = 0; i < input.size(); i++) { // por cada patron de entrenamiento
		salida = calcular_salida(input[i]);
		if( clase(salida) == clase(result[i]) )
			aciertos++;
	}

	cerr << aciertos << ' ' << value_type(aciertos) / input.size() << '\n';
	return value_type(aciertos) / input.size();
}

size_t RBF::clase(const vector &v){
	int how_much = 0, index;
	for(size_t K=0; K<v.size(); ++K)
		if(v[K]>0){
			how_much++;
			index=K;
		}
	if(how_much == 1) return index;
	return v.size();
}

int RBF::centroide_mas_cerca (const vector &punto){
	int index_min = 0;
	value_type dist_min, dist;

	dist_min = capa_gaussiana[0].distancia2(punto);

	for (int K = 1; K < ncg; K++) {
		dist = capa_gaussiana[K].distancia2(punto);
		if (dist < dist_min) {
			dist_min = dist;
			index_min = K;
		}
	}

	return index_min;
}


void RBF::imprimir_centroides () {
	for (int K = 0; K < ncg; K++) 
		capa_gaussiana[K].imprimir_centroide();
}

void RBF::classify(std::ostream &output){
	for(size_t K=0; K<input.size(); ++K){
		vector sal = calcular_salida(input[K]);
		output << clase(sal) << '\n';
	}
}

void RBF::print_intermezzo(std::ostream &output){
	output << input.size() << ' ' << ncg << '\n';
	for(size_t K=0; K<input.size(); ++K){
		vector inter = calcular_intermedio(input[K]);
		for(size_t L=0; L<inter.size()-1; ++L)
			output << inter[L] << ' ';
		output << clase(result[K]) << '\n';
	}
}

