#include <iostream>
#include <valarray>
#include <map>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "util.h"
#include "math_vector.h"
using namespace std;
using namespace math;

void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "Usage: program.bin [OPTIONS]\n";
		cerr << "Genera la entrada de datos para el SOM\n" << 
		"-n N \t Cantidad de patrones a generar\n" << 
		"-f string \t Nombre de la funcion clasificadora\n" <<
		"-l \t Lista las funciones disponibles\n" << 
		"-h \t Imprime esta ayuda\n";
	}
	exit (status);
}

typedef std::valarray<float> vectorf;
typedef bool (*filter)(const vectorf &v);

void init();

bool rectangle(const vectorf &v); 
bool rectangle_fade(const vectorf &v);
bool circle(const vectorf &v); 
bool ring(const vectorf &v); 
bool not_circle(const vectorf &v){
	return not circle(v);
} 
bool not_ring(const vectorf &v){
	return not ring(1.5f*v);
}
bool t_shape(const vectorf &v); 
bool cuadraditos(const vectorf &v); 
bool circle_fade(const vectorf &v);

template<class T>
void listar(const T &m);

map<string, filter> mapa;

int main(int argc, char **argv){
	init();
	int option;
	size_t n=0;
	const size_t p=2;
	float ratio=0;
	filter funcion;

	while( (option=getopt(argc, argv, "n:f:lh")) != -1 ){
		switch(option){
		case 'n': n=strtol(optarg,NULL,10);break;
		case 'f': funcion = mapa[string(optarg)];break;
		case 'l': listar(mapa); return EXIT_SUCCESS;
		case 'h': usage(EXIT_SUCCESS); break;
		default: usage(EXIT_FAILURE);
		}
	}

	cout << n << endl;
	for(size_t K=0; K<n;){
		vectorf percepcion(p), desvio(p);

		for(size_t L=0; L<p; ++L)
			percepcion[L] = randomize<float>(-1.f,1.f)();

		if(funcion(percepcion)){
			for(size_t J=0; J<percepcion.size(); ++J)
				cout << 4*percepcion[J] << ' ';
			cout << endl;
			K++;
		}
	}

	return 0;
}

void init(){
	mapa["circle"] = &circle;
	mapa["circle_fade"] = &circle_fade;
	mapa["not_circle"] = &not_circle;
	mapa["ring"] = &ring;
	mapa["not_ring"] = &not_ring;
	mapa["rectangle"] = &rectangle;
	mapa["rectangle_fade"] = &rectangle_fade;
	mapa["t_shape"] = &t_shape;
	mapa["cuadraditos"] = &cuadraditos;
}

template<class T>
void listar(const T &m){
	for(typename T::const_iterator it = m.begin(); it != m.end(); ++it)
		cout << it->first << '\n';
}

bool rectangle(const vectorf &v){
	return abs(v).max() <= 1;
}

bool circle(const vectorf &v){
	return (v*v).sum() <= 1;
} 
bool ring(const vectorf &v){
	return between( 0.25f, (v*v).sum(), 1.f);
}

bool t_shape(const vectorf &v){
	return
		between(-0.25f, v[0], 0.25f)
		or between(0.5f, v[1], 1.f);
}

bool cuadraditos(const vectorf &v){
	const float radio = 0.1f;
	return 
		between(1-radio, abs(v[0]), 1+radio)
		and between(1-radio, abs(v[1]), 1+radio)
		or 
		between(1-radio, v[0], 1+radio)
		and abs(v[1]) <= radio/2;

		//abs(v).max() <= radio/2;
}

bool circle_fade(const vectorf &v){
	return randomize<float>(0,1)() > norm2(v);
}

bool rectangle_fade(const vectorf &v){
	return randomize<float>(0,1)() > (v[0]+1)/2;
}

