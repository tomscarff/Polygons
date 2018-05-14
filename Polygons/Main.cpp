// Main.cpp
// Main function file

#include <iostream>
#include <vector>
#include "Vector.h"
#include"Matrix.h"
#include "Polygon.h"
#include "Derived shapes.h"
#include "PolygonManager.h"
#include "InputHandler.h"

using namespace std;

int main() {
	PolygonManager polyMan;
	InputHandler inpHan(&polyMan);

	return 0;
}