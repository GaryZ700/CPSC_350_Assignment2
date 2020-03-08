/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

#ifndef _OS_METHODS_H_
#define _OS_METHODS_H_

#ifdef WIN32_
	#include <windows.h>
#else
	#include <unistd.h>
#endif

using namespace std;

class OSMethods{

	public:
		static void Sleep(int time);
};

#endif //_OS_METHODS_H_
