#include <iostream>
#include <algorithm>
#include "neurona.h"
#include "util.h"
#include "math_vector.h"
using namespace std;

neurona::neurona(int p, value_type alpha):
	weight(p+1), alpha(alpha){}

void neurona::init(){
	const value_type ratio=1;
	generate_n(
		&weight[0],
		weight.size(),
		randomize<value_type>(-ratio,ratio)
	);
}

neurona::value_type neurona::output(const vector &input) const{ 
	return math::sign( math::dot(weight,input) );
}

void neurona::train(const vector &input, value_type delta){
	weight += alpha*delta*input;
}

void neurona::print(ostream &out) const{
	for(size_t K=0; K<weight.size(); ++K)
		out << weight[K] << ' ';
	
	out << endl;
}

