// InputHandler.cpp
// A class designed to handle inputs from the console, and use them to execute commands
// in the object manager. It holds a pointer to an existing object manager. 

#include "InputHandler.h"
using namespace std;

// Constructor / Destructor

InputHandler::InputHandler(PolygonManager* pm) :
	handle(pm),
	isRunning(true)
{
	cout << "--------WELCOME TO POLYGON--------------------------------------------------" << endl << endl;
	printhelp();
	cout << "----------------------------------------------------------------------------" << endl;
	
	cout << "Below is a list of enterable commands. To bring it up again, enter 'list' as a \ncommand." << endl;
	listinputcommands();
	getinput();
}

InputHandler::~InputHandler()
{
	cout << endl;
	cout << "--------THANK YOU FOR USING POLYGON-----------------------------------------" << endl;
}

// List commands
void InputHandler::listinputcommands() const
{
	cout << "	'add'		- Add a type of polygon from a list" << endl;
	cout << "	'remove'	- Remove one of the polygons" << endl;
	cout << "	'list'		- List the polygons and their vertices, or the commands" << endl;
	cout << "			  again" << endl;
	cout << "	'move'		- Translate a polygon (or all) by a specified vector" << endl;
	cout << "	'rotate'	- Rotate a polygon (or all) by a specified angle" << endl;
	cout << "	'rescale'	- Rescale a polygon" << endl;
	cout << "	'centre'	- Centres all the polygons collectively" << endl;
	cout << "	'area'		- Calculate the area of a polygon" << endl;
	cout << "	'draw'		- Draw the polygons to the console" << endl;
	cout << "	'finish'	- End the program" << endl;
	cout << "If you have entered a command and wish to cancel it, enter 0." << endl;
}

void InputHandler::printhelp() const
{
	cout << "Please enter a command from the list below." << endl;
	cout  << endl;
}

void InputHandler::getinput()
{
	do {
		cout << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "Please enter a command:" << endl;
		cout << ">";
		clearcin(); // reset the buffer
		getcommand();
	} while (isRunning); // Repeat
	return;
}

// Gets the input string from cin, and wires it up to various commands
void InputHandler::getcommand()
{
	string command{ readinput<string>() };

	if (command.compare("add") == 0) { addcommand(); }
	else if (command.compare("remove") == 0) { removecommand(); }
	else if (command.compare("list") == 0) { listcommand(); }
	else if (command.compare("move") == 0) { movecommand(); }
	else if (command.compare("rotate") == 0) { rotcommand(); }
	else if (command.compare("rescale") == 0) { rescalecommand(); }
	else if (command.compare("centre") == 0) { handle->centreall(); cout << "Polygons centred." << endl; }
	else if (command.compare("area") == 0) { areacommand(); }
	else if (command.compare("draw") == 0) { handle->draw(); }
	else if (command.compare("finish") == 0) { isRunning = false; } // Cuts the main loop
	else {
		cout << "Invalid input." << endl;
		return;
	}
}

//////////////
// COMMANDS //
//////////////

// Add a shape to the linked PolygonManager
void InputHandler::addcommand() const
{
	cout << "Please enter the number to choose from one of the following shapes \nto add:" << endl;
	cout << "(Note: Shapes 3, 4, and 5 will be constructed as regular polygons, " << endl;
	cout << "but may not retain their regularity when manipulated by the rescale command.)" << endl;
	cout << "	1. Isosceles triangle" << endl;
	cout << "	2. Rectangle" << endl;
	cout << "	3. Pentagon" << endl;
	cout << "	4. Hexagon" << endl;
	cout << "	5. General n-gon" << endl;
	cout << "Or 0 to cancel." << endl;
	
	try {
		cout << ">";
		clearcin();
		int choice{ readinput<int>() };
		if (choice == 0) {
			cout << "Command cancelled." << endl;
			return;
		}
		else if (choice == 1) { // Add isos triangle
			cout << "Please enter the base-width and height of the triangle, e.g. '2 4':" << endl;
			cout << ">";
			clearcin();
			double base{ readinput<double>() };
			double height{ readinput<double>() };
			if (base > 0 && height > 0) {
				handle->addisos(base, height);
				cout << "Isosceles of base " << base << " and height " << height << " added." << endl;
				return;
			}
			else throw bad_input;
		}
		else if (choice == 2) { // Add rectangle
			cout << "Please enter the width and height of the rectangle, e.g. '2 4':" << endl;
			cout << ">";
			clearcin();
			double width{ readinput<double>() };
			double height{ readinput<double>() };
			if (width > 0 && height > 0) {
				handle->addrect( width, height);
				cout << "Rectangle of width " << width << " and height " << height << " added." << endl;
				return;
			}
			else throw bad_input;
		}
		else if (choice == 3) { // Add pentagon
			cout << "Please enter the circumradius of the pentagon:" << endl;
			cout << ">";
			clearcin();
			double R{ readinput<double>() };
			if (R > 0) {
				handle->addpenta(R);
				cout << "Pentagon of circumradius " << R << " added." << endl;
				return;
			}
			else throw bad_input;
		}
		else if (choice == 4) { // Add hexagon
			cout << "Please enter the circumradius of the hexagon:" << endl;
			cout << ">";
			clearcin();
			double R{ readinput<double>() };
			if (R > 0) {
				handle->addhexa(R);
				cout << "Hexagon of circumradius " << R << " added." << endl;
				return;
			}
			else throw bad_input;
		}
		else if (choice == 5) { // Add ngon
			cout << "Please enter the number of vertices of the polygon (must be at least 3):" << endl;
			cout << ">";
			clearcin();
			int n{ readinput<int>() };
			if (n < 3) { throw bad_input; }
			cout << "Please enter the circumradius of the polygon:" << endl;
			cout << ">";
			clearcin();
			double R{ readinput<double>() };
			if (R > 0) {
				handle->addngon(n, R);
				cout << n << "-gon of circumradius " << R << " added." << endl;
				return;
			}
			else {
				cout << "Invalid input." << endl;
				return;
			}
		}
	}
	catch (int flag) {
		if (flag == bad_input) {
			cout << "Invalid input." << endl;
			return;
		}
	}

}

// Remove a shape to the linked PolygonManager
void InputHandler::removecommand() const
{
	cout << "Please enter the number of the polygon you wish to remove, or 0 to cancel:" << endl;
	handle->listshapes();
	try {
		cout << ">";
		clearcin();
		int inputint{ readinput<int>() }; // If input was a string, will throw exception
		if (inputint == 0) {
			cout << "Command cancelled." << endl;
			return;
		}
		if (inputint < 1 || inputint > handle->count()) {
			cout << "Invalid input." << endl;
			return;
		}
		cout << handle->getname(inputint) << " removed." << endl;
		handle->remove(inputint);
		return;
	}
	catch (int flag) {
		if (flag == bad_input) {
			cout << "Invalid input." << endl;
			return;
		}
	}
}

// Choose a list to show
void InputHandler::listcommand() const
{
	cout << "Please enter the number to select which list you would like to see:" << endl;
	cout << "	1. List of shapes (name only)" << endl;
	cout << "	2. List of shapes (name and vertex list)" << endl;
	cout << "	3. List of commands" << endl;
	cout << "Or 0 to cancel." << endl;

	try {
		cout << ">";
		clearcin();
		int choice{ readinput<int>() };
		if (choice == 0) {
			cout << "Command cancelled." << endl;
			return;
		}
		else if (choice == 1) {
			handle->listshapes();
			return;
		}
		else if (choice == 2) {
			handle->listinfo();
			return;
		}
		else if (choice == 3) {
			listinputcommands();
			return;
		}
		else {
			cout << "Invalid input." << endl;
			return;
		}
	}
	catch (int flag) {
		if (flag == bad_input) {
			cout << "Invalid input." << endl;
			return;
		}
	}
}

/////////////////////////////
// TRANSFORMATION COMMANDS //
/////////////////////////////

// Translate one or all polygons
void InputHandler::movecommand() const
{
	cout << "Please enter the number of the polygon you wish to translate, or enter 'all', \nor 0 to cancel:" << endl;
	handle->listshapes();
	try {
		cout << ">";
		clearcin();
		int inputint{ readinput<int>() }; // If input was a string, will throw exception
		if (inputint == 0) {
			cout << "Command cancelled." << endl;
			return;
		}
		if (inputint < 0 || inputint > handle->count()) {
			cout << "Invalid input." << endl;
			return;
		}
		cout << "Please enter the x and y coords you wish to translate the " << lowercase(handle->getname(inputint));
		cout << " \nby, separated by a space, e.g. '-3.5 2.8':" << endl;
		try {
			cout << ">";
			clearcin();
			double inputx{ readinput<double>() };
			double inputy{ readinput<double>() };
			handle->translate(inputint, Vector(inputx, inputy)); // Translate polygon using inputs
			cout << "Translated " << lowercase(handle->getname(inputint)) << " by vector " << Vector(inputx, inputy) << "." << endl;
			return;
		}
		catch (int flag) {
			if (flag == bad_input) {
				cout << "Invalid input." << endl;
				return;
			}
		}
	}
	catch (int flag) {
			if (flag == bad_input) { // Input was a string; make sure it was 'all'
				cin.clear(); // Clear the failed bit, but don't sync yet
				string inputstring{ readinput<string>() };
				if (inputstring.compare("all") == 0) {
					try {
						cout << "Please enter the x and y coords you wish to translate the polygons by, \ne.g. '-3.5 2.8':" << endl;
						cout << ">";
						clearcin();
						double inputx{ readinput<double>() }; // Will throw exceptions and cancel if nonsense is entered
						double inputy{ readinput<double>() };
						handle->translateall(Vector(inputx, inputy));
						cout << "Translated all polygons by vector " << Vector(inputx, inputy) << "." << endl;
						return;
					}
					catch (int flag) {
						if (flag == bad_input) {
							cout << "Invalid input." << endl;
							return;
						}
					}
				}
		}
	}
}

// Rotate one or all polygons
void InputHandler::rotcommand() const
{
	const double pi{ 3.14159265 };
	cout << "Please enter the number of the polygon you wish to rotate, or enter 'all', \nor 0 to cancel:" << endl;
	handle->listshapes();
	try {
		cout << ">";
		clearcin();
		int inputint{ readinput<int>() }; // If input was a string, will throw exception
		if (inputint == 0) {
			cout << "Command cancelled." << endl;
			return;
		}
		if (inputint < 0 || inputint > handle->count()) {
			cout << "Invalid input." << endl;
			return;
		}
		cout << "Please enter the angle you wish to rotate the " << lowercase(handle->getname(inputint));
		cout << " \nby, in degrees:" << endl;
		try {
			cout << ">";
			clearcin();
			double angledeg{ readinput<double>() }; // in degrees
			double angle{ angledeg * 2 * pi / 360 };  // in rads
			handle->rotate(inputint, angle); // Translate polygon using inputs
			cout << "Rotated " << lowercase(handle->getname(inputint)) << " by angle " << angledeg << " degrees." << endl;
			return;
		}
		catch (int flag) {
			if (flag == bad_input) {
				cout << "Invalid input." << endl;
				return;
			}
		}
	}
	catch (int flag) {
		if (flag == bad_input) { // Input was a string; make sure it was 'all'
			cin.clear(); // Clear the failed bit, but don't sync yet
			string inputstring{ readinput<string>() };
			if (inputstring.compare("all") == 0) {
				try {
					cout << "Please enter the angle you wish to rotate the polygons by, in degrees:" << endl;
					cout << ">";
					clearcin();
					double angledeg{ readinput<double>() }; // in degrees
					double angle{ angledeg * 2 * pi / 360 };  // in rads
					handle->rotateall(angle);
					cout << "Rotated all polygons by vector " << angledeg << " degrees." << endl;
					return;
				}
				catch (int flag) {
					if (flag == bad_input) {
						cout << "Invalid input." << endl;
						return;
					}
				}
			}
		}
	}
}

// Rescale one polygon
void InputHandler::rescalecommand() const
{
	cout << "Please enter the number of the polygon you wish to rescale, \nor 0 to cancel:" << endl;
	handle->listshapes();
	try {
		cout << ">";
		clearcin();
		int inputint{ readinput<int>() }; // If input was a string, will throw exception
		if (inputint == 0) {
			cout << "Command cancelled." << endl;
			return;
		}
		if (inputint < 0 || inputint > handle->count()) {
			cout << "Invalid input." << endl;
			return;
		}
		cout << "Please enter factors by which you want to scale the " << lowercase(handle->getname(inputint));
		cout << " \nby in x and y directions, e.g. '-2 1.5':" << endl;
		try {
			cout << ">";
			clearcin();
			double inputx{ readinput<double>() };
			double inputy{ readinput<double>() };
			handle->rescale(inputint, inputx, inputy); // Translate polygon using inputs
			cout << "Rescaled " << lowercase(handle->getname(inputint)) << " by factors x:" << inputx << " and y:" << inputy <<  "." << endl;
			return;
		}
		catch (int flag) {
			if (flag == bad_input) {
				cout << "Invalid input." << endl;
				return;
			}
		}
	}
	catch (int flag) {
		if (flag == bad_input) { // Input was a string; invalidate
			cout << "Invalid input." << endl;
			return;
		}
	}
}

// Area command - print the area of polygon to the console
void InputHandler::areacommand() const
{
	cout << "Please enter the number of the polygon you would like the area of, or 0 to \ncancel:" << endl;
	handle->listshapes();
	try {
		cout << ">";
		clearcin();
		int inputint{ readinput<int>() }; // If input was a string, will throw exception
		if (inputint == 0) {
			cout << "Command cancelled." << endl;
			return;
		}
		if (inputint < 1 || inputint > handle->count()) {
			cout << "Invalid input." << endl;
			return;
		}
		cout << "Area of the " << handle->getname(inputint) << " is " << handle->getarea(inputint) << "." << endl;
		return;
	}
	catch (int flag) {
		if (flag == bad_input) {
			cout << "Invalid input." << endl;
			return;
		}
	}
}


void InputHandler::clearcin() const
{
	cin.clear();
	cin.sync();
}


// Convenience function for strings:
const std::string lowercase(std::string str) {
	std::string lower;
	for (unsigned int i{ 0 }; i < str.size(); i++) {
		lower += tolower(str.at(i));
	}
	return lower;
}