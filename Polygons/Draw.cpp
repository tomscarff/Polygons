// Draw.cpp
// Definition of PolygonManager::draw()

// Uses the Bresenham line algorithm on all the lines of the polygons to fill a 2D 
// array of bools - "pixels", which are then used tp draw to the console.

// Disclaimer: Some of the guts of the algorithm has been taken from the Rosetta Code article
// on the Bresenham line algorithm, which is open source. I've indicated where in the code.
// The rest of the methods (boolean pixels, drawing method, scaling method etc) are mine.

#include <cmath>
#include <string>
#include <iostream>
#include "PolygonManager.h"

using namespace std;

void PolygonManager::draw() const
{
	// Set up the 'pixels'
	bool pixels[100][80] = { false };

	const double pixelAspectRatio{ 0.5 }; // x:y - Need to have fewer pixels in y direction to compensate, i.e. make image square
	const unsigned int maxWidth{ drawWidth }; // 79 by default
	const unsigned int maxHeight{ (const unsigned int)(pixelAspectRatio*drawWidth) };
	
	// Iterate over all the polygons' vertices to find the boundaries of our image, i.e. largest |x| or |y| value.
	double maxX{ 0 };
	for (auto it{ polygons.cbegin() }; it != polygons.cend(); it++)
	{
		for (unsigned int i{ 0 }; i < (*it)->size(); i++) {
			double newX{ (*it)->vertex(i)(1) }, newY{ (*it)->vertex(i)(2) };
			if (fabs(newX) > maxX) { maxX = fabs(newX); }
			if (fabs(newY) > maxX) { maxX = fabs(newY); }
		}
	}
	maxX *= 1.2; // Add an extra 20% of free space around the image

	// Will need to scale all vertex locations to give them in terms of pixel locations:
	const double scaleX{ maxWidth / (2.0 * maxX) };
	const double scaleY{ maxHeight / (2.0 * maxX) };

	const unsigned int midX{ maxWidth / 2 }, midY{ maxHeight / 2 };

	// Now iterate over polygons using the Bresenham line algorithm to populate pixels.
	for (auto it{ polygons.cbegin() }; it != polygons.cend(); it++)
	{
		// Iterate over vertices to get lines
		for (unsigned int i{ 0 }; i < (*it)->size(); i++)
		{
			double x1, x2, y1, y2;
			if (!(i == (*it)->size() - 1)) { // connect to next vertex if there is one
				x1 = scaleX * (*it)->vertex(i)(1); 
				x2 = scaleX * (*it)->vertex(i+1)(1);
				y1 = scaleY * (*it)->vertex(i)(2);
				y2 = scaleY * (*it)->vertex(i+1)(2);
			}
			else { // last vertex - connect to first vertex
				x1 = scaleX * (*it)->vertex(i)(1);
				x2 = scaleX * (*it)->vertex(0)(1);
				y1 = scaleY * (*it)->vertex(i)(2);
				y2 = scaleY * (*it)->vertex(0)(2);
			}
			
			// The next few lines were borrowed from Rosetta Code
			const bool steep = (fabs(y2 - y1) > fabs(x2 - x1)); 
			if (steep)
			{
				std::swap(x1, y1);
				std::swap(x2, y2);
			}

			if (x1 > x2)
			{
				std::swap(x1, x2);
				std::swap(y1, y2);
			}

			const double dx = x2 - x1;
			const double dy = fabs(y2 - y1);

			double error = dx / 2.0;
			const int ystep = (y1 < y2) ? 1 : -1;
			int y = (int)y1;

			const int maxX = (int)x2;

			for (int x = (int)x1; x<maxX; x++)
			{
				if (steep)
				{
					// set pixel at y,x
					pixels[y + midX][x + midY] = true;
				}
				else
				{
					// set pixel at x,y
					pixels[x + midX][y + midY] = true;
				}

				error -= dy;
				if (error < 0)
				{
					y += ystep;
					error += dx;
				}
			}
		}
	}

	// Draw the pixels
	for (int y{ (const int)maxHeight }; y >= 0; y--)
	{
		string line;
		for (int x{ 0 }; x < maxWidth; x++)
		{
			if (!pixels[x][y] && x != midX && y != midY)
			{
				line += " "; // empty space
			}
			else if (!pixels[x][y] && x != midX && y == midY)
			{
				line += "-"; // x-axis
			}
			else if (!pixels[x][y] && x == midX && y != midY)
			{
				line += "|"; // y-axis
			}
			else if (!pixels[x][y] && x == midX && y == midY)
			{
				line += "O"; // origin
			}
			else if (pixels[x][y])
			{
				line += "x"; // shape!
			}
		}
		cout << line << endl;
	}
	cout << endl;
	
	// Print image size
	cout << "The width of the image is " << 2 * maxX << " units." << endl;
}