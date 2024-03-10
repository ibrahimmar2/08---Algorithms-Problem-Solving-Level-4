#include <iostream>

using namespace std;

int ReadYear()
{
    int Year;
    cout << "Please enter the year: ";
    cin >> Year;
    return Year;
}

int ReadMonth()
{
    int Month;
    cout << "Please enter the month: ";
    cin >> Month;
    return Month;
}

int ReadDay()
{
    int Day;
    cout << "Please enter the day: ";
    cin >> Day;
    return Day;
}

bool isLeapYear(short Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

short NumberOfDaysInAMonth(short Month, short Year)
{
    if (Month < 1 || Month > 12) return 0;
    int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[Month - 1];
}

short DayOfWeekOrder(short Day, short Month, short Year)
{
    short a, y, m;
    a = (14 - Month) / 12;
    y = Year - a;
    m = Month + (12 * a) - 2;
    // Gregorian: 0 - Sunday, 1 - Monday, ..., 6 - Saturday
    return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

int NumberOfDays(short Day, short Month, short Year)
{
    int TotalDays = 0;
    for (int i = 1; i < Month; i++)
    {
        TotalDays += NumberOfDaysInAMonth(i, Year);
    }
    TotalDays += Day;
    return TotalDays;
}

struct sDate
{
    short Year;
    short Month;
    short Day;
};

sDate GetDate(short DateOrderInYear, short Year)
{
    sDate Date;
    short RenainingDays = DateOrderInYear;
    short MonthDays = 0;

    Date.Year = Year;
    Date.Month = 1;

    while (true)
    {
        MonthDays = NumberOfDaysInAMonth(Date.Month, Year);

        if (RenainingDays > MonthDays)
        {
            RenainingDays -= MonthDays;
            Date.Month++;
        }
        else
        {
            Date.Day = RenainingDays;
            break;
        }
    }

    return Date;
}

bool CheckDate(int Date1, int Date2)
{
    if (Date1 < Date2)
        return true;
    else
        return false;
}

int main()
{
    int Year1 = ReadYear();
    int Month1 = ReadMonth();
    int Day1 = ReadDay();

    int Year2 = ReadYear();
    int Month2 = ReadMonth();
    int Day2 = ReadDay();

    int Date1 = NumberOfDays(Day1, Month1, Year1);
    int Date2 = NumberOfDays(Day2, Month2, Year2);

    if (CheckDate(Date1, Date2))
        cout << "Yes, Date1 is less than Date2." << endl;
    else
        cout << "No, Date1 is getter than Date2." << endl;


    return 0;
}
