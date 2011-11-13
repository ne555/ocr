#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include "matrix.h"
using namespace std;


int main(int argc, char **argv){
	typedef unsigned char byte;
	int magic, row, column, n;
	cin.read( (char *) &magic, sizeof(magic) );
	cin.read( (char *) &n, sizeof(n) );
	cin.read( (char *) &row, sizeof(row) );
	cin.read( (char *) &column, sizeof(column) );
	cerr << magic << ' ' << n << ' ' << row << ' ' << column << ' ' <<  endl;

/*
	cout.write( (char *) &magic, sizeof(magic) );
	cout.write( (char *) &n, sizeof(n) );
	cout.write( (char *) &row, sizeof(row) );
	cout.write( (char *) &column, sizeof(column) );
*/

	int option;
	int umbral = 128;
    while( (option=getopt(argc, argv, "n:u:")) != -1 )
		switch(option){
		case 'n': n=strtol(optarg, NULL, 10); break;
		case 'u': umbral=strtol(optarg, NULL, 10); break;
		}

	matrix3d<byte> image(n,row,column);
	cin.read( (char *) image.data(), image.size()*sizeof(*image.data()) );

	for(size_t K=0; K<n; ++K){
		for(size_t L=0; L<row; ++L){
			for(size_t M=0; M<column; ++M)
				cout << (int)image(K,L,M) << ' ';
				//if(image(K,L,M) < umbral ) cout << ' ';
				//else cout << '*';
			cout << endl;
		}
		cout << endl << endl;
	}

	return 0;
}


