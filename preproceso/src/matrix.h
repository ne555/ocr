#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template<class T>
struct matrix3d{
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;

	//value_type *buffer;
	std::vector<value_type> buffer;
	size_t row, column, depth;
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
	const_reference operator()(size_t x, size_t y, size_t z) const{
		return buffer[ x*column*depth + y*column + z ];
	}
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
	size_t row, column;
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

	const_reference operator()(size_t x, size_t y) const{
		return buffer[ x*column + y ];
	}
};

#endif

