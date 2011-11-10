#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template<class T>
struct matrix3d{
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;

	//value_type *buffer;
	std::vector<value_type> buffer;
	const size_t row, column, depth;
	matrix3d(size_t row, size_t column, size_t depth):
		row(row), column(column), depth(depth)
	{
		buffer.resize( row*column*depth );
	}

	pointer data(){
		return &buffer[0];
	}

	reference operator()(size_t x, size_t y, size_t z){
		return buffer[ x*column*depth + y*column + z ];
	}

	size_t size() const{
		return buffer.size();
	}
	//const_reference operator()(size_t x, size_t y, size_t z) const;

};

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

	matrix2d<int> sum(row, column), sum_sqr(row,column);

	for(size_t K=0; K<n; ++K)
		for(size_t L=0; L<row; ++L)
			for(size_t M=0; M<column; ++M){
				sum(L,M) += image(K,L,M);
				sum_sqr(L,M) += square(image(K,L,M));
			}

	const float EPS = 1e-1;
	matrix2d<float> variance(row, column);
	for(size_t K=0; K<row; ++K){
		for(size_t L=0; L<column; ++L){
			variance(K,L) = sum_sqr(K,L) - float(square(sum(K,L)))/n;
			variance(K,L) /= n;
			cout << ((variance(K,L)<EPS)? '0': '*') << ' ';
			//cout << variance(K,L) << ' ';
		}
		cout << endl;
	}
	
	

	return 0;
}


