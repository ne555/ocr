#include <iostream>
#include <vector>
#include <cmath>
#include "matrix.h"
using namespace std;


template<class T>
inline T square(T x){
	return x*x;
}

int main(int argc, char **argv){
	typedef unsigned char byte;
	int magic, row, column, n;
	
	cin.read( (char *) &magic, sizeof(magic) );
	cin.read( (char *) &n, sizeof(n) );
	cin.read( (char *) &row, sizeof(row) );
	cin.read( (char *) &column, sizeof(column) );
	cerr << magic << ' ' << n << ' ' << row << ' ' << column << ' ' <<  endl;


	matrix3d<byte> image(n,row,column);
	cin.read( (char *) image.data(), image.size()*sizeof(*image.data()) );

	matrix2d<int> sum(row, column);

	for(size_t K=0; K<n; ++K)
		for(size_t L=0; L<row; ++L)
			for(size_t M=0; M<column; ++M)
				sum(L,M) += image(K,L,M);
			

	for(size_t K=0; K<row; ++K){
		for(size_t L=0; L<column; ++L)
			cout << sum(K,L)/n << ' ';
		cout << endl;
	}
	

	return 0;
}

