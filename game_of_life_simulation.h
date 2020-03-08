/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

#include <vector>
#include "screen.h"
#include "os_methods.h"
#include "game_of_life_constants.h"
#include "game_of_life_boundaries.h"

using namespace std;

//Game Of Life Simuation Class, is responsible for the actual execution of the game of life simulation
class GameOfLifeSimulation{
	
	public:
		GameOfLifeSimulation(Screen *configuration, void (*boundaryLogic)(Screen*), kOutputMode ouput);
		~GameOfLifeSimulation();

		void Simulate();
		
	private:
		void OutputData();		
		bool IsStable();
		int CantorPairingFunction(int x, int y);		
		
		int generation;	
		Screen *bacteriaScreen;
		void (*boundaryLogic)(Screen*);
		kOutputMode output;
				

		//is a an array containing two vectors
		//one vector is used to store a complete history
		//while the second vector is used to store aa possible pattern that is identified	
		vector<string> *history;
};
