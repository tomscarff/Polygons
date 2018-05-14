// Derived shapes.h

// Classes for polygons derived from the abstract base class, Polygon.
// Shapes: 
//		Isosceles, Rectangle, Pentagon (non-regular), Hexagon (non-regular)

// Also includes declarations of factory functions for objects of these classes, plus GeneralPoly.
#pragma once

#include "Polygon.h"

class Isosceles : public SymmetricPoly {
public:
	Isosceles(const double base, const double height);
	~Isosceles() {}
	const std::string name() const { return "Isosceles triangle"; }
};

class Rectangle : public SymmetricPoly {
public:
	Rectangle(const double width, const double height);
	~Rectangle() {}
	const std::string name() const { return "Rectangle"; }
};

class Pentagon : public GeneralPoly {
public:
	Pentagon(const double R) :
		GeneralPoly(5, R)
	{}
	~Pentagon() {}
	const std::string name() const { return "Pentagon"; }
};

class Hexagon : public GeneralPoly {
public:
	Hexagon(const double R) :
		GeneralPoly(6, R)
	{}
	~Hexagon() {}
	const std::string name() const { return "Hexagon"; }
};

namespace fact {

	// Factory functions: return a base class pointer to a newed polygon object.
	// Each do exception handling to check and abort if allocation fails.

	Polygon* createGenPoly(const int n, const double R);
	Polygon* createIsosceles(const double base, const double height);
	Polygon* createRectangle(const double width, const double height);
	Polygon* createPentagon(const double R);
	Polygon* createHexagon(const double R);

}