#pragma once
#ifndef cmatrixhead
#define cmatrixhead
#include <vector>
#include <initializer_list>

template<typename T> class Matrix
{
public:
	//constructors
	Matrix<T>();	//default constructor
	Matrix<T>(int dimension);	//create identity matrix
	Matrix<T>(int mheight,int mwidth);	//empty matrix of set dimensions
	Matrix<T>(std::initializer_list<std::vector<T>> list);	//matrix from data
	Matrix<T>(const Matrix<T>& original);	//copy existing matrix
	~Matrix<T>();
public:		//Operators
	std::vector<T> operator[](int i);
	//Matrix<T> operator= (Matrix<T> newMatrix);
	Matrix<T> operator+ (Matrix<T> otherMatrix) const;
	Matrix<T> operator+= ( Matrix<T>& otherMatrix);
	Matrix<T> operator+ (T scalar) const;
	Matrix<T> operator+= (T scalar);
	Matrix<T> operator- (Matrix<T> otherMatrix) const;
	Matrix<T> operator-= (Matrix<T> otherMatrix);
	Matrix<T> operator- (T scalar) const;
	Matrix<T> operator-= (T scalar);
	Matrix<T> operator* (Matrix<T> otherMatrix) const;
	Matrix<T> operator*= (Matrix<T> otherMatrix);
	Matrix<T> operator* (T scalar) const;
	Matrix<T> operator*= (T scalar);
	Matrix<T> operator/ (Matrix<T> otherMatrix) const;
	Matrix<T> operator/= (Matrix<T> otherMatrix);
	Matrix<T> operator/ (T scalar) const;
	Matrix<T> operator/= (T scalar);
public:		//Mathematical operations
	T det();
	static T det(const Matrix<T> m);
	Matrix<T> inv();
	static Matrix<T> inv(Matrix<T> m);
	Matrix<T> transpose();
	static Matrix<T> transpose(Matrix<T> m);
	T trace();
	static T trace(Matrix<T> m);
protected:	//Data structure
	std::vector<std::vector<T>> matrix;
	int height, width;
public:		//Data actions
	void set(int y, int x, T newValue);
	void insertCol(int col, std::vector<T> newItems);
	void insertRow(int row, std::vector<T> newItems);
	T get(int y, int x) const;
public:		//Public helper functions
	int getHeight() const;
	int getWidth() const;
	void print();
protected:	//Public helper functions
	Matrix<T> submatrix(int y, int x);
};

//Throwable exceptions
class InvalidDimensions : public std::exception {
public:	InvalidDimensions(const char* msg) : std::exception(msg) {}
};
class NotInvertable : public std::exception {
public:	NotInvertable(const char* msg) : std::exception(msg) {}
};
class DivideByZero : public std::exception {
public:	DivideByZero(const char* msg) : std::exception(msg) {}
};
class BadData : public std::exception {
public:	BadData(const char* msg) : std::exception(msg) {}
};
class OutOfBounds : public std::exception {
public:	OutOfBounds(const char* msg) : std::exception(msg) {}
};


#include "Matrix.cpp"
#endif // !cmatrixhead