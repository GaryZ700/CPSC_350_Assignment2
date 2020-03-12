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
	outputMenu.AddOption("1. Display Output with a Pause", "1");
	outputMenu.AddOption("2. Display Output, but Press Enter to Continue", "2");
	outputMenu.AddOption("3. Send Output to a File", "3");	
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Game of Life Configuration Menu
void GameOfLife::MainMenu(){

	kOutputMode mode;
	Screen* initialConfiguration; 	
	void (*boundaryFunction)(Screen*&);

	//Display the Main Menu and Parse the Input
	mainMenu.Display();
	string answer = mainMenu.ParseOption();

	if(answer == "1")
		initialConfiguration = RandomConfiguration(); 				
	else
		initialConfiguration = LoadFile();

	//Display the Boundary Menu and Parse the Input
	boundaryMenu.Display();
	string boundary = boundaryMenu.ParseOption();			

	if(boundary == "1")
		boundaryFunction = GameOfLifeBoundaries::ClassicBoundary;
	else if(boundary == "2")
		boundaryFunction = GameOfLifeBoundaries::DoughnutBoundary;
	else
		boundaryFunction = GameOfLifeBoundaries::MirrorBoundary; 

	//Display the Output Menu and Parse the Input
	outputMenu.Display();
	string outputMode = outputMenu.ParseOption();
	
	if(outputMode == "1")
		mode = STANDARD;
	else if(outputMode == "2")
		mode = PAUSE;
	else
		mode = FILEOUT; 

	//Set up the Simulation, and then run it
	GameOfLifeSimulation simulation(initialConfiguration, boundaryFunction, mode);
	simulation.Simulate();	
}

//---------------------------------------------------------------------------------

//Function to Build a Random Configuration for the Game of Life
Screen* GameOfLife::RandomConfiguration(){

	//Prompt the User for the Size of the Game of Life Simulation	
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

	//Prompt for the Populatoin Density
	double populationDensity = input.GetDouble(kPopulationDensityPrompt, kPopulationDensityError, numeric_limits<double>::min(), 1, kPopulationDensityTooSmall, kPopulationDensityTooLarge);	
	
	int insertionAmount;
	double bacteriaAmount = size.x * size.y * populationDensity;
	string bg;
	string insertionChar;
	string data = "";	

	//decide whether to randomly add in bacteria or randomly add in empty spaces
	//and calculate the amount of either spaces or bacteria to add in 
	//add in empty spaces
	if(populationDensity >= 0.5){
		insertionAmount = round( (size.x*size.y) - bacteriaAmount );
		bg = "X";
		insertionChar = '-';
	}
	
	//add in bacteria
	else{
		insertionAmount = bacteriaAmount; 
		bg = "-";
		insertionChar = 'X';
	}

	BuildRandomConfiguration(insertionAmount, data, bg, insertionChar, size);
	
	return new Screen(size, data, bg[0]);
}

//---------------------------------------------------------------------------------

//insertionAmount, integer representing the amount of insertion chars to add randomly into the data string
//data: reference to the data string where data parsed from the file is to be placed into
//bg: constant string reference that refers to the background character, is a string due to the use of the string.replace() method
//insertionChar: constant reference to a string that refers to the character that is to be inserted into random locations in the data string
	//insertionChar is a string and not char due to te use of string.replace() method
//size: constant reference to a Vector2D that refers to the size of the bacteria screen
void GameOfLife::BuildRandomConfiguration(int insertionAmount, string &data,  const string &bg, const string &insertionChar, const Vector2D &size){

	int counter = 0;
	int gridSize = size.x * size.y;
	
	//take into account the number of newline characters that will be 
	//added into the string representation of the screen
	gridSize += size.y - 1;

	while(insertionAmount > 0){
	
		++counter;

		//check whether or not the string grid has been constructed
		//if it has alreadly been randomly constructed once, but 
		//the random placement algorithem failed to place the 
		//correct amounts of insertionCharacters to acheive the desired bacteria density
		//then place insertionCharacters at any availble location in the bacteria grid
		if(data.size() < gridSize){

			//if end of a row has beeen reached, 
			//then add a "\n" to signify this
			if( counter % int(size.x + 1) == 0){
				data += "\n";
				++counter;
			}

			//Randomly decide whether to add in an insertion character
			//or a background character
		        if(double(rand()) / RAND_MAX > double(rand()) / RAND_MAX){
				data += insertionChar;
				insertionAmount--;
			}
			else
				data += bg;
		}
		else if(data[counter % gridSize] == bg[0]){
			data.replace(counter % gridSize, 1, string(insertionChar));
			--insertionAmount;
		}
	}	
}

//---------------------------------------------------------------------------------

Screen* GameOfLife::LoadFile(){
	
	//parse file data to ensure that it is accurately formatted
	int  size[2];
	string data = "";

	ParseFileData(size, data);

	return new Screen(Vector2D(size[1], size[0]), data);	
}

//---------------------------------------------------------------------------------

//size: reference to an integer array of size 2, where the values are formatted as follows [rows, cols]
//data: reference to a string where all of the parsed data from the file is to be stored
void GameOfLife::ParseFileData(int size[2], string &data){

	int lineNumber;
	string line;
	fstream file;
	
	//restart point at which the code will return to if there is an error in the file format
	restart:;
	
	lineNumber = 0;

	file = input.GetFile(kLoadFilePrompt, kLoadFileNameError, ios::in);

	//get size of simulation from the first two lines of the file
	//will be [rows, cols]
	//and ensure that rows and column number portion of the file is correctly formatted
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
	
	//parse actual bactera configuration from the file 		
	while(getline(file, line)){
		
		++lineNumber;
		int lineSize = line.size();

		//check to ensure that there are the correct 
		//number of columns in the file as specified 	
		if(lineSize != size[1]){
			cout << kLoadFileBadCol << endl;
			goto restart;
		}

		//for loop used to parse the lines of the input file line by line 
		//to ensure that all the characters are correctly formatted
		for(int i=0; i<lineSize; ++i){
			if(line[i] == 'X' || line[i] == '-')
				data += line[i];
			else{	
				cout << kLoadFileBadChar << endl;
				cout << "The Error is on line " << lineNumber << ", '" << line  << "'" << endl << endl;
				goto restart;
			}	
		}

		data += "\n";		
	}

	//check to ensure that there are the correct
	//number of rows in the file as specified
	if(lineNumber != size[0] + 2){
		cout << kLoadFileBadRow << endl;
		goto restart;
	}

	file.close();
}
