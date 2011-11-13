#include <iostream>
using namespace std;

int main(int argc, char **argv){
	int magic, n;
	cin.read( (char *) &magic, sizeof(magic) );
	cin.read( (char *) &n, sizeof(n) );

	cerr << "Magic " << magic << "\tn " << n << '\n';

	char *buffer = new char[n];
	cin.read(buffer, n);

	for(size_t K=0; K<n; ++K)
		cout << char('0'+buffer[K]) ;

	delete [] buffer;
	return 0;
}


