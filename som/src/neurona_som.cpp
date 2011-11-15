#include <cstdio>
#include <algorithm>
#include "neurona_som.h"
#include "util.h"
#include "math_vector.h"

using namespace std;

neurona_som::neurona_som(size_t n):
	weight(n)
{}

void neurona_som::init(){
	const value_type ratio=1;
	generate_n(
		&weight[0],
		weight.size(),
		randomize<value_type>(-ratio,ratio)
	);
}

neurona_som::value_type neurona_som::distance(const neurona_som::vector &patron) const{
    return math::norm2(patron-weight);
}

void neurona_som::train(const vector &patron, float alfa){
	weight += alfa * (patron-weight);
}

void neurona_som::graph(FILE *out){
	if(out) 
		fprintf(out, "%f %f  ", weight[0], weight[1]);
}
