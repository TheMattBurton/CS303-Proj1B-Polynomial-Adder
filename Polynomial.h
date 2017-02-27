#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Term.h"
#include <string>
#include <list>

using std::string;

class Polynomial
{
public:
	bool isEmpty();

	void setPolynomial(string input);

	void createTerms();

	void sortTerms();

	void addTerms();

	void printTerms() const;

	void clearTerms();

	Polynomial(string input = "");

private:
	string inputPolynomial;
	std::list<Term> termsList;
};

#endif