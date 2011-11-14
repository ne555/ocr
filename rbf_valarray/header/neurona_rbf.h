#ifndef NEURONA_RBF_H
#define NEURONA_RBF_H

#include <valarray>

class neurona_rbf {
public:
	typedef float value_type;
	typedef std::valarray<value_type> vector;

	neurona_rbf(int size, value_type varianza);
	value_type calcular (const vector &entrada);
	bool set_centroid (const vector &new_centroid);
	value_type gaussian (value_type x);
	value_type distancia2(const vector &punto);
	void graph() const;
	void imprimir_centroide();

private:
	vector centroid;
	value_type varianza;
};

#endif
