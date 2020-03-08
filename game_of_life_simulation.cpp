/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

#include "game_of_life_simulation.h"

using namespace std;

GameOfLifeSimulation::GameOfLifeSimulation(Screen *configuration, void (*boundaryLogic)(Screen*&), kOutputMode output){

	this->generation = 0;

	this->bacteriaScreen = configuration;
	this->boundaryLogic = boundaryLogic;
	this->output = output;

	this->history = new vector<string>(kStabilityCycleMax * 2);
	this->history->clear();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GameOfLifeSimulation::~GameOfLifeSimulation(){
	delete history;
	delete bacteriaScreen;	
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameOfLifeSimulation::Simulate(){
	
	while(!IsStable()){
		cout << "Is Not Stable " << endl;	
		OutputData();
		boundaryLogic(bacteriaScreen);	
		++generation;		
		cout << bacteriaScreen->ToString() << endl;			
	}
}

//---------------------------------------------------------------------------------

//Function to Output Data to the correct output form
void GameOfLifeSimulation::OutputData(){

	//print out the current generation to the screen
	cout << "Building Output String" << endl;
	string outputString = "";
	outputString += "Generation: " + to_string(generation) + "\n\n";
	outputString +=  bacteriaScreen->ToString() + "\n\n";
	cout << "Output String Construction Completed" << endl;

	switch(output){
		case STANDARD:
			cout << "Standard Output" << endl;
			cout << outputString;
			OSMethods::Sleep(kPauseTime);
			break;
		case PAUSE:
			break;
		case FILEOUT:
			break;
	}
	cout << "Switch Complete" << endl;
}

//---------------------------------------------------------------------------------

bool GameOfLifeSimulation::IsStable(){
	
	cout << endl << endl << "Is Stable Function Being Called" << endl;

	history->push_back(bacteriaScreen->ToString());		
	
	//check whether the current history shows any stabilization
	if(history->size() == 2*kStabilityCycleMax){
		int i = 0;
		while(i<history->size()){
			
			//get the pattern of size i
			for(int j=0; j<=i; ++j){
				cout << "History Values: " << j << " = " << history->at(j) << endl;
				if(history->at(j) != history->at( (j*2) + 1 + j )){
					cout << "If Worked" << endl;
					goto nextPattern;
				}
			}
			
			cout << "Return True" << endl;
			return true;	

			nextPattern:
				++i;
		}
		
		cout << "History Cleared" << endl; 
		history->clear();
	}

	cout << "False Return " << endl << endl;
	return false;
}

//---------------------------------------------------------------------------------

//Cantor Pairing Function is used to take a pair of natural numbers, x and y
//and compress the data of the two values into a single natural number
//is a bijection between the set of all pairs of natural numbers and the set of all natural numbers
int GameOfLifeSimulation::CantorPairingFunction(int x, int y){
	
	cout << "Cantor Pairing Function  " << x << "  " << y << endl;  
	return (0.5 * (x + y) * (x + y + 1)) + y;   
}
