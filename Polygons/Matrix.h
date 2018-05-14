// Matrix.h
// A class for matrices - used in functions for transformations (rotation, rescaling)
#pragma once

class Matrix {
private:
	double data[4];

public:
	Matrix();
	Matrix(const double a, const double b, const double c, const double d);	// a	b
																			// c	d
	~Matrix() {}
	Matrix(const Matrix& param);

	const Matrix& operator= (const Matrix& rhs);

	const double& operator() (const int i, const int j) const;
	double& operator() (const int i, const int j);

	const Matrix operator* (const Matrix& rhs) const;

	const double det() const; // determinant
};

// Additional operator overloads:
const Matrix operator* (double lhs, const Matrix& rhs);

std::ostream& operator<< (std::ostream& os, const Matrix& rhs);