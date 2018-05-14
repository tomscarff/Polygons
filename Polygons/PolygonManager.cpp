// PolygonManager.cpp
// A class for storing and managing all the polygons used in the program.

#include "Derived shapes.h"
#include "PolygonManager.h"

// Polygon accessor:
// Starts at i = 1,...,count
Polygon* PolygonManager::polygon(const unsigned int i) const
{
	if (i > polygons.size()) {
		std::cerr << "Error: Call for polygon " << i << " went out of range." << std::endl;
		exit(1);
	}
	return polygons.at(i - 1);
}

// Destructor:

PolygonManager::~PolygonManager()
{
	if (!polygons.empty()) 
	{
		for (auto it = polygons.begin(); it != polygons.end(); it++) 
		{
			delete *it;
		}
		polygons.clear();
	}
}

// Function to display a list of the polygons and their info
void PolygonManager::listshapes() const
{
	unsigned int i{ 1 };
	for (auto it = polygons.cbegin(); it != polygons.cend(); it++, i++) {
		std::cout << "	" << i << ". " << (*it)->name() << std::endl;
	}
}

void PolygonManager::listinfo() const
{
	unsigned int i{ 1 };
	for (auto it = polygons.cbegin(); it != polygons.cend(); it++, i++) {
		std::cout << i << ". ";
		(*it)->printinfo();
	}
}

// Functions to add polygons:
// Note: factory functions (declared in Derived shapes.h using namespace fact) take care of bad_alloc exception handling.

void PolygonManager::addisos(const double base, const double height)
{
	polygons.push_back(fact::createIsosceles(base, height));
	return;
}

void PolygonManager::addrect(const double width, const double height)
{
	polygons.push_back(fact::createRectangle(width, height));
	return;
}

void PolygonManager::addpenta(const double R)
{
	polygons.push_back(fact::createPentagon(R));
	return;
}

void PolygonManager::addhexa(const double R)
{
	polygons.push_back(fact::createHexagon(R));
	return;
}

void PolygonManager::addngon(const unsigned int n, const double R)
{
	polygons.push_back(fact::createGenPoly(n, R));
	return;
}

// Removing function:
void PolygonManager::remove(const unsigned int i)
{
	unsigned int j{ 1 };
	auto it = polygons.cbegin(); // Increment const_iterator i times
	while (j < i) {
		it++; j++;
	}
	polygons.erase(it);
	return;
}


//

void PolygonManager::translate(const unsigned int i, const Vector& r)
{
	polygon(i)->translate(r);
	return;
}

void PolygonManager::rotate(const unsigned int i, const double angle)
{
	polygon(i)->rotatecentre(angle);
	return;
}

void PolygonManager::rescale(const unsigned int i, const double x, const double y)
{
	polygon(i)->rescale(x, y);
	return;
}

// Transformations to all polygons:

void PolygonManager::translateall(const Vector& r)
{
	for (auto it = polygons.begin(); it != polygons.end(); it++) {
		(*it)->translate(r);
	}
	return;
}

void PolygonManager::rotateall(const double angle)
{
	for (auto it = polygons.begin(); it != polygons.end(); it++) {
		(*it)->rotateorigin(angle);
	}
	return;
}

void PolygonManager::rescaleall(const double x, const double y)
{
	// May not behave as expected, since rescale() works differently for different polygons
	for (auto it = polygons.begin(); it != polygons.end(); it++) {
		(*it)->rescale(x, y);
	}
	return;
}

void PolygonManager::centreall()
{
	Vector sumcentres;
	for (auto it = polygons.begin(); it != polygons.end(); it++) {
		sumcentres += (*it)->centre();
	}
	Vector c{ (1.0 / count())*sumcentres };
	translateall(-c);
	return;
}

void PolygonManager::setdrawWidth(const unsigned int width)
{
	drawWidth = width;
	return;
}