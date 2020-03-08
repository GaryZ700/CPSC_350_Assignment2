/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

#include "game_of_life_boundaries.h"

using namespace std;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//DoughnutBoundary Function to set up the Classic Boundary Logic
//screen: pointer to the starting bacteria generation
void GameOfLifeBoundaries::ClassicBoundary(Screen *screen){
	BuildNextGeneration(screen, ClassicBoundaryLogic);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//DoughnutBoundary Function to set up the Mirror Boundary Logic
//screen: pointer to the starting bacteria generation
void GameOfLifeBoundaries::MirrorBoundary(Screen *screen){
	BuildNextGeneration(screen, MirrorBoundaryLogic);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//DoughnutBoundary Function to set up the Doughnut Boundary Logic
//screen: pointer to the starting bacteria generation
void GameOfLifeBoundaries::DoughnutBoundary(Screen *screen){
	BuildNextGeneration(screen, DoughnutBoundaryLogic);
}

//---------------------------------------------------------------------------------

//Inner Logic to be used for the inner squares of the bacteria screen
//screen: pointer to starting generation screen
//newScreen: pointer to new generation screen
//position: position in the screen where an update to the generation is to be made
void GameOfLifeBoundaries::InnerLogic(Screen *screen, Screen *newScreen, const Vector2D &position){
	
}

//---------------------------------------------------------------------------------

//Doughnut Boundary Logic, Classic Boundary Logic to be used for the Game of Life
//screen: pointer to starting generation screen
//newScreen: pointer to new generation screen
//position: position in the screen where an update to the generation is to be made
void GameOfLifeBoundaries::ClassicBoundaryLogic(Screen *screen, Screen *newScreen, const Vector2D &position){
	
}

//---------------------------------------------------------------------------------

//Mirror Boundary Logic, mirror at the edges of the bacteria screen
//screen: pointer to starting generation screen
//newScreen: pointer to new generation screen
//position: position in the screen where an update to the generation is to be made
void GameOfLifeBoundaries::MirrorBoundaryLogic(Screen *screen, Screen *newScreen, const Vector2D &position){
	
}

//---------------------------------------------------------------------------------

//Doughnut Boundary Logic, bacteria screen turns on into itself
//screen: pointer to starting generation screen
//newScreen: pointer to new generation screen
//position: position in the screen where an update to the generation is to be made
void GameOfLifeBoundaries::DoughnutBoundaryLogic(Screen *screen, Screen *newScreen, const Vector2D &position){
	
}

//---------------------------------------------------------------------------------

//Builds the Next Generation of Bacteria based upon the Boundary Logic
//screen: pointer to a Screen object containing the starting bacteria generation
//boundaryLogic: pointer to a function that will take the starting bacteria genration screen pointer, the next bacteria genration screen pointer and a Vector2D constant reference of the bacteria to update
void GameOfLifeBoundaries::BuildNextGeneration(Screen *screen, void (*boundaryLogic)(Screen*, Screen*, const Vector2D&)){

	int area = screen->GetSize().x * screen->GetSize().y;
	Vector2D position;
	Screen *newScreen = new Screen(screen->GetSize());
	
	for(int location=0; location<area; ++location){

		//check whether or not boundary or inner logic should be used
		if(position.x == 0 || position.y == 0)
			boundaryLogic(screen, newScreen, position);
		else
			InnerLogic(screen, newScreen, position);
		
		++position;	
	}
}
