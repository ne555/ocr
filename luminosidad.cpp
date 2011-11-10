#include <iostream>
#include "matrix.h"
using namespace std;

typedef unsigned char byte;
byte luminancia( const matrix2d<byte> &m, int r, int c, int size ){
	cerr << "Abarca " << r << " -->  " << r+size << '\n';

	byte count = 0;
	for(int K=0; K<size; ++K)
		for(int L=0; L<size; ++L)
			if(m(r+K,c+L))
				count++;
	return count;
}

int main(int argc, char **argv){
	int magic, row, column, n;
	cin.read( (char *) &magic, sizeof(magic) );
	cin.read( (char *) &n, sizeof(n) );
	cin.read( (char *) &row, sizeof(row) );
	cin.read( (char *) &column, sizeof(column) );
	cerr << magic << ' ' << n << ' ' << row << ' ' << column << ' ' <<  endl;

	int factor = 4;
	int size = 5;
	int tamanio = 4;
	
	cout.write( (char *) &magic, sizeof(magic) );
	cout.write( (char *) &n, sizeof(n) );
	cout.write( (char *) &size, sizeof(size) );
	cout.write( (char *) &size, sizeof(size) );
	
	matrix2d<byte> image(row, column);

	int inicio = 4;
	cerr << "Factor " << factor << "\tsize " << size << "\tinicio " << inicio << '\n';
	cerr << "Tamanio " << tamanio << '\n';

	for(size_t K=0; K<n; ++K){
		cin.read( (char *) image.data(), image.size()*sizeof(*image.data()) );
		matrix2d<byte> submuestreo(size, size);
		for(size_t L=0; L<submuestreo.row; ++L)
			for(size_t M=0; M<submuestreo.column; ++M)
				submuestreo(L,M) = luminancia( image, L*inicio, M*inicio, tamanio );

		cout.write( (char *) submuestreo.data(), submuestreo.size()*sizeof(*submuestreo.data()) );
	}

	return 0;
}


