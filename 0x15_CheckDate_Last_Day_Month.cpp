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


struct stDate
{
    short Year;
    short Month;
    short Day;
};


bool IsLeapYear(short Year)
{


    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

int NumberOfDaysInAMonth(short Month, short Year)
{
    if (Month < 1 || Month > 12)
        return 0;

    if (Month == 2)
        return IsLeapYear(Year) ? 29 : 28;

    return (Month == 4 || Month == 6 || Month == 9 || Month == 11) ? 30 : 31;
}


bool CheckDateDay(stDate Date)
{
    return Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year) ? true : false;
}

bool CheckDateManth(stDate Date)
{
    return Date.Month == 12 ? true : false;
}

 stDate ReadFullDate()
 { 
     stDate Date;
     Date.Day = ReadDay();     
     Date.Month = ReadMonth(); 

     Date.Year = ReadYear();

     cout << "\n\n";
     return Date;
 }

int main()
{
    stDate Date1 = ReadFullDate();


    if (CheckDateDay(Date1))
        cout << "Yes, Day is Last Day in Month" << endl;
    else
        cout << "No, Day is Not Last Day in Month" << endl;

    if (CheckDateManth(Date1))
        cout << "Yes, Month is Last Day in Year" << endl;
    else
        cout << "No, Month is Not Last Day in Year" << endl;

    return 0;
}
