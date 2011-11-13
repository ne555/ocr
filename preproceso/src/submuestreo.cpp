#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

template<class T>
struct matrix2d{
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;

	//value_type *buffer;
	std::vector<value_type> buffer;
	const size_t row, column;
	matrix2d(size_t row, size_t column):
		row(row), column(column)
	{
		buffer.resize( row*column );
	}

	void clear(){
		std::fill(buffer.begin(), buffer.end(), 0);
	}

	pointer data(){
		return &buffer[0];
	}

	reference operator()(size_t x, size_t y){
		return buffer[ x*column + y ];
	}

	size_t size() const{
		return buffer.size();
	}
	//const_reference operator()(size_t x, size_t y, size_t z) const;

};

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

int main(int argc, char **argv){
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

