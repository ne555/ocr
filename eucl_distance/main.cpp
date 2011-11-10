#include <iostream>
#include <fstream>
#include <valarray>
#include <vector>
#include <limits>
//using namespace std;

using std::cerr;
using std::cout;
using std::endl;
using std::cin;

typedef float value_type;
typedef std::valarray<value_type> vector;
typedef std::vector<vector> set;
typedef std::vector<char> dictionary;

void read(set &v, dictionary &dict, std::istream &in);

value_type distancia(const vector &a, const vector &b);
value_type norm(const vector &v);
float classify(const set &ref, const dictionary &label_ref, const set &test, const dictionary &label_test);

int main(int argc, char **argv){
	const char *train_file_name=argv[1], *test_file_name=argv[2];
	std::ifstream train_file(train_file_name), test_file(test_file_name);

	set patrones, test;
	dictionary label, label_test;

	read(patrones, label, train_file);
	read(test, label_test, test_file);

	std::cerr << classify(patrones, label, test, label_test) << std::endl;

	return 0;
}
void read(set &v, dictionary &dict, std::istream &in){
	cerr << "Inicio de la lectura\n";
	int patrones, percepciones;
	in >> patrones >> percepciones;

	v.resize(patrones, vector(percepciones));
	dict.resize(patrones);

	for(size_t K=0; K<patrones; ++K){
		for(size_t L=0; L<percepciones; ++L)
			in >> v[K][L];
		in >> dict[K];
	}

	cerr << "Fin de la lectura\n";
}

value_type distancia(const vector &a, const vector &b){
	return norm(a-b);
}

value_type norm(const vector &v){
	return (v*v).sum();
}

float classify(const set &ref, const dictionary &label_ref, const set &test, const dictionary &label_test){
	int aciertos = 0;
	for(size_t K=0; K<test.size(); ++K){
		std::cerr << '.';
		value_type menor_distancia = std::numeric_limits<value_type>::max();
		size_t index_menor = 0;
		for(size_t L=0; L<ref.size(); ++L){
			value_type aux = distancia(ref[L], test[K]);
			if(aux<menor_distancia){
				menor_distancia = aux;
				index_menor = L;
			}
		}
		cout << label_test[K] << " --> " << label_ref[index_menor] << '\t';
		if(label_ref[index_menor] == label_test[K]) aciertos++;
	}

	std::cerr << "Fin de la clasificacions\n";
	std::cerr << "Aciertos " << aciertos << '\n';
	return float(aciertos)/test.size();
}


