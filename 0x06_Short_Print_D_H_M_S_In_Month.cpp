#include <iostream>

using namespace std;

int ReadYear()
{
	int Year;
	cout << "Please enter to year?" << endl;
	cin >> Year;
	return Year;
}

int ReadMonth()
{
	int Month;
	cout << "Please enter to Month?" << endl;
	cin >> Month;
	return Month;
}


bool IsLeapYear(int Year)
{
	return (Year % 400 == 0) ? true : (Year % 100 != 0) ? false : (Year % 4 == 0)? true: false;
}

int NumberOfDaysInAMonth(short Month, short Year)
{
	if (Month < 1 || Month > 12)
		return 0;

	if (Month == 2)
		return IsLeapYear(Year) ? 29 : 28;

	return (Month == 4 || Month == 6 || Month == 9 || Month == 11) ? 30 : 31;
}

int NumberOfHours(short Month, int Year)
{
	return NumberOfDaysInAMonth(Month, Year) * 24;
}

int NumberOfMinutes(short Month, int Year)
{
	return NumberOfHours(Month, Year) * 60;
}

int NumberOfSeconds(short Month, int Year)
{
	return NumberOfMinutes(Month, Year) * 60;
}

int main()
{
	int Year = ReadYear();
	int Month = ReadYear();

	cout << "Number of Days    in Year [" << Month << "] is " << NumberOfDaysInAMonth(Month, Year) << endl;
	cout << "Number of Hours   in Year [" << Month << "] is " << NumberOfHours(Month, Year) << endl;
	cout << "Number of Minutes in Year [" << Month << "] is " << NumberOfMinutes(Month, Year) << endl;
	cout << "Number of Seconds in Year [" << Month << "] is " << NumberOfSeconds(Month, Year) << endl;

}
