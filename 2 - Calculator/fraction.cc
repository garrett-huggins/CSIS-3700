#include "fraction.h"

int32_t gcd(int32_t a,int32_t b) {
  int32_t
    r;

  // make sure a and b are not negative
  a = (a < 0) ? -a : a;
  b = (b < 0) ? -b : b;

  while (b != 0) {
    r = a % b;
    a = b;
    b = r;
  }

  return a;
}

Fraction::Fraction(int32_t n, int32_t d) {
	int32_t g;

	if (d < 0) {
		n = -n;
		d = -d;
	}

	g = gcd(n,d);

	num = n / g;
	den = d / g;
}

Fraction::~Fraction(void) {}

Fraction Fraction::operator+(Fraction rhs) {
	int32_t s,t;
	
	s = num * rhs.den + den * rhs.num;
	t = den * rhs.den;
	
	return Fraction(s,t);
}
Fraction Fraction::operator-(Fraction rhs) {
	int32_t s,t;
	
	s = num * rhs.den - rhs.num * den;
	t = den * rhs.den;
	
	return Fraction(s,t);
}
Fraction Fraction::operator*(Fraction rhs) {
	int32_t s,t;

	s = num * rhs.num;
	t = den * rhs.den;

	return Fraction(s,t);

}
Fraction Fraction::operator/(Fraction rhs) {
	int32_t s,t;

	s = num * rhs.den;
	t = den * rhs.num;

	return Fraction(s,t);
}

Fraction &Fraction::operator=(Fraction rhs) {
	num = rhs.num;
	den = rhs.den;

	return *this;
}

bool Fraction::operator==(Fraction rhs) {

	return num == rhs.num && den == rhs.den;

}
bool Fraction::operator!=(Fraction rhs) {

	return num != rhs.num || den != rhs.den;
}
bool Fraction::operator<=(Fraction rhs) {

	return num * rhs.den <= den * rhs.num;
}
bool Fraction::operator>=(Fraction rhs) {
	return num * rhs.den >= den * rhs.num;
}
bool Fraction::operator<(Fraction rhs) {
	return num * rhs.den < den * rhs.num;
}
bool Fraction::operator>(Fraction rhs) {
	return num * rhs.den > den * rhs.num;
}

std::istream &operator>>(std::istream &is, Fraction &f) {

	int32_t n,d;
	
	char slash;

	is >> n >> slash >> d;
	
	f = Fraction(n,d);
	
	return is;
}
std::ostream &operator<<(std::ostream &os, Fraction f) {

	os << f.getNum() << " / " << f.getDen();

	return os;
}
