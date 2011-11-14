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
		cerr << "Usage: program.bin [OPTIONS] < infile\n";
		cerr << "Muestra la imagen umbralizada\n" << 
		"-u N \t Establece el umbral. 128 por defecto" <<
		"-h \t Ayuda del programa\n";
	}

	exit (status);
}

int main(int argc, char **argv){
	int option;
	int umbral = 128;
    while( (option=getopt(argc, argv, "u:h")) != -1 )
		switch(option){
		case 'u': umbral=strtol(optarg, NULL, 10); break;
		case 'h': usage(EXIT_SUCCESS); break;
		default: usage(EXIT_FAILURE);
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

	for(size_t K=0; K<n; ++K){
		for(size_t L=0; L<row; ++L){
			for(size_t M=0; M<column; ++M)
				if(image(K,L,M) < umbral ) cout << ' ';
				else cout << '*';
			cout << endl;
		}
		cout << endl << endl;
	}

	return 0;
}


