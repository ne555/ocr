#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "matrix.h"
using namespace std;

typedef unsigned char byte;
byte luminancia( const matrix2d<byte> &m, int r, int c, int size, int max ){
	//cerr << "Abarca " << r << " -->  " << r+size << '\n';
	byte count = 0;
	for(int K=0; K<size and K<max; ++K)
		for(int L=0; L<size and L<max; ++L)
			if(m(r+K,c+L))
				count++;
	return count;
}

void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "Usage: program.bin < infile > outfile\n";
		cerr << "Computa el numero de pixeles pintados" <<
		" en subregiones de la imagen\n" << 
		"\t Las regiones NO se solapan\n" <<
		"-s \t Cantidad de regiones a dividir\n" <<
		"-h \t Ayuda del programa\n";
	}
	exit (status);
}

int main(int argc, char **argv){
	int option, size=1;
	while( (option=getopt(argc, argv, "s:h")) != -1 ){
		switch(option){
		case 's': size=strtol(optarg, NULL, 10); break;
		case 'h': usage(EXIT_SUCCESS); break;
		default: usage(EXIT_FAILURE);
		}
	}

	int magic, row, column, n;
	cin.read( (char *) &magic, sizeof(magic) );
	cin.read( (char *) &n, sizeof(n) );
	cin.read( (char *) &row, sizeof(row) );
	cin.read( (char *) &column, sizeof(column) );
	cerr << magic << ' ' << n << ' ' << row << ' ' << column << ' ' <<  endl;

	int tamanio = row/size;
	if(row%size) tamanio++;
	
	cout.write( (char *) &magic, sizeof(magic) );
	cout.write( (char *) &n, sizeof(n) );
	cout.write( (char *) &size, sizeof(size) );
	cout.write( (char *) &size, sizeof(size) );
	
	matrix2d<byte> image(row, column);

	for(size_t K=0; K<n; ++K){
		cin.read( (char *) image.data(), image.size()*sizeof(*image.data()) );
		matrix2d<byte> submuestreo(size, size);
		for(size_t L=0; L<submuestreo.row; ++L)
			for(size_t M=0; M<submuestreo.column; ++M)
				submuestreo(L,M) = luminancia( image, L*tamanio, M*tamanio, tamanio, row );

		cout.write( (char *) submuestreo.data(), submuestreo.size()*sizeof(*submuestreo.data()) );
	}

	return 0;
}


