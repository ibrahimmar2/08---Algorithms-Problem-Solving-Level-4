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

int ReadDay()
{
	int Day;
	cout << "Please enter to Day?" << endl;
	cin >> Day;
	return Day;
}

bool isLeapYear(short Year)
{


	return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

short NumberOfDaysInAMonth(short Month, short Year)
{
	if (Month < 1 || Month>12) return  0;
	int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[Month - 1];
}

short DayOfWeekOrder(short Day, short Month, short Year)
{
	short a, y, m;
	a = (14 - Month) / 12;
	y = Year - a;
	m = Month + (12 * a) - 2;
	// Gregorian://0:sun, 1:Mon, 2:Tue...etc 

	return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

int NumberOfDays(short Day, short Month, short Year)
{
	int TotalDays = 0;
	
	

	for (int i = 0; i < Month;  i++)
	{
		TotalDays += NumberOfDaysInAMonth(i,Year);
	}

	TotalDays += Day;

	return TotalDays;
}


int main()
{
	int Year = ReadYear();
	int Month = ReadMonth();
	int Day = ReadDay();

	cout << "Number of Days from the begining of the year is " << NumberOfDays(Day, Month, Year) << endl;
}

