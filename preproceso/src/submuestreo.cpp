#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unistd.h>
#include <cstdlib>
#include "matrix.h"
using namespace std;

template<class T>
matrix2d<T> acumular(matrix2d<T> result){
	for(size_t K=1; K<result.column; ++K)
		result(0,K) += result(0,K-1);
	for(size_t K=1; K<result.row; ++K)
		result(K,0) += result(K-1,0);

	for(size_t K=1; K<result.row; ++K)
		for(size_t L=1; L<result.column; ++L)
			result(K,L) += result(K-1,L)+result(K,L-1)-result(K-1,L-1);
		
	return result;
}

void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "No info";
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

	matrix2d<byte> image(row, column);

	int row2 = 2, column2 = 2;

	cout.write( (char *) &magic, sizeof(magic) );
	cout.write( (char *) &n, sizeof(n) );
	cout.write( (char *) &row2, sizeof(row) );
	cout.write( (char *) &column2, sizeof(column) );

	char umbral = 30;

	for(size_t K=0; K<n; ++K){
		cin.read( (char *) image.data(), image.size()*sizeof(*image.data()) );
		matrix2d<byte> submuestreo(2,2);
		for(size_t L=0; L<row; ++L)
			for(size_t M=0; M<column; ++M)
				if( image(L,M) > umbral )
					++submuestreo(L*2/row, M*2/column);

		cout.write( (char *) submuestreo.data(), submuestreo.size()*sizeof(*submuestreo.data()) );
	}
	return 0;
}

