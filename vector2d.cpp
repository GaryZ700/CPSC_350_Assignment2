/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 2: Game of Life
*/

#include "vector2d.h"

Vector2D::Vector2D(){
	this->x = 0;
	this->y = 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Vector2D::Vector2D(double x, double y){
	this->x = x;
	this->y = y;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Copy Constructor 
//vector: Vector2D to be deep copied into this object
Vector2D::Vector2D(Vector2D *vector){
	this->x = vector->x;
	this->y = vector->y;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Define all the statics const variables of the class
//left = negative, right = positive
//up = positive, down = negative
const Vector2D Vector2D::kLeft = Vector2D(-1, 0);
const Vector2D Vector2D::kRight = Vector2D(1, 0);
const Vector2D Vector2D::kUp = Vector2D(0, 1);
const Vector2D Vector2D::kDown = Vector2D(0, -1);
const Vector2D Vector2D::kZero = Vector2D(0, 0);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

double Vector2D::Magnitude() const{
	return sqrt( pow(x, 2) + pow(y, 2) ); 
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

string Vector2D::ToString() const{
	return "Vector 2: \n\t X: " + to_string(x) + "\n\tY: " + to_string(y) + "\n"; 
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Returns a normalized vector2, does not affect the current object
Vector2D Vector2D::Normalized() const{
	double normalizationFactor = sqrt(pow(x, 2) + pow(y, 2));
	return *(new Vector2D( x/normalizationFactor, y/normalizationFactor )); 
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Equality Overload
//lhs: constant Vector2D memory reference for the left hand side of an equality equation
bool Vector2D::operator==(const Vector2D &lhs) const{
	return ( this->x == lhs.x && this->y == lhs.y );
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//>= Overload
//lhs: constant Vector2D memory reference for the left hand side of a >= equation
bool Vector2D::operator>=(const Vector2D &lhs) const{
	return ( (this->x >= lhs.x) && (this->y >= lhs.y) ); 
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//<= Overload 
//lhs: Constant Vector2D memory reference for the left hand side of a <= Equation
bool Vector2D::operator<=(const Vector2D &lhs) const{
	return ( (this->x <= lhs.x) && (this->y <= lhs.y) );
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//> Overload
//lhs: Constant Vector2D memory reference for the left hand side of a > equation
bool Vector2D::operator>(const Vector2D &lhs) const{
	return ( (this->x > lhs.x) && (this->y > lhs.y) );
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//< Overload 
//lhds: constant Vector2D memory reference for the left hand side of a < equation
bool Vector2D::operator<(const Vector2D &lhs) const{
	return ( (this->x < lhs.x) && (this->y < lhs.y) );
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Addition Overload
//lhs: constant Vector2D memory reference representing the left hand side of an addition equation
Vector2D Vector2D::operator+(const Vector2D &lhs) const{
	return *(new Vector2D(this->x + lhs.x, this->y + lhs.y));
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Subtraction Overload 
//lhs: constant Vector2D memory reference representing the left hand side of a subtraction equation
Vector2D Vector2D::operator-(const Vector2D &lhs) const{
	return *(new Vector2D(this->x-lhs.x, this->y-lhs.y));
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Multiplication Overload 
//constant: double to multiply the vector by 
Vector2D Vector2D::operator*(double constant) const{
	return *(new Vector2D(this->x*constant, this->y*constant));
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Division Overload
//lhs: double to divide the vector by
Vector2D Vector2D::operator/(double constant) const{
	return *(new Vector2D(this->x/constant, this->y/constant));
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Post Increment Overload
//Increments x, and then y, to simulate the use of a double for loop to generate a 2x2 Array
Vector2D Vector2D::operator++(){
	
	if(this->x <= this->y)
		this->x++;
	else
		this->y++;
		
	return this;
}
