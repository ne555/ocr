#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv){
	typedef unsigned char byte;
	int magic, row, column, n;

	ifstream buffer_file( argv[1], ios::binary ), label_file( argv[2], ios::binary );

	buffer_file.read( (char *) &magic, sizeof(magic) );
	buffer_file.read( (char *) &n, sizeof(n) );
	buffer_file.read( (char *) &row, sizeof(row) );
	buffer_file.read( (char *) &column, sizeof(column) );
	
	label_file.read( (char *) &magic, sizeof(magic) );
	label_file.read( (char *) &n, sizeof(n) );
	cerr << magic << ' ' << n << ' ' << row << ' ' << column << ' ' <<  endl;


	size_t size = row*column;
	byte *buffer = new byte [size];
	byte *label = new byte [n];

	label_file.read( (char*) label, n );

	cout << n << ' ' << size << '\n';

	for(size_t K=0; K<n; ++K){
		buffer_file.read( (char*) buffer, size );
		for(size_t L=0; L<size; ++L)
			cout << (int)buffer[L] << ' ';
		cout << (int) label[K] << '\n';
	}

	delete [] buffer;
	delete [] label;

	return 0;
}


