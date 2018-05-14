// Vector.cpp
// A class for (2D) vectors; used for storing vertex locations and for translations

#include <iomanip>
#include <cmath>
#include "Vector.h"

const Vector& Vector::operator= (const Vector& rhs)
{
	if (&rhs == this) { return *this; }
	x = rhs.x;
	y = rhs.y;
	return *this;
}

const Vector& Vector::operator+= (const Vector& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

const Vector& Vector::operator-= (const Vector& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

const double Vector::dot(const Vector& rhs) const
{
	return x*rhs.x + y*rhs.y;
}

const Vector Vector::operator+ (const Vector& rhs) const
{
	Vector temp(x + rhs.x, y + rhs.y);
	return temp;
}

const Vector Vector::operator- (const Vector& rhs) const
{
	Vector temp(x - rhs.x, y - rhs.y);
	return temp;
}

const Vector Vector::operator- () const
{
	Vector temp(-x, -y);
	return temp;
}

const double& Vector::operator() (const int i) const
{
	if (i == 1) { return x; }
	else if (i == 2) { return y; }
	else {
		std::cerr << "Error: Attempted to access vector element out of range." << std::endl;
		exit(1);
	}
}

double& Vector::operator() (const int i)
{
	if (i == 1) { return x; }
	else if (i == 2) { return y; }
	else {
		std::cerr << "Error: Attempted to access vector element out of range." << std::endl;
		exit(1);
	}
}


// Additional operator overloads:

const Vector operator* (double lhs, const Vector& rhs)
{
	Vector temp;
	temp(1) = lhs * rhs(1);
	temp(2) = lhs * rhs(2);
	return temp;
}

const Vector operator* (const Matrix& lhs, const Vector& rhs)
{
	Vector temp;
	for (unsigned int i{ 1 }; i <= 2; i++) {
		temp(i) = lhs(i, 1) * rhs(1) + lhs(i, 2) * rhs(2);
	}
	return temp;
}

std::ostream& operator<< (std::ostream& os, const Vector& rhs)
{
	os << "(";
	if (std::fabs(std::fmod(rhs(1), 1.0)) < 0.01 || std::fabs(rhs(1)) < 0.01) { os << std::fixed << std::setprecision(0) << rhs(1); }
	else { os << std::fixed << std::setprecision(2) << rhs(1); }
	os << ",";
	if (std::fabs(std::fmod(rhs(2), 1.0)) < 0.01 || std::fabs(rhs(2) < 0.01)) { os << std::fixed << std::setprecision(0) << rhs(2); }
	else { os << std::fixed << std::setprecision(2) << rhs(2); }
	os << ")";
	return os;
}