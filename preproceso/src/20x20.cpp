#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include "matrix.h"
using namespace std;

void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "Usage: program.bin < infile > outfile\n";
		cerr << "Captura un cuadrado de 20x20 del centro de la imagen\n" << 
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

	matrix3d<byte> image(n,row,column), interior(n,20,20);
	cin.read( (char *) image.data(), image.size()*sizeof(*image.data()) );

	row-=8;
	column-=8;

	for(size_t K=0; K<n; ++K)
		for(size_t L=0; L<row; ++L)
			for(size_t M=0; M<column; ++M)
				interior(K,L,M) = image(K,L+4,M+4);


	cout.write( (char *) &magic, sizeof(magic) );
	cout.write( (char *) &n, sizeof(n) );
	cout.write( (char *) &row, sizeof(row) );
	cout.write( (char *) &column, sizeof(column) );
	cout.write( (char *) interior.data(), interior.size()*sizeof(*interior.data()) );

	return 0;
}



