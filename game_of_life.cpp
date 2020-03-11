/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

#include "game_of_life.h"

using namespace std;

GameOfLife::GameOfLife(){

	//Set up the main menu
	mainMenu.AddText("Welcome to the Game of Life Simuation!\n\n");
	mainMenu.AddOption("1. Begin with a Random Configuration", "1");
	mainMenu.AddOption("2. Specify a File Configuration", "2");
	
	//Set up the boundary condition menu
	boundaryMenu.AddText("Please choose one of the following boundary conditions for the Game of Life. \n\n");
	boundaryMenu.AddOption("1. Classic Mode", "1");
	boundaryMenu.AddOption("2. Doughnut Mode", "2");
	boundaryMenu.AddOption("3. Mirror Mode", "3");

	//Set up the Output Mode for the Simulation
 	outputMenu.AddText("Please choose one of the following output options. \n\n");
	outputMenu.AddOption("1. Display Output", "1");
	outputMenu.AddOption("2. Display Output with a Pause", "2");
	outputMenu.AddOption("3. Send Output to a File", "3");	
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Game of Life Menu
void GameOfLife::MainMenu(){

	kOutputMode mode;
	Screen* initialConfiguration; 	
	void (*boundaryFunction)(Screen*&);

	mainMenu.Display();
	string answer = mainMenu.ParseOption();

	if(answer == "1")
		initialConfiguration = RandomConfiguration(); 				
	else
		initialConfiguration = LoadFile();

	boundaryMenu.Display();
	string boundary = boundaryMenu.ParseOption();			

	if(boundary == "1")
		boundaryFunction = GameOfLifeBoundaries::ClassicBoundary;
	else if(boundary == "2")
		boundaryFunction = GameOfLifeBoundaries::DoughnutBoundary;
	else
		boundaryFunction = GameOfLifeBoundaries::MirrorBoundary; 

	outputMenu.Display();
	string outputMode = outputMenu.ParseOption();
	
	if(outputMode == "1")
		mode = STANDARD;
	else if(outputMode == "2")
		mode = PAUSE;
	else
		mode = FILEOUT; 
	
	cout << "MODE: " << mode << endl;
	cout << "TEST MODE: " << STANDARD << endl;

	GameOfLifeSimulation simulation(initialConfiguration, boundaryFunction, mode);
	simulation.Simulate();	
}

//---------------------------------------------------------------------------------

Screen* GameOfLife::RandomConfiguration(){
	
 	Vector2D size(
		input.GetInt(
			kColSizePrompt, 
			kSizeError,
			1,
			numeric_limits<int>::max(),
			kSizeValueTooSmall
		),
		input.GetInt(
			kRowSizePrompt,
			kSizeError,
			1,
			numeric_limits<int>::max(),
			kSizeValueTooSmall
		)
	);

	double populationDensity = input.GetDouble(kPopulationDensityPrompt, kPopulationDensityError, numeric_limits<double>::min(), 1, kPopulationDensityTooSmall, kPopulationDensityTooLarge);	
	
	int insertionAmount;
	int counter = 0;
	int gridSize = size.x * size.y;
	double bacteriaAmount = gridSize * populationDensity;
	string bg;
	string insertionChar;
	string data = "";	

	//decide whether to randomly add in bacteria or randomly add in empty spaces 
	//add in empty spaces
	if(populationDensity >= 0.5){
		insertionAmount = round( gridSize - bacteriaAmount );
		bg = "X";
		insertionChar = "-";
	}
	
	//add in bacteria
	else{
		insertionAmount = bacteriaAmount; 
		bg = "-";
		insertionChar = "X";
	}
	
	cout << "Inerstion Amount " << insertionAmount << endl;
	cout << "bg " << bg << endl;
	cout << "insertion char " << insertionChar << endl;

	//add the number of newlines characters that will be added into the data 
	//string to the grid size
	gridSize += size.y - 1;

	while(insertionAmount > 0){
	
		++counter;

		//check whether or not the string grid has been constructed
		//if it has alreadly been randomly constructed once, then for the next turn
		//change the algorithem to avoid an endless loop
		if(data.size() < gridSize){

			//if end of a row has beeen reached, 
			//then add a "\n" to signify this
			if( counter % int(size.x + 1) == 0){
				data += "\n";
				++counter;
			}

		        if(double(rand()) / RAND_MAX > double(rand()) / RAND_MAX){
				data += insertionChar;
				insertionAmount--;
			}
			else
				data += bg;
		//	cout << "internal data " << data << endl;	
		}
		else if(data[counter % gridSize] == bg[0]){
			data.replace(counter % gridSize, 1, insertionChar);
			--insertionAmount;
		//	cout << "else if " << data << endl;
		//	cout << "insertion amt " << insertionAmount << endl;
		}
	}	

	cout << data << endl;

	cout << "DATA COMPUTED" << endl;

	return new Screen(size, data, bg[0]);
}

//---------------------------------------------------------------------------------

Screen* GameOfLife::LoadFile(){
	
	fstream file; 

	//parse file data to ensure that it is accurately formatted
	int lineNumber;
	int  size[2];
	string line;
	string data = "";

	//while loop to ensure that inputted file is correctly formatted
	do{	
		restart:;

		lineNumber = 0;
		file = input.GetFile(kLoadFilePrompt, kLoadFileNameError, ios::in);

		//get size of simulation from the first two lines of the file
		//will be [rows, cols]
		for(int i=0; i<2; ++i){

			getline(file, line);
			
			++lineNumber;			
	
			//try catach to ensure that the first line can be converted to a valid integer
			try{
				size[i] = stoi(line);
			}
			catch(exception e){
				cout << kLoadFileBadSize << endl;
				cout << "The error is on line " << lineNumber << ", '" << line << "'" << endl << endl;
				goto restart;
			}
		}	
				
		while(getline(file, line)){
			++lineNumber;
			
			int lineSize = line.size();
			for(int i=0; i<lineSize; ++i){
				if(line[i] == 'X' || line[i] == '-')
					data += line[i];
				else{	
					cout << kLoadFileBadChar << endl;
					cout << "The Error is on line " << lineNumber << ", '" << line  << "'" << endl << endl;
					goto restart;
				}	
			}

			if(lineSize != size[1]){
				cout << kLoadFileBadCol << endl;
				cout << "The Error is on line " << lineNumber << ", '" << line  << "'" << endl << endl;
				goto restart;
			}

			data += "\n";		
		}

		cout << lineNumber << endl << endl;

		if(lineNumber != size[0] + 2){
			cout << kLoadFileBadRow << endl;
			cout << "The Error is on line " << lineNumber << ", '" << line  << "'" << endl << endl;
			goto restart;
		}

	cout << "FALSE" << endl;
	}while(false);

	cout << endl << "Start of File Data " << data << endl;
	cout << "End of File Data" << endl << endl;

	file.close();

	return new Screen(Vector2D(size[1], size[0]), data);	
}
