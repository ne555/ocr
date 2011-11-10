#include "neurona.h"
#include "util.h"
#include "math_vector.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

neurona::neurona(int p, value_type alpha, value_type momentum):
	weight(p+1), delta_weight(p+1), alpha(alpha), momentum(momentum){}

void neurona::init(){
	const value_type ratio=1;
	generate_n(
		&weight[0],
		weight.size(),
		randomize<value_type>(-ratio,ratio)
	);
}

neurona::neurona(std::istream &in){
	size_t size;
	in >> alpha >> momentum;
	in >> size;
	weight.resize(size); delta_weight.resize(size);
	for(size_t K=0; K<size; ++K)
		in >> weight[K];
}

void neurona::serialize(std::ostream &out) const{
	out << alpha << ' ' << momentum << '\t';
	out << weight.size() << '\t';
	for(size_t K=0; K<weight.size(); ++K)
		out << setprecision(7) << fixed << weight[K] << ' ';
	out << '\n';
}

neurona::value_type neurona::output(const vector &input) const{ 
	//return math::sign( math::dot(weight,input) );
	return math::sigmoid( math::dot(weight,input) );
}

void neurona::train(const vector &input, value_type delta){
	delta_weight = alpha*delta*input + momentum*delta_weight;
	weight += delta_weight;
}

neurona::vector neurona::error(neurona::value_type delta) const{
	return vector(delta*weight);
}

