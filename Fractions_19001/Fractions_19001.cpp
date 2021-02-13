#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include "fraction_19001.h"

using namespace std;

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int LCM(int a, int b) {
	return a * b / gcd(a, b);
}

fraction operator+(fraction f1, fraction f2) {
	fraction ret;
	ret.setD(LCM(f1.getD(), f2.getD()));
	ret.setN(f1.getN() * ret.getD() / f1.getD() + f2.getN() * ret.getD() / f2.getD());
	return ret;
}

fraction additiveInverse(fraction f) {
	fraction ret;
	ret.setN(-f.getN());
	ret.setD(f.getD());
	return ret;
}

fraction operator-(fraction f1, fraction f2) {
	return f1 + additiveInverse(f2);
}
fraction operator*(fraction f1, fraction f2) {
	fraction ret;
	ret.setN(f1.getN() * f2.getN());
	ret.setD(f1.getD() * f2.getD());
	return ret;
}
fraction multiplicativeInverse(fraction f) {
	fraction ret;
	ret.setN(f.getD());
	ret.setD(f.getN());
	return ret;
}
fraction operator/(fraction f1, fraction f2) {
	return f1 * multiplicativeInverse(f2);
}
fraction reduced(fraction f) {
	fraction ret;
	ret.setN(f.getN() / gcd(f.getD(), f.getN()));
	ret.setD(f.getD() / gcd(f.getD(), f.getN()));
	return ret;
}


float toFloat(fraction f){
	return 1.0 * f.getN() / f.getD();
}

void print(fraction f){
	cout << setw(2) << f.getN() << '/' << setw(2) << f.getD() << "  , "
		<< setw(2) << reduced(f).getN() << '/' << setw(2) << reduced(f).getD() << "  , "
		<< toFloat(f);
}

void load(fraction** &list, int &size) {
	ifstream reader("Data.txt");
	reader >> size;
	list = new fraction*[size];
	int n, d;
	for (int i = 0; i < size; i++) {
		reader >> n >> d;
		list[i] = new fraction(n, d);
	}
}

void printList(fraction**& list, const int& size) {
	for (int i = 0; i < size; i++){
		cout << "\t\t\tFraction " << i + 1 << " = ";
		print(*list[i]);
		cout << endl << endl;
	}
}

int getNumber(int size) {
	char d;
	int in = 0;
	do {
		d = _getch();
		cout << d;
		if (d == ' ')
			break;
		else if (d < '0' || d > '9') {
			return 0;
			break;
		}
		else {
			in *= 10;
			in += d - '0';
		}
	} while (1);
	if (in > size)
		return 0;
	else return in;
}

int main() {
	fraction** list;
	int size;
	load(list, size);
	char option;
	int l, r1, r2, in;
	char opr, d;
	bool valid;

	do {
		system("cls");
		printList(list, size);
		cout << "\n\n\n\t\t\tF_ = F_ opr F_  or 1 / F_ or -F_  (opr = + - * /)";
		cout << "\n\n  \t\t\tF";
		valid = true;
		if (!(valid = l = getNumber(size)))
			continue;
		cout << "= ";
		d = _getch();
		cout << d;
		if (d == '1') {
			cout << " / F";
			if (!(valid = r1 = getNumber(size)))
				continue;
			*list[l - 1] = multiplicativeInverse(*list[r1 - 1]);
		}
		else if (d == '-') {
			cout << " F";
			if (!(valid = r1 = getNumber(size)))
				continue;
			*list[l - 1] = additiveInverse(*list[r1 - 1]);
		}
		else if (d == 'F') {
			if (!(valid = r1 = getNumber(size)))
				continue;
			d = _getch();
			cout << d << " F";
			if (!(d == '+' || d == '-' || d == '*' || d == '/')) {
				valid = false;
				continue;
			}
			opr = d;
			if (!(valid = r2 = getNumber(size)))
				continue;
			switch (opr) {
			case '+':
				*list[l - 1] = *list[r1 - 1] + *list[r2 - 1]; break;
			case '-':
				*list[l - 1] = *list[r1 - 1] - *list[r2 - 1]; break;
			case '*':
				*list[l - 1] = *list[r1 - 1] * *list[r2 - 1]; break;
			case '/':
				*list[l - 1] = *list[r1 - 1] / *list[r2 - 1]; break;
			}
		}
		else {
			valid = false;
			continue;
		}
		system("cls");
		printList(list, size);
		cout << "\n\n\n\t\t\tDo you wanna Continue? (Y/N)";
		option = _getch();
		if (option == 'N' || option == 'n')
			break;
		else
		{
			valid = false;
			continue;
		}
	} while (!valid);
	return 0;
}