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

//Inner Logic to be used for the non-border computations of the bacteria screen
//screen: pointer to starting generation screen
//newScreen: pointer to new generation screen
//position: position in the screen where an update to the generation is to be made
//getOffSetPosition: pointer to a function that takes the initial screen, the current position vector and 
	//the offset vector to generate the final offset position, this is used to create different
	//boundary conditions
void GameOfLifeBoundaries::InnerLogic(Screen *screen, Screen *newScreen, const Vector2D &position, Vector2D* (*getOffSetPosition)(const Vector2D&, const Vector2D&, const Vector2D&)){

	int neighbors = 0;	
	Vector2D size = screen->GetSize();

	//loop from -1 to 1 in order to create vector combinations 
	//that offset the position of the current position to all 
	//position surronding the current position
	for(int y=-1; y<2; ++y){
		for(int x=-1; x<2; ++x){

			//skip iteration if position is not being offset 
			if(x == 0 && y == 0)
				continue;				
		
			Vector2D *offSetPosition = getOffSetPosition(size, position, Vector2D(x, y));
		
			if(screen->GetPixel(offSetPosition) == 'X')	
				++neighbors;
		
			delete offSetPosition;
		}
	}

	//logic used to determine if a cell will live or die in the current position
	CoreLogic(screen, newScreen, position, neighbors);
}

//---------------------------------------------------------------------------------

//Classic Boundary Logic to be used for the Game of Life
//screen: pointer to starting generation screen
//newScreen: pointer to new generation screen
//position: position in the screen where an update to the generation is to be made
void GameOfLifeBoundaries::ClassicBoundaryLogic(Screen *screen, Screen *newScreen, const Vector2D &position){
	
	//Central Idea of this algorithem is that for each position
	//in the boundary, all possible vector offsets to check a valid 
	//position where a neighbor exists are generated, and then
	//linearly combined in order to check Class Game of Life
	//border cells

	int neighbors = 0;
	int offSetIndex = 0;
	vector<Vector2D> offSets;

	offSets.push_back(Vector2D::kZero);

	//add in the appropriate vectors to check all of the surrounding neighbors
	//logic works by checking what offsets are possible given what the vector value is NOT
	//for example, if x!=0, then there are spaces to check to the left of the current position, 
	//meaning that a left vector can be added to the list of offsets to check
	if(position.x != 0)
		offSets.push_back(Vector2D::kLeft);

	if(position.x != screen->GetSize().x-1)
		offSets.push_back(Vector2D::kRight);

	if(position.y != 0)
		offSets.push_back(Vector2D::kDown);

	if(position.y != screen->GetSize().y-1)
		offSets.push_back(Vector2D::kUp);
	
	for(int i=0; i<offSets.size(); ++i){
		for(int j=0; j<offSets.size(); ++j){
			
			Vector2D offSet(offSets.at(i) + offSets.at(j));

			if(offSet == Vector2D::kZero || abs(offSet.x) == 2 || abs(offSet.y) == 2)
				continue;

			if(screen->GetPixel(position + offSet) == 'X')	
				neighbors += 1;			
		}
	}
	
	//divide neighbors by two since for loop overcounts each neighbor twice
	CoreLogic(screen, newScreen, position, neighbors/2);
}

//---------------------------------------------------------------------------------

//Mirror Boundary Logic, mirror at the edges of the bacteria screen
//screen: pointer to starting generation screen
//newScreen: pointer to new generation screen
//position: position in the screen where an update to the generation is to be made
void GameOfLifeBoundaries::MirrorBoundaryLogic(Screen *screen, Screen *newScreen, const Vector2D &position){
	InnerLogic(screen, newScreen, position, MirrorOffSetPosition);		
}

//---------------------------------------------------------------------------------

//Doughnut Boundary Logic, bacteria screen turns on into itself
//screen: pointer to starting generation screen
//newScreen: pointer to new generation screen
//position: position in the screen where an update to the generation is to be made
void GameOfLifeBoundaries::DoughnutBoundaryLogic(Screen *screen, Screen *newScreen, const Vector2D &position){
	InnerLogic(screen, newScreen, position, DoughnutOffSetPosition);		
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
				InnerLogic(screen, newScreen, Vector2D(x, y), ClassicOffSetPosition);	
		}
	}

	//deletes the old screen reference and moves the new screen pointer to the original screen 
	delete screen;
	screen = newScreen;
}

//---------------------------------------------------------------------------------

//Core Logic for the Game of Life Simulation used to determine if bacteria live or die
//screen: Screen pointer where update is to be made based on the logic
//position: reference to Vector2D of position where the update is to be made
//neighbors: int that represents the number of neighbors the cell in question has
void GameOfLifeBoundaries::CoreLogic(Screen *screen, Screen *newScreen, const Vector2D &position, int neighbors){

	//core logic for game of life simulation
	if(neighbors <= 1 || neighbors > 3)
		newScreen->SetPixel('-', position);
	else if(neighbors == 3)
		newScreen->SetPixel('X', position);
	else
		newScreen->SetPixel(screen->GetPixel(position), position);
}

//---------------------------------------------------------------------------------

//ClassicOffSetPosition Function 
//screenSize: is a constant reference to a Vector 2D that represents the size of the current Bacteria Screen
//position: is a constant reference to a Vector 2D that represents the current position in the bacteria Screen
//offSet: is a constant reference to a Vector 2D that represents the offset from the current position in the bacteria screen
Vector2D* GameOfLifeBoundaries::ClassicOffSetPosition(const Vector2D &screenSize, const Vector2D &position, const Vector2D &offSet){
	return new Vector2D(position + offSet);
}

//---------------------------------------------------------------------------------

//Computes the OffSet Position for the Doughnut Mode
//screenSize: is a constant reference to a Vector 2D that represents the size of the current Bacteria Screen
//position: is a constant reference to a Vector 2D that represents the current position in the bacteria Screen
//offSet: is a constant reference to a Vector 2D that represents the offset from the current position in the bacteria screen
Vector2D* GameOfLifeBoundaries::DoughnutOffSetPosition(const Vector2D &screenSize, const Vector2D &position, const Vector2D &offSet){
	
	Vector2D *offSetPosition = new Vector2D(position + offSet);

	//adjust the offSet to account for a leftwards doughnut movement by add in the approriate size componenet
	//adjust the offSet to account for a rightwards doughnut movement by using the modulo operator
	if(offSetPosition->x < 0)
		offSetPosition->x += screenSize.x;
	else
		offSetPosition->x = int(offSetPosition->x) % int(screenSize.x);
	
	if(offSetPosition->y < 0) 
		offSetPosition->y += screenSize.y;
	else	
		offSetPosition->y = int(offSetPosition->y) % int(screenSize.y);
		
	return offSetPosition;	
}

//---------------------------------------------------------------------------------

//Computes the OffSet Position for the Mirror Mode
//screenSize: is a constant reference to a Vector 2D that represents the size of the current Bacteria Screen
//position: is a constant reference to a Vector 2D that represents the current position in the bacteria Screen
//offSet: is a constant reference to a Vector 2D that represents the offset from the current position in the bacteria screen
Vector2D* GameOfLifeBoundaries::MirrorOffSetPosition(const Vector2D &screenSize, const Vector2D &position, const Vector2D &offSet){
	
	Vector2D offSetPosition(position + offSet); 
	
	//if position is along the y-axis, then shift the position by 
	//removing the x shift which would be invalid since it is outside 
	//the screen area, but by removing the x-shift, the cell that would
	//be reflected is checked instead of the reflection itsel
	if(offSetPosition.x < 0 || offSetPosition.x > screenSize.x - 1){
		offSetPosition.x -= offSet.x;
	}

	//Same argument as above if statment follows for this if, the only difference 
	//is that x-axis is inverted with the y-axis and vice versa
	if(offSetPosition.y < 0 || offSetPosition.y > screenSize.y - 1){
		offSetPosition.y -= offSet.y;	
	}

	//in the case where dealing with an offSet position that 
	//is not on the border, the original offSetPosition is returned
	//since no modifications due to mirror mode need to be amde
	return new Vector2D(offSetPosition);
}
