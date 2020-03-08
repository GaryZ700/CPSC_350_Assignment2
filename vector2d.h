/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

#ifndef _VECTOR_2D_H_
#define _VECTOR_2D_H_

#include <string>
#include <cmath>

using namespace std;

//2D Vector class that allows for storing data as a 2D coordinate point
//Note, although it is not usally recomended to make member variables public,
//in this case it is purposefully done in order to allow direct manipulation of 
//the x and y compnenents of the vector
class Vector2D{

	public:
		Vector2D();
		Vector2D(double x, double y);
		Vector2D(Vector2D *vector);		

		double Magnitude() const;
		string ToString() const; 
		Vector2D Normalized() const;		
		
		bool operator==(const Vector2D &lhs) const;
		bool operator>=(const Vector2D &lhs) const;
		bool operator<=(const Vector2D &lhs) const;
		bool operator>(const Vector2D &lhs) const;
		bool operator<(const Vector2D &lhs) const;
		Vector2D operator+(const Vector2D &lhs) const;
		Vector2D operator-(const Vector2D &lhs) const;
		Vector2D operator*(double lhs) const;
		Vector2D operator/(double lhs) const;
		Vector2D operator++();
	
		//Left is negative, right is positive
		//up is positive, down is negative
		static const Vector2D kLeft;
		static const Vector2D kRight; 
		static const Vector2D kUp; 
		static const Vector2D kDown;
		static const Vector2D kZero;	
		double x;
		double y;	
};

#endif //_VECTOR_2D_H_
