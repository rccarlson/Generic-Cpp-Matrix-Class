#include "pch.h"
#ifndef cmatriximplement
#define cmatriximplement
#include "Matrix.h"
#include <vector>
#include <initializer_list>

//--------------------CONSTRUCTORS--------------------

//Default constructor
template <typename T> Matrix<T>::Matrix() {
	height = 0; width = 0;
	matrix.resize(height);
	for (int i = 0; i < height; i++)
		matrix[i].resize(width);
}
//Construct identity matrix
template<typename T> Matrix<T>::Matrix(int dimensions)
{
	//Set dimensions
	height = dimensions;	width = dimensions;
	//apply dimensions
	matrix.resize(height);
	for (int i = 0; i < height; i++)
		matrix[i].resize(width);
	for (int i = 0; i < dimensions; i++)
		set(i, i, 1);
}
//Construct empty matrix
template <typename T> Matrix<T>::Matrix(int mheight, int mwidth)
{
	//Set dimensions
	height = mheight;	width = mwidth;
	//apply dimensions
	matrix.resize(height);
	for (int i = 0; i < height; i++)
		matrix[i].resize(width);
}
//Construct defined matrix
template<typename T> Matrix<T>::Matrix(std::initializer_list<std::vector<T>> input) {
	height = 0;
	for (std::vector<T> i : input) {
		height++;
		matrix.push_back(i);
		int elemWidth = i.size();
		width = elemWidth > width ? elemWidth : width;
	}
	for (int i = 0; i < height; i++)
		matrix[i].resize(width);
}
//Copy existing matrix
template<typename T> Matrix<T>::Matrix(const Matrix<T>& original) {
	//Set dimensions
	height = original.getHeight();
	width = original.getWidth();
	//apply dimensions
	matrix.resize(height);
	for (int i = 0; i < height; i++)
		matrix[i].resize(width);
	//populate data
	for (int i = 0; i < original.getWidth(); i++) for (int j = 0; j < original.getHeight(); j++) {
		set(j, i, original.get(j,i));
	}
}
template <typename T> Matrix<T>::~Matrix()
{
}

//--------------------OPERATORS--------------------

//Fetch data from matrix via brackets
template <typename T> std::vector<T> Matrix<T>::operator[](int i){
	if (i < height)	//requesting a valid height
		return matrix[i];
	else	//requesting an invalid height
		throw std::invalid_argument("Array: Out of bounds. Matrix<T>::operator[]");
	return matrix[0];
}
//Add two matrices of equal dimensions
template<typename T> Matrix<T> Matrix<T>::operator+(Matrix<T> otherMatrix) const
{
	if (this->getHeight() != otherMatrix.getHeight() || this->getWidth() != otherMatrix.getWidth())
		throw InvalidDimensions("Cannot add matrices of different sizes");
	Matrix newMatrix = otherMatrix;
	for (int i = 0; i < width; i++) for (int j = 0; j < height; j++)
		newMatrix.set(j, i, get(j, i) + otherMatrix.get(j, i));
	return newMatrix;
}
template<typename T> Matrix<T> Matrix<T>::operator+=( Matrix<T>& otherMatrix)
{
	for (int i = 0; i < width; i++) for (int j = 0; j < height; j++)
		set(j, i, get(j, i) + otherMatrix.get(j, i));
	return (*this);
}
//Add all items in matrix by scalar
template<typename T> Matrix<T> Matrix<T>::operator+(T scalar) const
{
	Matrix newMatrix(this->getHeight(),this->getWidth());
	for (int i = 0; i < width; i++) for (int j = 0; j < height; j++)
		newMatrix.set(j, i, get(j, i) + scalar);
	return newMatrix;
}
template<typename T> Matrix<T> Matrix<T>::operator+=(T scalar)
{
	for (int i = 0; i < width; i++) for (int j = 0; j < height; j++)
		set(j, i, get(j, i) + scalar);
	return (*this);
}
//Subtract two matricies of equal dimensions
template<typename T> Matrix<T> Matrix<T>::operator-(Matrix<T> otherMatrix) const
{
	if (this->getHeight() != otherMatrix.getHeight() || this->getWidth() != otherMatrix.getWidth())
		throw InvalidDimensions("Cannot subtract matrices of different sizes");
	Matrix newMatrix = otherMatrix;
	for (int i = 0; i < width; i++) for (int j = 0; j < height; j++)
		newMatrix.set(j, i, get(j, i) - otherMatrix.get(j, i));
	return newMatrix;
}
template<typename T> Matrix<T> Matrix<T>::operator-=(Matrix<T> otherMatrix)
{
	if (this->getHeight() != otherMatrix.getHeight() || this->getWidth() != otherMatrix.getWidth())
		throw InvalidDimensions("Cannot subtract matrices of different sizes");
	for (int i = 0; i < width; i++) for (int j = 0; j < height; j++)
		set(j, i, get(j, i) - otherMatrix.get(j, i));
	return (*this);
}
//Subtract all items in matrix by scalar
template<typename T> Matrix<T> Matrix<T>::operator-(T scalar) const
{
	Matrix newMatrix(this->getHeight(), this->getWidth());
	for (int i = 0; i < width; i++) for (int j = 0; j < height; j++)
		newMatrix.set(j, i, get(j, i) - scalar);
	return newMatrix;
}
template<typename T> Matrix<T> Matrix<T>::operator-=(T scalar)
{
	for (int i = 0; i < width; i++) for (int j = 0; j < height; j++)
		set(j, i, get(j, i) - scalar);
	return (*this);
}
//Multiply this matrix by a scalar
template<typename T> Matrix<T> Matrix<T>::operator*(T scalar) const
{
	Matrix newMatrix = (*this);
	for (int i = 0; i < width; i++) for (int j = 0; j < height; j++)
		newMatrix.set(j, i, get(j, i) * scalar);
	return newMatrix;
}
template<typename T> Matrix<T> Matrix<T>::operator*=(T scalar)
{
	*this = *this * scalar;
	return (*this);
}
//Dot product with another matrix
template<typename T> Matrix<T> Matrix<T>::operator*(Matrix<T> otherMatrix) const
{
	//TODO::ADD FAILURE CONDITIONS
	if (getWidth() != otherMatrix.getHeight())
		throw InvalidDimensions("Cannot multiply matrices");
	Matrix<T> newMatrix(height, otherMatrix.getWidth());
	for (int i = 0; i < otherMatrix.getWidth(); i++) for (int j = 0; j < height; j++) {
		//iterates vertically across output
		T output = 0;
		for (int k = 0; k < width; k++)
			output += get(j, k)*otherMatrix.get(k, i);
		newMatrix.set(j, i, output);
	}
	return newMatrix;
}
template<typename T> Matrix<T> Matrix<T>::operator*=(Matrix<T> otherMatrix)
{
	(*this) = (*this)*otherMatrix;
	return (*this);
}
//Divide this matrix by another matrix
template<typename T> Matrix<T> Matrix<T>::operator/(Matrix<T> otherMatrix) const
{
	if (otherMatrix.getHeight() != otherMatrix.getWidth())
		throw InvalidDimensions("Cannot divide by a non-square matrix");

	return (*this) * (otherMatrix.inv());
}
template<typename T> Matrix<T> Matrix<T>::operator/=(Matrix<T> otherMatrix)
{
	*this = *this / otherMatrix;
	return (*this);
}
//Divide all items in the matrix by a constant
template<typename T> Matrix<T> Matrix<T>::operator/(T scalar) const
{
	if (scalar == 0) throw DivideByZero("Cannot divide matrix by 0");
	Matrix<T> out(getHeight(), getWidth());
	for (int i = 0; i < getWidth(); i++) for (int j = 0; j < getHeight(); j++)
		out.set(j, i, get(j, i) / scalar);
	return out;
}
template<typename T> Matrix<T> Matrix<T>::operator/=(T scalar)
{
	*this = *this / scalar;
	return (*this);
}
//Find determinant of the matrix
template<typename T> T Matrix<T>::det()
{
	return Matrix<T>::det(*this);
}
//Find determinant of the matrix
template<typename T> T Matrix<T>::det(const Matrix<T> m)
{
	if (m.getWidth() < 2 || m.getHeight() < 2)
		throw InvalidDimensions("Matrix is not minimum dimensions");
	if (m.getWidth() != m.getHeight())
		throw InvalidDimensions("Matrix is not square");
	//Matrix is now assumed to be viable square
	if (m.getWidth() == 2)	//Recursive base case
		return (m.get(0, 0)*m.get(1, 1)) - (m.get(1, 0)*m.get(0, 1));
	T det = 0;
	int inverter = 1;
	for (int multCol = 0; multCol < m.getWidth(); multCol++) {
		//build submatrix
		Matrix<T> sub(m.getHeight() - 1, m.getWidth() - 1);
		int currSubCol = 0;
		for (int i = 0; i < m.getWidth(); i++) {
			if (currSubCol == multCol) i++;
			for (int j = 1; j < m.getHeight() && i<m.getWidth(); j++) {
				sub.set(j-1, currSubCol, m.get(j, i));
			}
			currSubCol++;
		}
		det += (m.get(0, multCol)*sub.det())*inverter;
		inverter *= -1;
	}
	return det;
}
//Find inverse of the matrix
template<typename T> Matrix<T> Matrix<T>::inv()
{
	return Matrix<T>::inv(*this);
}
//Find inverse of the matrix
template<typename T> Matrix<T> Matrix<T>::inv(Matrix<T> m)
{
	T mdet = m.det();
	if (mdet == 0)
		throw NotInvertable("Matrix has determinant 0 and cannot be inverted");
	if (m.getWidth() != m.getHeight())
		throw NotInvertable("Matrix is not square");
	if (m.getWidth() == 2 && m.getHeight()) {
		Matrix<T> temp({ {m.get(1,1),-m.get(0,1)},{-m.get(1,0),m.get(0,0)} });
		return temp*(1.0 / det(m));
	}
	Matrix<T> m_t = m.transpose();
	Matrix<T> m_t_det = m_t;
	for (int i = 0; i < m_t.getWidth(); i++) for (int j = 0; j < m_t.getHeight(); j++) {
		m_t_det.set(j, i, m_t.submatrix(j, i).det());
	}
	Matrix<T> adj_m(m.getHeight(), m.getWidth());
	int inverter = 1;
	for (int i = 0; i < m_t.getWidth(); i++) for (int j = 0; j < m_t.getHeight(); j++) {
		adj_m.set(j, i, inverter*m_t_det.get(j,i));
		inverter *= -1;
	}
	return adj_m*(1.0/det(m));
}
//Transpose matrix
template<typename T> Matrix<T> Matrix<T>::transpose()
{
	return Matrix<T>::transpose(*this);
}
//Transpose matrix
template<typename T> Matrix<T> Matrix<T>::transpose(Matrix<T> m)
{
	Matrix<T> newMatrix(m.getWidth(), m.getHeight());
	for (int i = 0; i < m.getWidth(); i++) for (int j = 0; j < m.getHeight(); j++) {
		newMatrix.set(i, j, m.get(j, i));
	}
	return newMatrix;
}
//Trace is the sum of elements on the main diagonal
template<typename T> T Matrix<T>::trace()
{
	if (getWidth() != getHeight())
		throw NotInvertable("Matrix must be square to find trace");
	T sum = 0;
	for (int i = 0; i < getHeight(); i++)
		sum += get(i, i);
	return sum;
}
//Trace is the sum of elements on the main diagonal
template<typename T> T Matrix<T>::trace(Matrix<T> m)
{
	return m.trace();
}


//--------------------DATA ACTION FUNCTIONS--------------------

//Set an item in matrix
template<typename T> void Matrix<T>::set(int y, int x, T newValue) {
	if(y<height && x<width)
		matrix[y][x] = newValue;
	else
		throw std::invalid_argument("Array: Out of bounds. Matrix<T>::set");
}
//Gets item from matrix
template<typename T> T Matrix<T>::get(int y, int x) const{
	if (y >= getHeight() || x >= getWidth())
		throw OutOfBounds("Tried to access out of bounds index");
	return matrix[y][x];
}
//Inserts new column at specified location. Column currently there is moved to the left
template<typename T> void Matrix<T>::insertCol(int col, std::vector<T> newItems)
{
	if (newItems.size() != getHeight())
		throw BadData("Length of data to append does not match matrix height");
	for (int j = 0; j < getHeight(); j++)
		matrix[j].insert(matrix[j].begin() + col, newItems[j]);
	width++;
}
//Inserts new row at specified location. Row currently there is moved down
template<typename T> void Matrix<T>::insertRow(int row, std::vector<T> newItems)
{
	if (newItems.size() != getWidth())
		throw BadData("Length of data to append does not match matrix width");
	matrix.insert(matrix.begin() + row, newItems);
	height++;
}

//--------------------HELPER FUNCTIONS--------------------

//Returns height of the matrix
template<typename T> int Matrix<T>::getHeight() const {
	return height;
}
//Returns width of the matrix
template<typename T> int Matrix<T>::getWidth() const{
	return width;
}
//Print matrix to console
template<typename T> void Matrix<T>::print()
{
	for (int i = 0; i < height; i++) {
		std::cout << (i == 0 ? "{" : " ") << "{\t";
		for (int j = 0; j < width; j++) {
			std::cout << matrix[i][j]<<"\t";
		}
		if (i < height - 1)
			std::cout << "}\n";
		else
			std::cout << "}}";
	}
	std::cout<<std::endl;
}
//Build a sub-matrix that includes all points not on the specified row/column
template<typename T> Matrix<T> Matrix<T>::submatrix(int y, int x)
{
	Matrix<T> sub(getHeight() - 1, getWidth() - 1);
	int currSubCol = 0;
	int currSubRow = 0;
	for (int i = 0; i < getWidth(); i++) {
		if (currSubCol == x) i++;
		currSubRow = 0;
		for (int j = 0; j < getHeight() && i < getWidth() && currSubRow<getHeight()-1; j++) {
			if (currSubRow == y) j++;
			sub.set(currSubRow, currSubCol, get(j, i));
			currSubRow++;
		}
		currSubCol++;
	}
	return sub;
}


#endif // !cmatriximplement