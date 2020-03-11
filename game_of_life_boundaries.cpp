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
//getOffSetPosition: pointer to a function that takes both the current position vector and the offset vector to generate the final offset position
void GameOfLifeBoundaries::InnerLogic(Screen *screen, Screen *newScreen, const Vector2D &position, Vector2D* (*getOffSetPosition)(const Vector2D&, const Vector2D&, const Vector2D&)){

	int neighbors = 0;	
	Vector2D size = screen->GetSize();

	for(int y=-1; y<2; ++y){
		for(int x=-1; x<2; ++x){

			if(x == 0 && y == 0)
				continue;				
			
			Vector2D *offSetPosition = getOffSetPosition(size, position, Vector2D(x, y));

			if(screen->GetPixel(offSetPosition) == 'X')	
				++neighbors;
			
			delete offSetPosition;
		}
	}

	CoreLogic(screen, newScreen, position, neighbors);
}

//---------------------------------------------------------------------------------

//Doughnut Boundary Logic, Classic Boundary Logic to be used for the Game of Life
//screen: pointer to starting generation screen
//newScreen: pointer to new generation screen
//position: position in the screen where an update to the generation is to be made
void GameOfLifeBoundaries::ClassicBoundaryLogic(Screen *screen, Screen *newScreen, const Vector2D &position){
	
	int neighbors = 0;
	int offSetIndex = 0;
	vector<Vector2D> offSets;

	offSets.push_back(Vector2D::kZero);

	//cout << "!!!!!!!!!!!!!" << endl;
	
	//add in the appropriate vectors to check all of the surrounding neighbors
	if(position.x != 0){
	//	cout << "Left" << endl; 
		offSets.push_back(Vector2D::kLeft);
	}
	if(position.x != screen->GetSize().x-1){
	//	cout << "Right" << endl;
		offSets.push_back(Vector2D::kRight);
	}
	if(position.y != 0){
	//	cout << "Down" << endl;
		offSets.push_back(Vector2D::kDown);
	}
	if(position.y != screen->GetSize().y-1){
	//	cout << "Up" << endl;
		offSets.push_back(Vector2D::kUp);
	}
	
	cout << position.ToString() << endl;

	for(int i=0; i<offSets.size(); ++i){
		for(int j=0; j<offSets.size(); ++j){
			
			Vector2D offSet(offSets.at(i) + offSets.at(j));

			if(offSet == Vector2D::kZero || abs(offSet.x) == 2 || abs(offSet.y) == 2)
				continue;
			if(position == Vector2D(3, 9)){	
				/*cout << "###########position with off set###########" << endl;	
				cout << (position + offSet).ToString() << endl;
				cout << screen->GetPixel(position + offSet) << endl;*/
			}

			if(screen->GetPixel(position + offSet) == 'X')	
				neighbors += 1;			
		}
	}
	
	/*cout << "!!!!!!!!!!!!!" << endl;
	cout << neighbors << endl;
	cout << neighbors / 2 << endl;
	cout << "TESTTESTTEST" << endl;*/

	//divide neighbors by two since for loop overcounts each neighbor twice
	CoreLogic(screen, newScreen, position, neighbors/2);
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

	delete screen;
	screen = newScreen;
}

//---------------------------------------------------------------------------------

//Core Logic for the Game of Life Simulation
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

	//adjust the offSet to account for a leftwards doughnut movement
	if(offSetPosition->x < 0)
		offSetPosition->x += screenSize.x;
	if(offSetPosition->y < 0) 
		offSetPosition->y += screenSize.y;
	
	//apply the modulus operator to ensure that doughnut wrapping occurs for the right side 
	offSetPosition->x = int(offSetPosition->x) % int(screenSize.x);
	offSetPosition->y = int(offSetPosition->y) % int(screenSize.y);
	
	return offSetPosition;	
}
