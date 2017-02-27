#include "Term.h"

void Term::setCoefficient(int coeff){
	coefficient = coeff;
}

void Term::setExponent(int exp){
	exponent = exp;
}

void Term::resetTerm(){
	coefficient = 1;
	exponent = 0;
}

int Term::getCoefficient() const{
	return coefficient;
}

int Term::getExponent() const{
	return exponent;
}

bool Term::operator==(const Term& otherTerm)const{
	return (exponent == otherTerm.exponent);
}

bool Term::operator<(const Term& otherTerm)const{
	return (exponent < otherTerm.exponent);
}

bool Term::operator>(const Term& otherTerm)const{
	return (exponent > otherTerm.exponent);
}

Term::Term(int coeff, int exp) : coefficient(coeff), exponent(exp) {}
