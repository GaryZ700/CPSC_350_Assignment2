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
void GameOfLifeBoundaries::ClassicBoundary(Screen *&screen){
	BuildNextGeneration(screen, ClassicBoundaryLogic);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//DoughnutBoundary Function to set up the Mirror Boundary Logic
//screen: pointer to the starting bacteria generation
void GameOfLifeBoundaries::MirrorBoundary(Screen *&screen){
	BuildNextGeneration(screen, MirrorBoundaryLogic);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//DoughnutBoundary Function to set up the Doughnut Boundary Logic
//screen: pointer to the starting bacteria generation
void GameOfLifeBoundaries::DoughnutBoundary(Screen *&screen){
	BuildNextGeneration(screen, DoughnutBoundaryLogic);
}

//---------------------------------------------------------------------------------

//Inner Logic to be used for the inner squares of the bacteria screen
//screen: pointer to starting generation screen
//newScreen: pointer to new generation screen
//position: position in the screen where an update to the generation is to be made
void GameOfLifeBoundaries::InnerLogic(Screen *screen, Screen *newScreen, const Vector2D &position){

	cout << "INNER LOGICLOGIC LOGIC" << endl;
	cout << screen->ToString() << endl;
	cout << position.ToString() << endl << endl;
	int neighbors = 0;
	
	for(int y=-1; y<2; ++y){
		for(int x=-1; x<2; ++x){

			Vector2D offset(x, y);
			
			if(offset == Vector2D::kZero)
				continue;
			cout << offset.ToString() << endl;
			
			if(screen->GetPixel(position + offset) == 'X')	
				++neighbors;
		}
	}

	//core logic for game of life simulation
	if(neighbors <= 1 || neighbors > 3)
		newScreen->SetPixel('-', position);
	else if(neighbors == 3)
		newScreen->SetPixel('X', position);
	cout << "NEIGHTBORS!!!!!!!!!!!!" << endl;
	cout << neighbors << endl;
	cout << "!!!!!!!!!!!!!!!" << endl;
}

//---------------------------------------------------------------------------------

//Doughnut Boundary Logic, Classic Boundary Logic to be used for the Game of Life
//screen: pointer to starting generation screen
//newScreen: pointer to new generation screen
//position: position in the screen where an update to the generation is to be made
void GameOfLifeBoundaries::ClassicBoundaryLogic(Screen *screen, Screen *newScreen, const Vector2D &position){
	cout << "CLASSSIC BOUNDARY" << endl;
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
void GameOfLifeBoundaries::BuildNextGeneration(Screen *&screen, void (*boundaryLogic)(Screen*, Screen*, const Vector2D&)){

	Vector2D size = screen->GetSize();
	Screen *newScreen = new Screen(size);
	
	for(int y=0; y<screen->GetSize().y; ++y){
		for(int x=0; x<screen->GetSize().x; ++x){

			//check whether or not boundary or inner logic should be used
			if(x == 0 || y == 0 || x == size.x-1 || y == size.y-1)
				boundaryLogic(screen, newScreen, Vector2D(x, y));
			else
				InnerLogic(screen, newScreen, Vector2D(x, y));	
		}
	}

	cout << "Built New Generation )))))))))))))))))))))))" << endl;
//	cout << newScreen->ToString() << endl << endl;
	delete screen;
	screen = newScreen;
}
