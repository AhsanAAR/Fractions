#include "fraction_19001.h"
#include <iostream>
#include <iomanip>

using namespace std;


void fraction::setN(int N) {
		numerator = N;
}
void fraction::setD(int D) {
	if (D < 0) {
		denominator = -D;
		setN(-numerator);
	}
	else if (D == 0) {
		setN(0);
		setD(1);
	}
	else {
		denominator = D;
	}
}
int fraction::getN()const {
	return numerator;
}
int fraction::getD()const{
	return denominator;
}

fraction::fraction() {
	numerator = denominator = 0;
}
fraction::fraction(int n, int d) {
	setN(n);
	setD(d);
}




