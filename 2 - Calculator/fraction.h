#include <iostream>
#include <cstdint>

#ifndef _FRACTION_H
#define _FRACTION_H

class Fraction {

	private:
		int32_t num, den;

	public:
		Fraction(int32_t n = 0, int32_t d = 1);
		~Fraction(void);

		// rhs == right hand side
		Fraction operator+(Fraction rhs);
		Fraction operator-(Fraction rhs);
		Fraction operator*(Fraction rhs);
		Fraction operator/(Fraction rhs);
		Fraction &operator=(Fraction rhs);

		bool operator==(Fraction rhs);
		bool operator!=(Fraction rhs);
		bool operator<=(Fraction rhs);
		bool operator>=(Fraction rhs);
		bool operator<(Fraction rhs);
		bool operator>(Fraction rhs);

		int32_t getNum() { return num; }
		int32_t getDen() { return den; }

};

std::istream &operator>>(std::istream &is, Fraction &f);
std::ostream &operator<<(std::ostream &os, Fraction f);

#endif
