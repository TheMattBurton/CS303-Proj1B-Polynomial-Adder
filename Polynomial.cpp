#include "ErrorClass.h"
#include "Polynomial.h"
#include <string>
#include <sstream>
#include <iostream>

using std::cout;
using std::stringstream;

bool Polynomial::isEmpty(){
	return termsList.empty();
}

void Polynomial::setPolynomial(string input){
	inputPolynomial = input;	
}

void Polynomial::createTerms(){
	size_t polyStringSize = inputPolynomial.size();	
	int currentCoef, currentExpo;
	Term currentTerm;
	
	for (size_t pos = 0; pos < polyStringSize; pos++){ 
		// check each character and edit string based on conditions, resulting in space-delimited coefficients & exponents		
		if (inputPolynomial[pos] == '^' && inputPolynomial[pos - 1] != 'X')
			throw ErrorClass("Incorrect input format detected. \n");
		else if (inputPolynomial[pos] == 'X'
			&& (pos == 0 || (pos > 0 && inputPolynomial.find_first_not_of("0123456789", pos - 1) == pos - 1))) {
			inputPolynomial.insert(pos, "1");
			polyStringSize++;
		}
		else if ((inputPolynomial[pos] == '-')
			&& (pos > 0) && (inputPolynomial[pos - 1] != 'X')
			&& (inputPolynomial[pos - 1] != '^')
			&& (inputPolynomial[pos - 1] != ' ')){
			inputPolynomial.insert(pos, "X^0 ");
			polyStringSize += 4;
		}
		else if ((inputPolynomial[pos] == '+')
			&& (pos > 0)
			&& (inputPolynomial[pos - 1] != 'X')
			&& (inputPolynomial[pos - 1] != '^')
			&& (inputPolynomial[pos - 1] != ' ')){
			inputPolynomial.insert(pos, "X^0 ");
			polyStringSize += 4;
		}
		else if (inputPolynomial[pos] == 'X'
			&& inputPolynomial[pos + 1] != '^'){
			inputPolynomial.insert(pos + 1, "^1 ");
			polyStringSize += 3;
		}
		if (inputPolynomial[pos] == 'X'){						
			inputPolynomial.erase(pos, 2);
			inputPolynomial.insert(pos, " ");
			if (inputPolynomial.find_first_not_of("0123456789", pos + 2) < polyStringSize)
				pos = inputPolynomial.find_first_not_of("0123456789", pos + 2);
			inputPolynomial.insert(pos, " ");			
		}
		if (inputPolynomial[pos] == '+')
			inputPolynomial.replace(pos, 1, " ");
	}

	inputPolynomial += " 0"; // pad string in case single integer entered as polynomial
	
	if (inputPolynomial.find_first_not_of("0123456789- ", 0) < inputPolynomial.size())
		throw ErrorClass("Incorrect input format detected. \n");

	stringstream ss(inputPolynomial);

	while (ss){ // load parsed input string into termsList
		ss >> currentCoef >> currentExpo;
		currentTerm.setCoefficient(currentCoef);
		currentTerm.setExponent(currentExpo);
				
		if (currentCoef != 0) termsList.push_back(currentTerm);
		currentCoef = currentExpo = 0;
		currentTerm.resetTerm();
	}
}

void Polynomial::sortTerms(){
	std::list<Term>::iterator location_iter = termsList.begin();
	std::list<Term>::const_iterator location_prev_iter = termsList.begin();
	std::list<Term>::iterator firstOoO_iter = termsList.begin();
	std::list<Term>::const_iterator firstOoO_prev_iter = termsList.begin();
	Term tempTerm;

	for (++firstOoO_iter; firstOoO_iter != termsList.end(); ++firstOoO_iter){
		if (*firstOoO_iter > *firstOoO_prev_iter){
			tempTerm = *firstOoO_iter;  // save Term that needs to be moved/sorted
			location_prev_iter = location_iter = firstOoO_iter;
			--location_prev_iter;

			do
			{
				*location_iter = *location_prev_iter; // move Terms down the list
				--location_iter;
				if (location_prev_iter != termsList.begin())
					--location_prev_iter;
				// continue until beginning is reached, or the correct spot in list has been found for out-of-order Term
			} while (location_iter != termsList.begin() && *location_prev_iter < tempTerm);

			*location_iter = tempTerm;
		}
		++firstOoO_prev_iter;
	}
}

void Polynomial::addTerms(){
	std::list<Term>::iterator location_iter = termsList.begin();
	std::list<Term>::iterator location_prev_iter = termsList.begin();

	for (++location_iter; location_iter != termsList.end(); ++location_iter){
		if (*location_prev_iter == *location_iter){ //comparing exponent value equality
			location_prev_iter->setCoefficient(location_prev_iter->getCoefficient() + location_iter->getCoefficient());			
			termsList.erase(location_iter);  // Delete Term that has been added to previous
			location_iter = location_prev_iter;  // Reset iterator after deleting Term
		}
		if (location_prev_iter != location_iter)
			++location_prev_iter;  // advance prev_iter to next Term for comparison
	}
}

void Polynomial::printTerms() const{
	for (std::list<Term>::const_iterator iter = termsList.begin(); iter != termsList.end(); ++iter){
		if (iter->getCoefficient() > 0 && iter != termsList.begin())
			cout << "+";
		if (iter->getCoefficient() > 1 || iter->getCoefficient() < -1 || (iter->getExponent() == 0 && iter->getCoefficient() != 0)){ 
			cout << iter->getCoefficient();
			if (iter->getExponent() != 0)
				cout << "X";
		}
		else if (iter->getCoefficient() == 1)
			cout << "X";
		else if (iter->getCoefficient() == -1)
			cout << "-X";
		if (iter->getExponent() != 0 && iter->getExponent() != 1 && iter->getCoefficient() != 0)
			cout << "^" << iter->getExponent();
	}	
}

void Polynomial::clearTerms(){
	termsList.clear();
}

Polynomial::Polynomial(string input) : inputPolynomial(input){}