#include <iostream>
#include <vector>
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

int main(int argc, char **argv){
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



