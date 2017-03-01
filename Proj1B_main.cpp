/********************************************
*	Burton, Matt
*	Date: February 28, 2017
*	CS3030001 Spring 2017
*	Project 1B - Polynomial Adder
*	This program can accept input of multiple polynomials,
*	add the terms, and display the result.
********************************************/

#include "User_Interface.h"

int main()
{
	Polynomial the_polynomial;
	User_Interface userinterface(the_polynomial);
	userinterface.menu_process();

	return 0;
}