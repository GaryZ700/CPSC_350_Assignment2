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

	this->history = new vector<string>();
	this->history->clear();

	if(output == FILEOUT){

		string fileName;
		cout << kOutputFileName << endl;
		getline(cin, fileName);
		
		this->outputFile.open(fileName, ios::out);	
		
		cout << kFileOutputGenerations << endl;
		cin >> fileGeneration;
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GameOfLifeSimulation::~GameOfLifeSimulation(){

	delete history;
	delete bacteriaScreen;	
	
	if(output == FILEOUT)
		this->outputFile.close();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GameOfLifeSimulation::Simulate(){
	
	while(!IsStable()){
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
	string outputString = "";
	outputString += "Generation: " + to_string(generation) + "\n\n";
	outputString +=  bacteriaScreen->ToString() + "\n\n";

	switch(output){
		case STANDARD:
			cout << outputString;
			OSMethods::Sleep(kPauseTime);
			break;
		case PAUSE:
			cout << outputString << endl;
			input.Pause();		
			break;
		case FILEOUT:
			if(outputFile.is_open()){
		        	outputFile << outputString;
				cout << "Wrote to File" << endl;
			}	
			else
				cout << "Warning File is not open" << endl;
			break;	
	}
}

//---------------------------------------------------------------------------------

bool GameOfLifeSimulation::IsStable(){
	
	history->push_back(bacteriaScreen->ToString());		
	int size = history->size() - 1;
	
	//check if all cells have died
	//and if the file output mode is selected, that the max amount of outputted generations has 
	//not been crossed
	if(history->at(size).find('X') == string::npos ||
	   (output == FILEOUT && generation > fileGeneration)
	)
		return true;

	//check whether the current history shows any stabilizationd
	//check if the current history has data that is a multiple of two
	if(size%2 == 0){

		//check all current possible patterns that are possible to discern from the given data
		for(int i=0; i<size/2; ++i){	
			for(int j=1; j<=i; ++j){
				
				//get the pattern of size i
				for(int k=0; k<=j; ++k){
					if(history->at(size - k) != history->at( size - i - k )){
						goto nextPattern;
					}
				}
				
				return true;	

				nextPattern:;
			}	
		}

		//if the history is full then clear it
		if(history->size() == 2*kStabilityCycleMax)	
			history->clear();
	}

	return false;
}
