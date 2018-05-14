// Matrix.cpp
// A class for matrices - used in functions for transformations (rotation, rescaling)

#include <iostream>
#include "Matrix.h"

Matrix::Matrix()
{
	for (unsigned int i{ 1 }; i <= 2; i++) {
		for (unsigned int j{ 1 }; j <= 2; j++) {
			(*this)(i, j) = 0;
		}
	}
}

Matrix::Matrix(const double a, const double b, const double c, const double d)
{
	(*this)(1, 1) = a;
	(*this)(1, 2) = b;
	(*this)(2, 1) = c;
	(*this)(2, 2) = d;
}

Matrix::Matrix(const Matrix& param)
{
	for (unsigned int i{ 1 }; i <= 2; i++) {
		for (unsigned int j{ 1 }; j <= 2; j++) {
			(*this)(i, j) = param(i, j);
		}
	}
}

const Matrix& Matrix::operator= (const Matrix& rhs)
{
	if (&rhs == this) { return *this; }
	for (unsigned int i{ 1 }; i <= 2; i++) {
		for (unsigned int j{ 1 }; j <= 2; j++) {
			(*this)(i, j) = rhs(i, j);
		}
	}
	return *this;
}

const double& Matrix::operator() (const int i, const int j) const
{
	if (i < 1 || i > 2 || j < 1 || j > 2) {
		std::cerr << "Error: Attempted to access matrix element out of range." << std::endl;
		exit(1);
	}
	return data[2 * (i - 1) + (j - 1)];
}

double& Matrix::operator() (const int i, const int j)
{
	if (i < 1 || i > 2 || j < 1 || j > 2) {
		std::cerr << "Error: Attempted to access matrix element out of range." << std::endl;
		exit(1);
	}
	return data[2 * (i - 1) + (j - 1)];
}

const Matrix Matrix::operator* (const Matrix& rhs) const
{
	Matrix temp;
	for (unsigned int i{ 1 }; i <= 2; i++) {
		for (unsigned int j{ 1 }; j <= 2; j++) {
			temp(i, j) = (*this)(i, 1) * rhs(1, j) + (*this)(i, 2) * rhs(2, j);
		}
	}
	return temp;
}

const double Matrix::det() const
{
	return (*this)(1, 1) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 1);
}

const Matrix operator* (double lhs, const Matrix& rhs)
{
	Matrix temp;
	for (unsigned int i{ 1 }; i <= 2; i++) {
		for (unsigned int j{ 1 }; j <= 2; j++) {
			temp(i, j) = lhs * rhs(i, j);
		}
	}
	return temp;
}

std::ostream& operator<< (std::ostream& os, const Matrix& rhs)
{
	os << rhs(1, 1) << "	" << rhs(1, 2) << std::endl;
	os << rhs(2, 1) << "	" << rhs(2, 2);
	return os;
}