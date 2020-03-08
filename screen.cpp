/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

#include "screen.h"

using namespace std;

//Default Constructor
Screen::Screen(){
	Constructor(Vector2D(2, 2), "", '-');
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Overloaded Constructor
//col: integer number of columns the screen should have
//row: integer number of rows the screen should have
//data: string that represents the data to be placed onto the screen
//bg: char character that represents what should be on the background of the screen where no data is placed
Screen::Screen(int col, int row, string data, char bg){
	Constructor(Vector2D(col, row), data, bg);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Overloaded Constructor
//size: Vector2D that represents the size of the screen in columns and rows
//data: string of data that is to be placed onto the screen
//bg: char character that should be used for the background of the screen where there is no data
Screen::Screen(Vector2D size, string data, char bg){
	Constructor(size, data, bg);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Copy Constructor
//screen: Screen whose data is to be copied into this new screen 
Screen::Screen(Screen &screen){
	Constructor(Vector2D(screen.GetSize()), screen.ToString(), '-');
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Deconstructor
Screen::~Screen(){
	for(int x=0; x<size.x; ++x){
		delete[] screenArray[x];
	}

	delete[] screenArray;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Update Function
//data: string of data to update the screen with
//\n are taken to mean to move to the next row in the screen
//if the string is either too large or too small to fit onto the screen, 
//	then empty spaces are filled with the bg character
//	while extra characters are replaced with 
void Screen::Update(string data){	
	
	Vector2D dataPosition;
	char pixel;
	char dataChar;
	cout << "data: " << endl << data << endl;
	cout << data.size() << endl;
	cout << endl << "Building Screen" << endl;
//	cout << "starting vector: " << dataPosition.ToString() << endl;
	//loop over all positions within the screen and replace with either data from the data string
	//or with the bg char	
	for(int y=0; y<size.y; ++y){
		for(int x=0; x<size.x; ++x){
	
			//assume that the begining pixel will the background char
			pixel = bg;

			//do not to try to access data from the string that does not exist
			if(data.size() > dataPosition.x){
		
				dataChar = data[dataPosition.x];
//		 		cout << "dataChar :" << dataChar << endl;				

				//if the newline character is found
				//then move the dataposition up a line in the display 
				//and to the right to move past the \n
				if(dataChar == '\n'){
					dataPosition = dataPosition + Vector2D::kRight + Vector2D::kUp;
					dataChar = data[dataPosition.x];	
				}

				if(y==int(dataPosition.y)){
					pixel = dataChar;
					dataPosition.x++;
//					cout << "put pixel" << dataPosition.x << endl;
				}
			}

			screenArray[x][y] = pixel;
			cout << pixel;		
//			cout << (dataPosition).ToString() << y << endl;	
		}
		cout << endl;
		//cout << "Y: " << y << ", Ydata: " << dataPosition.y << endl;
	}
	cout << "Screen Construction Completed" << endl;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//GetPixel Function
//x, int x position of the pixel to get
//y, int y position of the pixel to get
char Screen::GetPixel(int x, int y){
	return GetPixel(Vector2D(x, y));
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//GetPixel Function, Overloaded to take a vector
//vector: Vector2D that represents a point on the screen to get
char Screen::GetPixel(const Vector2D &vector){
	if( vector >= Vector2D::kZero && vector <= size)
		return screenArray[int(vector.x)][int(vector.y)];
	else {
		cout << "Warning!! Accessing Pixel that does not exist!" << endl;
		return ' ';	
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Returns a string version of the Screen Matrix
string Screen::ToString(){

	string output = "";
	
	for(int y=0; y<size.y; ++y){
		for(int x=0; x<size.x; ++x){
			output += screenArray[x][y];
		}
		output += "\n";
	} 
	
	return output;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Returns the size vector of this screen object 
Vector2D Screen::GetSize(){ return size; }

//---------------------------------------------------------------------------------

//In order to avoid duplicating constructor code, the main execution code for the constructor will be written
//in this function and referenced from the other constructors
void Screen::Constructor(Vector2D size, string data, char bg){

	this->size=size;
	this->bg = bg;		

	screenArray = new char*[int(size.x)];

	for(int x=0; x<size.x; ++x){
		screenArray[x] = new char[int(size.y)];
	}

	Update(data);
}
