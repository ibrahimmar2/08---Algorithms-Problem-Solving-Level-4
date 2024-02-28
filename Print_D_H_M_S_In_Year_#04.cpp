#include <iostream>

using namespace std;

int ReadYear()
{
	int Year;
	cout << "Please enter to year?" << endl;
	cin >> Year;
	return Year;
}

bool IsLeapYear(int Year)
{
	return (Year % 400 == 0) ? true : (Year % 100 != 0) ? false : (Year % 4 == 0)? true: false;
}

/*
int NumberOfDays(int Year)
{
	return IsLeapYear(Year) ? 366 : 365;
}

int NumberOfHours(int Year)
{
	return IsLeapYear(Year) ? 8784 : 8760;
}

int NumberOfMinutes(int Year)
{
	return IsLeapYear(Year) ? 527040 : 525600;
}

int NumberOfSeconds(int Year)
{
	return IsLeapYear(Year) ? 31622400 : 3153600;
}
*/


int NumberOfDays(int Year)
{
	return IsLeapYear(Year) ? 366 : 365;
}

int NumberOfHours(int Year)
{
	return NumberOfDays(Year) * 24;
}

int NumberOfMinutes(int Year)
{
	return NumberOfHours(Year) * 60;
}

int NumberOfSeconds(int Year)
{
	return NumberOfMinutes(Year) * 60;
}

int main()
{
	int Year = ReadYear();

	cout << "Number of Days    in Year [" << Year << "] is " << NumberOfDays(Year) << endl;
	cout << "Number of Hours   in Year [" << Year << "] is " << NumberOfHours(Year) << endl;
	cout << "Number of Minutes in Year [" << Year << "] is " << NumberOfMinutes(Year) << endl;
	cout << "Number of Seconds in Year [" << Year << "] is " << NumberOfSeconds(Year) << endl;

}
