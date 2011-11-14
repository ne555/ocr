#include <iostream>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>
#include "matrix.h"
using namespace std;

typedef unsigned char byte;

void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "Usage: program.bin file1 file2 ... fileN\n";
		cerr << "Une las imagenes de los archivos en forma aleatoria\n" << 
		"\t La salida se envia a combinated.{data,label}\n" <<
		"-h \t Ayuda del programa\n";
	}

	exit (status);
}

int main(int argc, char **argv){
	int option;
	while( (option=getopt(argc, argv, "h")) != -1 ){
		switch(option){
		case 'h': usage(EXIT_SUCCESS); break;
		default: usage(EXIT_FAILURE);
		}
	}

	ifstream input[argc-1];
	vector< matrix2d<byte> > entrada;
	vector<char> label;
	entrada.reserve(60e3); label.reserve(60e3);

	cerr << "Argumentos " << argc << '\n';
	for(int K=0; K<argc-1; ++K)
		input[K].open(argv[K+1], ios::binary);

	int magic, row, column, n;
	for(int K=0; K<argc-1; ++K){
		cerr << "Leyendo ";
		input[K].read( (char *) &magic, sizeof(magic) );
		input[K].read( (char *) &n, sizeof(n) );
		input[K].read( (char *) &row, sizeof(row) );
		input[K].read( (char *) &column, sizeof(column) );

		//if(K==0) n /= 3;
		cerr << "n " << n << "\trow " << row << "\tcolumn " << column << '\n';
		label.insert( label.end(), n, K );

		matrix2d<byte> image(row, column);
		for(int L=0; L<n; ++L){
			input[K].read( (char *) image.data(), image.size()*sizeof(*image.data()) );
			entrada.push_back(image);
		}
	}

	ofstream data("combinated.data", ios::binary), label_out("combinated.label", ios::binary);
	vector<int> v(entrada.size());
	for(size_t K=0; K<v.size(); ++K)
		v[K] = K;
	random_shuffle( v.begin(), v.end() );

	n = v.size();

	data.write( (char *) &magic, sizeof(magic) );
	data.write( (char *) &n, sizeof(n) );
	data.write( (char *) &row, sizeof(row) );
	data.write( (char *) &column, sizeof(column) );

	label_out.write( (char *) &magic, sizeof(magic) );
	label_out.write( (char *) &n, sizeof(n) );

	cerr << "Escribir\n";

	for(size_t K=0; K<v.size(); ++K){
		data.write( (char *) entrada[ v[K] ].data(), entrada[ v[K] ].size()*sizeof(*entrada[ v[K] ].data()) );
		label_out.write( (char *) &label[ v[K] ], 1); 
	}
		
	
	//for(size_t K=0; K<v.size(); ++K)
	//	cerr << (int)label[K];
	cout << n << ", " << row*column << '\n';
	for(size_t K=0; K<v.size(); ++K){
		const vector<byte> &aux = entrada[v[K]].buffer;
		for(size_t L=0; L<aux.size(); ++L)
			cout << (int)aux[L] << ", ";
		cout << (int)label[v[K]] << '\n';	
	}
	


	return 0;
}


