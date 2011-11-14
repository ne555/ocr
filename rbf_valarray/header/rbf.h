#ifndef RBF_H
#define RBF_H

#include <iostream>
#include <vector>
#include "neurona.h"
#include "neurona_rbf.h"

class RBF {
public:
	typedef neurona_rbf::value_type value_type;
	typedef neurona_rbf::vector vector;
	typedef std::vector<vector> matrix;

	RBF (int n_entradas, int neuronas_capa_gaussiana, int neuronas_capa_salida, value_type eta);
	vector calcular_intermedio (const vector & entrada);
	vector calcular_salida_con_intermedio (const vector & intermedio);
	vector calcular_salida (const vector & entrada);
	void read (std::istream &in);
	void inicializar ();
	void entrenar_capa_gaussiana ();
	int entrenar_capa_salida (int cant_epocas, value_type acierto_minimo);
	int centroide_mas_cerca (const vector &punto);
	value_type prueba ();
	void imprimir_centroides ();
	size_t clase(const vector &v);
	void classify(std::ostream &output);
	void print_intermezzo(std::ostream &output);

private:
	std::vector<neurona_rbf> capa_gaussiana;
	std::vector<neurona> capa_salida;
	matrix input, result;
	int entradas;
	int ncg, ncs; // numero de neuronas de cada capa
};

#endif
