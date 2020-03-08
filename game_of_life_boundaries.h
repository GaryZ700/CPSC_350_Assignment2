/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

#ifndef _GAME_OF_LIFE_BOUNDARIES_H_
#define _GAME_OF_LIFE_BOUNDARIES_H_

#include "screen.h"

using namespace std;

//Namespace for storing all game of life boundary functions and staticants
class GameOfLifeBoundaries{

	public:
		static void ClassicBoundary(Screen *&screen);
		static void MirrorBoundary(Screen *&screen);
		static void DoughnutBoundary(Screen *&screen);
	private:
		static void InnerLogic(Screen *screen, Screen *newScreen, const Vector2D &position);
		static void ClassicBoundaryLogic(Screen *screen, Screen *newScreen, const Vector2D &position);	
		static void MirrorBoundaryLogic(Screen *screen, Screen *newScreen, const Vector2D &position);
		static void DoughnutBoundaryLogic(Screen *screen, Screen *newScreen, const Vector2D &position);
		static void BuildNextGeneration(Screen *&screen, void (*boundaryLogic)(Screen*, Screen*, const Vector2D&));
};

#endif
