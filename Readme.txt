Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life

2. List of Source Files
	1.  Makefile
	2.  game_of_life_constants.h
	3.  game_of_life.h
	4.  game_of_life_boundaries.h 
	5.  game_of_life_simulation.h
	6.  menu.h
	7.  os_methods.h
	8.  screen.h
	9.  user_input.h
	10. vector2d.h
	11. game_of_life.cpp
	12. game_of_life_boundaries.cpp
	13. game_of_life_simulation.cpp
	14. menu.cpp
	15. os_methods.cpp
	16. screen.cpp
	17. user_input.cpp
	18. vector2d.cpp 

3. Description of any known compile/runtime errors:
	Software will mistakenly not be able to identify stable Game of Life patterns if they require 50 or more cycles before the cycle repeats. 
	Testing was completed to the best abillities and knowledge of the programmer, but run-time errors may exist in certain input situations that were not tested. 
	During file reading/writing, hardware failure or other multiple software reading/writing to the same file may cause program to crash.	
	Running software for very large simulations, of total computation of over 6,000,000 bacteria will cause the simulation to be "killed". The amount of bacteria computed can be determined by getting the area of the bacteria screen, and then multiplying the area by the number of generations that are created. 

4. References used to complete the assignment:
	Class Lectures/Textbook
	Math 250 Notes
	Google C++ Stylesheet
	https://stackoverflow/questions/23369503/get-size-of-terminal-window-rows-columns
	https://stackoverflow.com/questions/2448242/struct-with-template-variables-in-c
	https://www.ibm.com/support/knowledgecenter/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/cplr326.htm
	https://stackoverflow.com/questions/1691007/whats-the-right-way-to-overload-operator-for-a-class-hierarchy
	https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
	https://stackoverflow.com/questions/11647186/define-a-const-static-object-variable-inside-the-class
	https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive/
	https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new/
	https://stackoverflow.com/questions/1153548/minimum-double-value-in-c-c
	https://en.cppreference.com/w/cpp/types/numeric_limits/min
	www.cplusplus.com/forum/beginner/24372
	https://geeksforgeeks.org/rand-and-srand-in-ccpp/
	https://www.geeksforgeeks.org/how-to-convert-a-single-character-to-string-in-cpp/ouble r1 = (rand() / RAND_MAX);
	https://www.tutorialspoint.com/cplusplus/cpp_return_pointer_from_functions.htm
	www.cplusplus.com/reference/fstream/open/
	https://www.techiedelight.com/convert-string-to-int-cpp
	https://stackoverflow.com/questions/41179629/how-to-use-something-like-a-continue-statement-in-nested-for-loops
        https://geeksforgeeks.org/namespace-in-c/	
	https://www.eskimo.com/~scs/cclass/int/sc10a.html
	https://en.cppreference.com/w/cpp/language/typedef
	www.cplusplus.com/reference/vector/vector/
 	https://stackoverflow.com/questions/5033232/c-class-copy-pointer-copy
	https://www.geeksforgeeks.org/are-array-members-deeply-copied/ 
	https://en.wikipedia.org/wiki/Pairing_function
	https://www.conwaylife.com/wiki/Main-Page
	https://www.geeksforgeeks.org/increment-and-decrement-operator-overloading-in-c/
	https://quora.com/How-do-you-pause-the-system-for-a-while-in-C++	
	https://stackoverflow.com/questions/21257544/c-wait-for-user-input
	www.cplusplus.com/reference/string/string/find/

5. Instructions for running the assignment
	1.) Run "make"
	2.) Run "./assignment2.exe"
