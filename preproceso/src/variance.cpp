#include <iostream>
#include <vector>
#include <cmath>
#include "matrix.h"
#include <unistd.h>
#include <cstdlib>

using namespace std;

template<class T>
inline T square(T x){
	return x*x;
}

void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "Usage: program.bin < infile \n";
		cerr << "Muestra la varianza celda a celda\n" << 
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

	typedef unsigned char byte;
	int magic, row, column, n;
	
	cin.read( (char *) &magic, sizeof(magic) );
	cin.read( (char *) &n, sizeof(n) );
	cin.read( (char *) &row, sizeof(row) );
	cin.read( (char *) &column, sizeof(column) );
	cerr << magic << ' ' << n << ' ' << row << ' ' << column << ' ' <<  endl;


	matrix3d<byte> image(n,row,column);
	cin.read( (char *) image.data(), image.size()*sizeof(*image.data()) );

	matrix2d<int> sum(row, column), sum_sqr(row,column);

	for(size_t K=0; K<n; ++K)
		for(size_t L=0; L<row; ++L)
			for(size_t M=0; M<column; ++M){
				sum(L,M) += image(K,L,M);
				sum_sqr(L,M) += square(image(K,L,M));
			}

	const float EPS = 1e-1;
	matrix2d<float> variance(row, column);
	for(size_t K=0; K<row; ++K){
		for(size_t L=0; L<column; ++L){
			variance(K,L) = sum_sqr(K,L) - float(square(sum(K,L)))/n;
			variance(K,L) /= n;
			cout << ((variance(K,L)<EPS)? ' ': '*');
			//cout << variance(K,L) << ' ';
		}
		cout << endl;
	}
	return 0;
}


