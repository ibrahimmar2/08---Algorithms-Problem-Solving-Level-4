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

void PrintDayNameOfWeek(short Year, short Month, short Day)
{
	int a, y, m, d;

	a = (14 - Month) / 12;
	y = Year - a;
	m = Month + (12 * a) - 2;

	d = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	string DayOfWeaks[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

	cout << "Data      : " << Day << "/" << Month << "/" << Year << endl;
	cout << "Day Order :" << d << endl;
	cout << "Day Name  :" << DayOfWeaks[d] << endl;


}


int main()
{
	int Year = ReadYear();
	int Month = ReadMonth();
	int Day = ReadDay();

	PrintDayNameOfWeek(Year, Month, Day);

}
