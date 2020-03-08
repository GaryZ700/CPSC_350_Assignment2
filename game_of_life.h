/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <fstream>
#include <exception>
#include "menu.h"
#include "user_input.h"
#include "screen.h" 
#include "game_of_life_simulation.h"
#include "game_of_life_constants.h"

using namespace std;

//Game of Life Class to Create Instances of the Game of Life Simulation to Run
class GameOfLife{

	public:
		GameOfLife();
		void MainMenu();
		
	private:
		Screen* LoadFile();
		Screen* RandomConfiguration();
		
		Menu mainMenu;
		Menu boundaryMenu;
		Menu outputMenu;
		UserInput input;
};

#endif //_GAME_OF_LIFE_H_
