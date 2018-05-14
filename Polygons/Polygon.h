// Polygon.h
// Abstract base class for polygons - an ordered set of vertex locations
#pragma once

#include <string>
#include <memory>
#include "Vector.h"
#include "Matrix.h"

class PolygonManager;

// The abstract base class in the Polygon hierarchy.
class Polygon {
private:
	const unsigned int n; // n-gon - n must be at least equal to 3 to form a polygon
	const std::unique_ptr<Vector[]> vertices; // RAII

protected:
	// Non-const accessor protected so that derived class ctors can initialise themselves,
	// but access is still read-only for clients
	Vector& vertex(const unsigned int i); // non-const accessor

public:
	Polygon(const unsigned int n); // Creates a polygon with n vertices
	virtual ~Polygon() {} // Smart pointers - clean up automatic
	Polygon(const Polygon& poly); // Copy constructor - deep copy

	Polygon& operator= (const Polygon& poly);

	const Vector& vertex(const unsigned int i) const; // const accessor - read-only

	const unsigned int size() const { return n; }
	virtual const std::string name() const = 0; // Returns the name of the shape, e.g. "Square, 7-gon, etc"

	const Vector centre() const; // Returns location of the centroid of the polygon

	const double area() const; // Returns the area of the polygon

	void translate(const Vector& r); // Translate polygon by vector r
	
	virtual void rotateorigin(const double angle); // Rotate about the origin of the coord system
	void rotatecentre(const double angle); // Rotate about the centre of the polygon
	
	virtual void rescale(const double x, const double y) = 0; // Specialised for different shape types
	// E.g. a rectangle must be rescaled such that isn't skewed if it is at an angle.

	void printinfo() const;

	friend PolygonManager; // Not ideal, but PolygonManager::draw() required vertex access
};

// Classes derived from polygon:

// A derived abstract class in the hierarchy for shapes that must retain some form of symmetry; specifically,
// they cannot be skewed by the rescale() function. Classes that inherit from this are Rectangle, Isosceles.
// They must retain information about their orientation such that they can be rescaled relative to their
// proportions - i.e. changing their width and height.
class SymmetricPoly : public Polygon {
private:
	double orient; // angle of orientation (in radians)

public:
	SymmetricPoly(const unsigned int n) :
		Polygon(n),
		orient(0)
	{}
	virtual ~SymmetricPoly() {} // Will also automatically call ~Polygon() to clean up.

	virtual const std::string name() const = 0;
	void rotateorigin(const double angle); // Polygon::rotatecentre() calls this, so only need to override this
	void rescale(const double width, const double height); // Method will be the same for all derived classes.
};


// A derived (non-abstract) class for general n-gons. They are initialised as regular polygons centred on the origin,
// with a circumradius, R, specified by the user. They retain no symmetry, and rescaling in x, y will simply scale 
// them in the main coordinate basis, irrespective of their orientation.
// Pentagon, Hexagon inherit from this - the only difference being their label (i.e. name()) and default n value.
class GeneralPoly : public Polygon {
public:
	GeneralPoly(const unsigned int n, const double R);
	virtual ~GeneralPoly() {}

	virtual const std::string name() const { return std::to_string(size()) + "-gon"; }
	void rescale(const double x, const double y);
};