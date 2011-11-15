#ifndef NEURONA_SOM_H
#define NEURONA_SOM_H

#include <cstdio>
#include <valarray>

class neurona_som {
public:
	typedef float value_type;
	typedef std::valarray<value_type> vector;
    //void set_weights (vector<float> & weights);
	void init(); 
	neurona_som(size_t n);

    value_type distance(const vector &patron) const;
	void train(const vector &patron, float alfa);

	void graph(FILE *out);
private:
    vector weight;
};

#endif
