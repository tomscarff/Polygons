// Derived shapes.cpp

#include "Derived shapes.h"

// Specialised polygon constructors:

Isosceles::Isosceles(const double base, const double height) :
	SymmetricPoly(3)
{
	vertex(0) = Vector(0, 0.5*height);
	vertex(1) = Vector(-0.5*base, -0.5*height);
	vertex(2) = Vector(0.5*base, -0.5*height);
}

Rectangle::Rectangle(const double width, const double height) :
	SymmetricPoly(4)
{
	const double a{ 0.5*width }, b{ 0.5*height };
	vertex(0) = Vector(a, b);
	vertex(1) = Vector(-a, b);
	vertex(2) = Vector(-a, -b);
	vertex(3) = Vector(a, -b);
}

// Factory functions:

Polygon* fact::createGenPoly(const int n, const double R)
{
	Polygon* pGenPoly;
	try { pGenPoly = new GeneralPoly(n, R); }
	catch (std::bad_alloc memfail)
	{
		std::cerr << "Error: Failed to create a new GeneralPoly object." << std::endl;
		exit(1);
	}
	return pGenPoly;
}

Polygon* fact::createIsosceles(const double base, const double height)
{
	Polygon* pIsos;
	try { pIsos = new Isosceles(base, height); }
	catch (std::bad_alloc memfail)
	{
		std::cerr << "Error: Failed to create a new Isosceles object." << std::endl;
		exit(1);
	}
	return pIsos;
}

Polygon* fact::createRectangle(const double width, const double height)
{
	Polygon* pRect;
	try { pRect = new Rectangle(width, height); }
	catch (std::bad_alloc memfail)
	{
		std::cerr << "Error: Failed to create a new Rectangle object." << std::endl;
		exit(1);
	}
	return pRect;
}

Polygon* fact::createPentagon(const double R)
{
	Polygon* pPenta;
	try { pPenta = new Pentagon(R); }
	catch (std::bad_alloc memfail)
	{
		std::cerr << "Error: Failed to create a new Pentagon object." << std::endl;
		exit(1);
	}
	return pPenta;
}

Polygon* fact::createHexagon(const double R)
{
	Polygon* pHexa;
	try { pHexa = new Hexagon(R); }
	catch (std::bad_alloc memfail)
	{
		std::cerr << "Error: Failed to create a new Hexagon object." << std::endl;
		exit(1);
	}
	return pHexa;
}

