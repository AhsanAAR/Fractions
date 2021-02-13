#pragma once
class fraction
{
public:
	fraction();
	fraction(int, int);


	void setN(int);
	void setD(int);
	int getN()const;
	int getD()const;


private:
	int numerator, denominator;
};

