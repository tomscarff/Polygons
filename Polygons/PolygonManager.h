// PolygonManager.h
// A class for storing and managing all the polygons used in the program.
// Also handles input and output to the console.
#pragma once

#include <vector>
#include "Polygon.h"

class PolygonManager {
private:
	std::vector<Polygon*> polygons;
	
	Polygon* polygon(const unsigned int i) const; // Polygon accessor - does range checking

	unsigned int drawWidth; // Used by draw() - default value is 79.

public:
	PolygonManager() : drawWidth(79) {}
	~PolygonManager();

	const int count() const { return polygons.size(); }

	void listshapes() const;
	void listinfo() const;

	const std::string getname(const unsigned int i) const { return polygon(i)->name(); }
	const double getarea(const unsigned int i) const { return polygon(i)->area(); }

	void addisos(const double base, const double height);
	void addrect(const double width, const double height);
	void addpenta(const double R); // circumradius R
	void addhexa(const double R);
	void addngon(const unsigned int n, const double R); // Add a general (initially regular) n-gon, with circumradius R

	void remove(const unsigned int i); // Remove the ith pgon in the list
	
	void translate(const unsigned int i, const Vector& r); // Translate the ith polygon in the list
	void rotate(const unsigned int i, const double angle);
	void rescale(const unsigned int i, const double x, const double y);

	void translateall(const Vector& r);
	void rotateall(const double angle);
	void rescaleall(const double x, const double y);
	void centreall();

	void setdrawWidth(const unsigned int width);
	void draw() const;
};