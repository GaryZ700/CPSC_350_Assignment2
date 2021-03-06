/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

#include "game_of_life_simulation.h"

using namespace std;

//Constructor for the Simulation Class
//configuration: pointer to the initial configuration for the Game of Life Simulation
//boundaryLogic: pointer to a function that takes in the initial configuration screen to be able to compute the boundary logic for the screen
//output: OutputMode enum used to determine how the simulation should output the data 
GameOfLifeSimulation::GameOfLifeSimulation(Screen *configuration, void (*boundaryLogic)(Screen*&), kOutputMode output){	
	this->generation = 0;

	this->bacteriaScreen = configuration;
	this->boundaryLogic = boundaryLogic;
	this->output = output;

	this->history = new vector<string>();
	this->history->clear();

	//Open the Output File
	if(output == FILEOUT){
		this->outputFile = this->input.GetFile(kOutputFileName, kOutputFileError, ios::out);  
		this->fileGenerationMax = input.GetInt(kFileOutputGenerations, kFileOutputGenerationsError, 1); 
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
	}
}

//---------------------------------------------------------------------------------

//Function to Output Data to the correct output form
void GameOfLifeSimulation::OutputData(){

	//Prepare Bacteria Generation Data to print out to the screen
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
			if(outputFile.is_open())
		        	outputFile << outputString;	
			else
				cout << kOutputFileWriteError << endl;
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
	if(history->at(size).find('X') == string::npos){
		OutputData();
		input.Pause(kGenerationDied);
		return true;
	}
	if(output == FILEOUT && generation > fileGenerationMax){
		OutputData();
		input.Pause(kGenerationMaxReached);
		return true;
	}

	//check whether the current history shows any stabilizationd
	//check if the current history has data that is a multiple of two, to ensure 
	//there is enough data 
	if(size%2 == 0){

		//check all current possible patterns that are possible to discern from the given data
		for(int i=0; i<size/2; ++i){	
			for(int j=1; j<=i; ++j){
				
				//get the pattern of size i
				for(int k=0; k<=j; ++k){
					if(history->at(size - k) != history->at( size - i - k ))
						goto nextPattern;
					
				}
				
				OutputData();	
				input.Pause(kSimulationStabilized);
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
