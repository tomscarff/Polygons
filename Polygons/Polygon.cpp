// Polygon.cpp
// Abstract base class for polygons - an ordered set of vertex locations

#include <cmath>
#include "Polygon.h"

// Constructor and destructor
Polygon::Polygon(const unsigned int n) :
	n(n),
	vertices(new Vector[n])
{
	if (n < 3) {
		std::cerr << "Error: Attempted to create a polygon with less than three vertices." << std::endl;
		exit(1);
	}

	if (vertices == nullptr) {
		std::cerr << "Error: Polygon construction failed. Could not allocate memory for vertices." << std::endl;
		exit(1);
	}
}

Polygon::Polygon(const Polygon& poly) :
	n(poly.n),
	vertices(new Vector[poly.n])
{
	for (unsigned int i{ 0 }; i < size(); i++)
	{
		vertex(i) = poly.vertex(i); // Deep copy
	}
}

Polygon& Polygon::operator= (const Polygon& poly)
{
	if (&poly == this) { return *this; }
	if (n != poly.n) {
		std::cerr << "Error: Attempted to assign to a Polygon with unequal vertex count." << std::endl;
	}
	for (unsigned int i{ 0 }; i < size(); i++)
	{
		vertex(i) = poly.vertex(i); // Deep copy
	}
	return *this;
}

// Accessors
const Vector& Polygon::vertex(const unsigned int i) const
{
	if (i >= size()) {
		std::cerr << "Error: Attempted to access vertex out of range." << std::endl;
		exit(1);
	}
	return vertices[i];
}

Vector& Polygon::vertex(const unsigned int i)
{
	if (i >= size()) {
		std::cerr << "Error: Attempted to access vertex out of range." << std::endl;
		exit(1);
	}
	return vertices[i];
}

// Find centre position: average over vertices
const Vector Polygon::centre() const {
	Vector sum;
	const double inv_size{ 1.0 / size() };
	for (unsigned int i{ 0 }; i < size(); i++) {
		sum += vertex(i);
	}
	return inv_size * sum;
}

// Find the area of the polygon using determinants of the matrix of vertices (formula on Wolfram Mathworld)
const double Polygon::area() const
{
	double sum{ 0 };
	for (unsigned int i{ 0 }; i < size(); i++)
	{
		if (i == size() - 1) { // if it's the last vertex, link to the first
			Matrix M(vertex(i)(1), vertex(i)(2), vertex(0)(1), vertex(0)(2));
			sum += M.det();
		}
		else {
			Matrix M(vertex(i)(1), vertex(i)(2), vertex(i+1)(1), vertex(i+1)(2));
			sum += M.det();
		}
	}
	return std::fabs(0.5 * sum);
}

// Transformations:

// Translate each vertex by vector r
void Polygon::translate(const Vector& r)
{
	for (unsigned int i{ 0 }; i < size(); i++) {
		vertex(i) += r;
	}
	return;
}

// Rotate about the origin of the coord system using a rotation matrix
void Polygon::rotateorigin(const double angle)
{
	using namespace std;
	Matrix R(cos(angle), -sin(angle), sin(angle), cos(angle));
	for (unsigned int i{ 0 }; i < size(); i++) {
		vertex(i) = R * vertex(i);
	}
	return;
}

// Rotate about the centre (centroid) of the polygon. This is done in effect by translating the polygon
// to the origin, rotating it there, and then translating back. (Equivalent to changing the basis of
// the rotation operation: i.e. in matrix operator form: R' = T^(-1) R T; v' = R' v)
void Polygon::rotatecentre(const double angle)
{
	Vector c = centre();
	translate(-c); // move to origin
	this->rotateorigin(angle); // rotate
	translate(c); // move back
	return;
}

// Print info function

void Polygon::printinfo() const
{
	std::cout << this->name() << ":" << std::endl << "	";
	for (unsigned int i{ 0 }; i < size(); i++) {
		std::cout << vertex(i) << " ";
	}
	std::cout << std::endl;
	return;
}

// Derived class function definitions:

void SymmetricPoly::rotateorigin(const double angle)
{
	Polygon::rotateorigin(angle);
	orient += angle; // Same as for Polygon but also logs the change in the shape's orientation
	return;
}


void SymmetricPoly::rescale(const double width, const double height)
{
	Vector c = centre();
	const double ori = orient;
	Matrix S(width, 0, 0, height); // Scaling matrix diag(width, height)
	translate(-c); // move to origin
	rotateorigin(-ori); // remove orientation
	for (unsigned int i{ 0 }; i < size(); i++) {
		vertex(i) = S * vertex(i); // Apply scaling matrix to each vertex
	}
	rotateorigin(ori);
	translate(c);
	return;
}

// GeneralPoly constructor: equally spaces the vertices counter-clockwise on a circle centred at the origin.
GeneralPoly::GeneralPoly(const unsigned int n, const double R) :
	Polygon(n)
{
	const double pi{ 3.14159265 };
	const double angle = 2 * pi / size(); // Angular spacing of vertices in polar coords (rads)
	for (unsigned int i{ 0 }; i < size(); i++) { // x = Rcos(); y = Rsin()
		vertex(i)(1) = R * std::cos(0.5*pi + i*angle); // Add the 90 deg term in the arg so that first vertex is at the top.
		vertex(i)(2) = R * std::sin(0.5*pi + i*angle);
	}
}

// Simply rescale all vertices of the polygon. Unlike for SymmetricPoly, will change centroid of polygon.
void GeneralPoly::rescale(const double x, const double y)
{
	Matrix S(x, 0, 0, y); // Scaling matrix diag(x,y)
	for (unsigned int i{ 0 }; i < size(); i++) {
		vertex(i) = S * vertex(i); // Apply scaling matrix to each vertex
	}
}