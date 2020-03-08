/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

//Screen class meant to hold data that will be displayed to the screen for the user to view
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <iostream>
#include <string>
#include "vector2d.h"

using namespace std;

class Screen{

	public:
		Screen();
		Screen(int col, int row, string data="", char bg='-');
		Screen(Vector2D size, string data="", char bg='-');
		Screen(Screen &screen);
		~Screen();
		
		void Update(string data);
		char GetPixel(int x, int y);
		char GetPixel(const Vector2D &vector);
		string ToString();
		Vector2D GetSize();
	private:
		void Constructor(Vector2D size, string data, char bg);

		Vector2D size;
		char bg;
		char **screenArray;	
};

#endif
