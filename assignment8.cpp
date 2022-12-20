/*
Created by: Arjun Mandair and Kishan Muhundhan
Created on: November 29, 2022
Last modified: December 1, 2022
Version: 1.0

Purpose: To create a proper fraction object using classes, setters,
getters, mutators, and accessors

Assumptions: We are assuming that when constructing a proper
fraction, the user inputs integers
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

class Fraction 
{
	private:
		int num;
		int denom;

	public:
		//Default constructor (setter)
		Fraction() 
		{
			(*this).num = 0;
			(*this).denom = 1;
		}

		//Data constructor (setter)
		Fraction(int numerator, int denominator) 
		{
			if(denominator == 0) 
			{
				(*this).num = 0;
				(*this).denom = 1;
				cout << "Denominator cannot be equal to 0" << endl
				     << "Failed to change denominator" << endl
				     << "Fraction numerator reset to 0 and "
				     << "fraction denominator reset to 1" << endl;
			}
			else if(numerator > denominator) 
			{
				num = 0;
				denom = 1;
				cout << "Numerator is greater than denominator. "
				     << "Not a proper fraction." << endl
				     << "Fraction numerator reset to 0 and fraction"
				     << " denominator reset to 1" << endl;
			}
			else 
			{
				num = numerator;
				denom = denominator;
			}
		}

		//Getter that returns a fraction's numerator
		int getNum() const 
		{
			return (*this).num;
		}

		//Getter that returns a fraction's denominator
		int getDenom() const 
		{
			return (*this).denom;
		}

		//Setter that sets a fractions numerator
		void setNum(int numerator) 
		{
			if(numerator > (*this).denom) 
			{
				cout << "Numerator is greater than denominator. "
				     << "Not a proper fraction." << endl
				     << "Failed to change numerator" << endl;
			}
			else 
			{
				(*this).num = numerator;
			}
		}

		//Setter that sets a fractions denominator
		void setDenom(int denominator) 
		{
			if(denominator == 0) 
			{
				cout << "Denominator cannot be equal to 0" << endl
				     << "Failed to change denominator" << endl;
			}
			else if((*this).num > denominator) 
			{
				cout << "Numerator is greater than denominator. "
				     << "Not a proper fraction." << endl
				     << "Failed to change denominator" << endl;
			}
			else
			{
				(*this).denom = denominator;
			}
		}

		//Function that return a rounded fraction in decimal
		//form to a specified decimal place
		double roundFrac(const int decimal) const 
		{
			return (round(((*this).num / ((*this).denom / 1.0))
			              * pow(10, decimal))) / pow(10, decimal);
		}

		//Boolean functiont that returns true if fractions
		//are exactly same and false if not
		bool isExactlySame(Fraction const & fracTwo) const 
		{
			if((*this).num == fracTwo.num && (*this).denom == fracTwo.denom) 
			{
				return true;
			} 
			else 
			{
				return false;
			}
		}

		//Function that prints out a fraction to the console
		void output() const 
		{
			cout << (*this).num << " / " << (*this).denom << endl;
		}
};

int main() 
{
	//Outputting default fraction
	Fraction fracDefault;
	fracDefault.output();
	cout << endl;

	//Outputting fracOne with both getters and function
	Fraction fracOne(3, 4);
	cout << "fracOne Numerator: " << fracOne.getNum() << endl
		 << "fracOne Denominator: " << fracOne.getDenom() << endl;
	fracOne.output();
	cout << endl;

	//Changing fracOne numerator to make numerator > denominator
	fracOne.setNum(5);
	cout << "fracOne Numerator: " << fracOne.getNum() << endl
		 << "fracOne Denominator: " << fracOne.getDenom() << endl;
	fracOne.output();
	cout << endl;

	//Changing fracOne denominator to make numerator > denominator
	fracOne.setDenom(2);
	cout << "fracOne Numerator: " << fracOne.getNum() << endl
		 << "fracOne Denominator: " << fracOne.getDenom() << endl;
	fracOne.output();
	cout << endl;

	//Making two fractions the same
	Fraction fracTwo(3, 4);
	if(fracOne.isExactlySame(fracTwo)) 
	{
		cout << "fracOne and fracTwo are exactly the same" << endl;
	} 
	else 
	{
		cout << "fracOne and fracTwo are NOT exactly the same" << endl;
	}
	cout << endl;

	//Making two fractions not the same
	fracOne.setDenom(8);
	fracOne.setNum(5);
	if(fracOne.isExactlySame(fracTwo)) 
	{
		cout << "fracOne and fracTwo are exactly the same" << endl;
	} 
	else 
	{
		cout << "fracOne and fracTwo are NOT exactly the same" << endl;
	}
	cout << endl;

	//Rounding fractions to specific decimal places
	fracOne.setDenom(65);
	fracOne.setNum(-7);
	cout << fracOne.roundFrac(5) << endl << fracOne.roundFrac(1) << endl
		 << fracOne.roundFrac(3) << endl << endl;

	//Trying to set denominator to 0
	fracOne.setDenom(0);
	cout << endl;
	Fraction fracThree(5, 0);

	return EXIT_SUCCESS;
}

/*



*/
