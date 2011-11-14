#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
using namespace std;

void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "Usage: program.bin file1 file2\n";
		cerr << "Compara los archivos linea a linea. \n" << 
		"\t Indica las diferencias y luego el total de lineas iguales\n" <<
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

	ifstream a(argv[1]), b(argv[2]);
	int ca, cb;
	int count = 0;
	while( a>>ca and b>>cb )
		if( ca == cb )
			count++;
		else
			cout << ca << " -> " << cb << '\t';
	
	cout << '\n' << count << '\n';

	return 0;
}


