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


bool IsDate1BeforeDate2(stDate Date1, stDate Date2) 
{
    return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == 
        Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == 
            Date2.Month ? Date1.Day < Date2.Day : false)) : false);
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

bool CheckDateManth(short Month)
{
    return (Month == 12);
}


stDate InCreaseDateByOneDay(stDate Date)
{
    if (CheckDateDay(Date))
    {
        if (CheckDateManth(Date.Month))
        {
            Date.Month = 1;
            Date.Day = 1;
            Date.Year++;
        }
        else
        {
            Date.Month = 1;
            Date.Day = 1;
        }
    }
    else
    {
        Date.Day++;
    }

    return Date;
}

int GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false)
{
    int Days = 0;
    while (IsDate1BeforeDate2(Date1, Date2))
    {
        Days++;
        Date1 = InCreaseDateByOneDay(Date1);
    }
    return IncludeEndDay ? ++Days : Days;
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
    
    stDate Date2 = ReadFullDate();  
    
    cout << "\nDiffrence is: " << GetDifferenceInDays(Date1, Date2) << " Day(s).";    

    cout << "\nDiffrence (Including End Day) is: " << GetDifferenceInDays(Date1, Date2, true) << " Day(s).";   
    
    system("pause>0");

    return 0;
}
