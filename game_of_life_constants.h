/* Gary Zeri
   ID: 2321569 
   zeri@chapman.edu
   CPSC 350-02
   Assignment 1
*/

//Header file to contain all the constant values used within the Game of Life Program

#ifndef _GAME_OF_LIFE_CONSTANTS_H_
#define _GAME_OF_LIFE_CONSTANTS_H_

#include <string>

using namespace std;

//Constant strings for prompting for the size of the Game of Life Simulation
const string kRowSizePrompt = "Please enter the number of rows the simulation should have: ";
const string kColSizePrompt = "Please enter the number of columns the simulation should have: "; 
const string kSizeError = "Please enter a valid integer";
const string kSizeValueTooSmall = "For the size of the Game of Life simulation, the value must be larger than 0.\nPlease enter a new number: ";

//Constant strings for prompting for the population density for Game of Life Board Generation
const string kPopulationDensityPrompt = "Please enter a value between 0 and 1: ";
const string kPopulationDensityError = "Please enter a valid number between 0 and 1 for the initial population density: ";
const string kPopulationDensityTooLarge = "The population density can not be larger than 1! Please enter a smaller number: ";
const string kPopulationDensityTooSmall = "The population density can not be smaller than 0";

//Constants for opening a file to read in the initial bacteria population
const string kLoadFilePrompt = "Please enter in the name of a file containing the intial population data: ";
const string kLoadFileNameError = "Warning! Bad File name! Please enter the correct file name: ";
const string kLoadFileBadSize = "Bad File Data! Please ensure that the first two lines of your initial configuration file are valid integers representing the number of rows and columns for the simulation respectively.";
const string kLoadFileBadCol = "Bad File Data! Please ensure that the number of columns in the provided data file matach the number specifed in the second line of the file!";
const string kLoadFileBadRow = "Bad File Data! Please ensure that the number of row in the provided data file match the number specified in the first line of the file!";
const string kLoadFileBadChar = "Bad File Data! Please ensure that the file consists only of '-', and 'X' as characters!";

//Constants Related Towards the Simulation Portion of the Game of Life
enum kOutputMode {STANDARD, PAUSE, FILEOUT};
const int kStabilityCycleMax = 20;
const int kPauseTime = 500;
const string kOutputFileName = "Please enter a name for the output file.\nWarning!! If the file has other data, it will be overwritten with outupt from this program!";
const string kFileOutputGenerations = "Please enter the maximum amount of generations that should be outputted to the output file.\nPlease note that if the system stabilizes before the maximum amount of generations have been reached then file output will cease.";

#endif //_GAME_OF_LIFE_CONSTANTS_H_
