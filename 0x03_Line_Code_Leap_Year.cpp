#include <iostream>

using namespace std;

int ReadYear()
{
	int Year;
	cout << "Please enter to year?" << endl;
	cin >> Year;
	return Year;
}
/*
* 
bool IsLeapYear(int Year)
{
	if (Year % 400 == 0)
		return true;
	else if (Year % 100 == 0)
		return false;
	else if (Year % 4 == 0)
		return true;
	else
		return false;
}
*/

bool IsLeapYear(int Year)
{
	return (Year % 400 == 0) ? true : (Year % 100 != 0) ? false : (Year % 4 == 0)? true: false;
}

int main()
{
	int Year = ReadYear();

	if (IsLeapYear(Year))
		cout << Year << " is Leap Year" << endl;
	else
		cout << Year << " is Not Leap Year" << endl;
}
