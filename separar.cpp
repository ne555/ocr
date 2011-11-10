#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char **argv){
	const size_t cant = 10;
	ifstream data(argv[1], ios::binary), label(argv[2], ios::binary);
	ofstream out_im[cant], out_lab[cant];
	int cuenta[cant] = {0};

	for(size_t K=0; K<cant; ++K){
		stringstream ss;
		ss << argv[1] << "_separated_" << K << ".data";
		out_im[K].open(ss.str().c_str(), ios::binary);
	}
	for(size_t K=0; K<cant; ++K){
		stringstream ss;
		ss << argv[1] << "_separated_" << K << ".label";
		out_lab[K].open(ss.str().c_str(), ios::binary);
	}

	int magic, row, column, n;
	data.read( (char *) &magic, sizeof(magic) );
	data.read( (char *) &n, sizeof(n) );
	data.read( (char *) &row, sizeof(row) );
	data.read( (char *) &column, sizeof(column) );
	label.read( (char *) &magic, sizeof(magic) );
	label.read( (char *) &n, sizeof(n) );
	
	for(size_t K=0; K<cant; ++K){
		out_im[K].write( (char *) &magic, sizeof(magic) );
		out_im[K].write( (char *) &n, sizeof(n) );
		out_im[K].write( (char *) &row, sizeof(row) );
		out_im[K].write( (char *) &column, sizeof(column) );
	}
	for(size_t K=0; K<cant; ++K){
		out_lab[K].write( (char *) &magic, sizeof(magic) );
		out_lab[K].write( (char *) &n, sizeof(n) );
	}

	char *clase = new char[n];
	label.read( clase, n );
	unsigned char *image = new unsigned char[row*column];
	for(size_t K=0; K<n; ++K){
		data.read( (char *) image, row*column );
		out_im[ clase[K] ].write( (char*) image, row*column );
		out_lab[ clase[K] ].write( &clase[K], 1 );
		++cuenta[ clase[K] ];
	}

	for(size_t K=0; K<cant; ++K){
		out_im[K].seekp( sizeof(int), ios::beg );
		out_lab[K].seekp( sizeof(int), ios::beg );
		out_im[K].write( (char *) &cuenta[K], sizeof(int) );
		out_lab[K].write( (char *) &cuenta[K], sizeof(int) );
	}

	delete [] clase;
	delete [] image;

	return 0;
}


