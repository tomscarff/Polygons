// InputHandler.h
// A class designed to handle inputs from the console, and use them to execute commands
// in a PolygonManager. It holds a pointer to an existing PolygonManager. 
#pragma once

#include "PolygonManager.h"

class InputHandler {
private:
	PolygonManager* const handle; // const pointer to non-const PolygonManager
	bool isRunning; // Read-only access
	const int bad_input{ -1 }; // Bad input flag

	void listinputcommands() const;
	void printhelp() const;

	void getcommand();

	void addcommand() const;
	void removecommand() const;
	void listcommand() const;
	void movecommand() const;
	void rotcommand() const;
	void rescalecommand() const;
	void areacommand() const;
	
	template<class T>
	const T readinput() const;
	
	// Clear the input buffer and reset
	void clearcin() const;

public:
	InputHandler(PolygonManager* pm);
	~InputHandler();

	void getinput();
};

// Utility template function, used to read a generic object from std::cin.
// Throws bad_input exceptions.
template<class T>
const T InputHandler::readinput() const
{
	using namespace std;
	T input;
	cin >> input;
	if (!cin.good()) { 
		throw bad_input; 
	}
	return input;
}

// Convenience function for strings
const std::string lowercase(std::string str);