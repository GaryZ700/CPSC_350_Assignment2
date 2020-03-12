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
const string kRowSizePrompt = "\nPlease enter the number of rows the simulation should have: ";
const string kColSizePrompt = "\nPlease enter the number of columns the simulation should have: "; 
const string kSizeError = "\nPlease enter a valid integer";
const string kSizeValueTooSmall = "\nFor the size of the Game of Life simulation, the value must be larger than 0.\nPlease enter a new number: ";

//Constant strings for prompting for the population density for Game of Life Board Generation
const string kPopulationDensityPrompt = "\nPlease enter a value between 0 and 1: ";
const string kPopulationDensityError = "\nPlease enter a valid number between 0 and 1 for the initial population density: ";
const string kPopulationDensityTooLarge = "\nThe population density can not be larger than 1! Please enter a smaller number: ";
const string kPopulationDensityTooSmall = "\nThe population density can not be smaller than 0";

//Constants for opening a file to read in the initial bacteria population
const string kLoadFilePrompt = "\nPlease enter in the name of a file containing the intial population data: ";
const string kLoadFileNameError = "\nWarning! Bad File name! Please enter the correct file name: ";
const string kLoadFileBadSize = "\nBad File Data! Please ensure that the first two lines of your initial configuration file are valid integers representing the number of rows and columns for the simulation respectively.";
const string kLoadFileBadCol = "\nBad File Data! Please ensure that the number of columns in the provided data file matach the number specifed in the second line of the file!";
const string kLoadFileBadRow = "\nBad File Data! Please ensure that the number of row in the provided data file match the number specified in the first line of the file!";
const string kLoadFileBadChar = "\nBad File Data! Please ensure that the file consists only of '-', and 'X' as characters!";

//Constants Related Towards the Simulation Portion of the Game of Life
enum kOutputMode {STANDARD, PAUSE, FILEOUT};
const int kStabilityCycleMax = 20;
const int kPauseTime = 500;
const string kOutputFileName = "\nPlease enter a name for the output file.\nWarning!! If the file has other data, it will be overwritten with outupt from this program!\n";
const string kOutputFileError = "\nThere was an error opening the provided file name, please enter a new file name.\n";
const string kFileOutputGenerationsError = "\nPlease enter a valid integer greater than 0.";
const string kOutputFileWriteError = "\nWarning! Output file could not be written to!";
const string kFileOutputGenerations = "Please enter the maximum amount of generations that should be outputted to the output file.\nPlease note that if the system stabilizes before the maximum amount of generations have been reached then file output will cease.\n";
const string kSimulationStabilized = "\nThe simulation has stabilized into a repeating pattern. Press enter to quit.";
const string kGenerationMaxReached = "\nThe max amount of bacteria generations has been written to the output file. Press enter to quit.";
const string kGenerationDied = "\nThe simulation has ended due to all bacteria dying off. Press enter to quit.";

#endif //_GAME_OF_LIFE_CONSTANTS_H_
