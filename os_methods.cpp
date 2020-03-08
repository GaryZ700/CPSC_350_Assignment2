/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

#include "os_methods.h"

//Sleep function takes a time integer to sleep in milliseconds
#ifdef WIN32_
	void OSMethods::Sleep(int time){
		Sleep(time);
	}	
#else
	void OSMethods::Sleep(int time){
		//1000 Second difference between usleep and sleep
		//sleep in milliseconds while usleep in microseconds
		usleep(time * 1000);
	}
#endif
