// Vector.h
// A class for (2D) vectors; used for storing vertex locations and for translations
#pragma once

#include <iostream>
#include "Matrix.h"

class Vector {
private:
	double x, y;

public:
	Vector() : // default ctor
		x(0),
		y(0)
	{}
	Vector(double x, double y) : // parameterised ctor
		x(x),
		y(y)
	{}
	
	~Vector() {} // destructor
	
	Vector(const Vector& param) : // copy ctor
		x(param.x),
		y(param.y)
	{}

	const Vector& operator= (const Vector& rhs);
	const Vector& operator+= (const Vector& rhs);
	const Vector& operator-= (const Vector& rhs);

	const double dot(const Vector& rhs) const; // scalar product

	const Vector operator+ (const Vector& rhs) const;
	const Vector operator- (const Vector& rhs) const;
	const Vector operator- () const; // inverse vector i.e -(x,y) = (-x,-y)

	const double& operator() (const int i) const; // element accessor
	double& operator() (const int i); // overload for non const vectors
};

// Additional operator overloads:
// (Note: using non-member non-friend functions for greater encapsulation)
const Vector operator* (double lhs, const Vector& rhs);
const Vector operator* (const Matrix& lhs, const Vector& rhs); // Matrix transformation

std::ostream& operator<< (std::ostream& os, const Vector& rhs);