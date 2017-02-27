#ifndef TERM_H
#define TERM_H

class Term
{
public:
	void setCoefficient(int coeff);

	void setExponent(int exp);

	void resetTerm();

	int getCoefficient() const;

	int getExponent() const;

	bool operator==(const Term& otherTerm)const;

	bool operator<(const Term& otherTerm)const;

	bool operator>(const Term& otherTerm)const;
	
	Term(int coeff = 1, int exp = 0 );
	
private:
	int coefficient;
	int exponent;
};

#endif