#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv){
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


