 #pragma warning(disable : 4996)

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

bool IsDate1BeforeDate2(stDate Date1, stDate Date2) 
{
    return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
}

bool IsLastDayInMonth(stDate Date) 
{ 
    return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year)); 
}

bool IsLastMonthInYear(short Month) 
{
    return (Month == 12);
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

stDate IncreaseDateByOneDay(stDate Date)
{
    if (IsLastDayInMonth(Date))
    {
        if (IsLastMonthInYear(Date.Month)) 
        {
            Date.Month = 1;
            Date.Day = 1;
            Date.Year++;
        }
        else 
        {
            Date.Day = 1;
            Date.Month++;
        }
    }
    else
    {
        Date.Day++;
    }
    return Date; }

int GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false) 
{
    int Days = 0;
    
    while (IsDate1BeforeDate2(Date1, Date2))
    {
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }
    
    return IncludeEndDay ? ++Days : Days;
}

int DayOfWeekOrder(stDate Date)
{
    return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
}

string DayShortName(short DayOfWeekOrder)
{
    string arrDayNames[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

    return arrDayNames[DayOfWeekOrder];
}

bool IsEndOfWeek(stDate Date)
{
    return  DayOfWeekOrder(Date) == 6;
}

bool IsWeekEnd(stDate Date)
{ 
    //Weekends are Fri and Sat
   
    short DayIndex = DayOfWeekOrder(Date); 
    return  (DayIndex == 5 || DayIndex == 6); 
}

bool IsBusinessDay(stDate Date)
{
    return  !IsWeekEnd(Date);
}


int DaysUntilEndOfWeek(stDate Date)
{
    return 6 - DayOfWeekOrder(Date);
}

int DaysUntilEndOfMonth(stDate Date1)
{
    stDate EndOfMontDate;

    EndOfMontDate.Day = NumberOfDaysInAMonth(Date1.Month, Date1.Year);
    EndOfMontDate.Month = Date1.Month;
    EndOfMontDate.Year = Date1.Year;

    return GetDifferenceInDays(Date1, EndOfMontDate, true);
}

int DaysUntilEndOfYear(stDate Date1)
{
    stDate EndOfYearDate;

    EndOfYearDate.Day = 31;
    EndOfYearDate.Month = 12;
    EndOfYearDate.Year = Date1.Year;

    return GetDifferenceInDays(Date1, EndOfYearDate, true);
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

stDate GetSystemDate() 
{
    stDate Date;
    time_t t = time(0);
    tm* now = localtime(&t);
    
    Date.Year = now->tm_year + 1900;   
    Date.Month = now->tm_mon + 1; 
    Date.Day = now->tm_mday;
    
    return Date; 
}

int main()
{
    stDate Date = GetSystemDate();



    cout << "Today is  : " << DayShortName(DayOfWeekOrder(Date))<< " , " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    cout << "\nIs it Week Of End?\n";
    
    if (IsEndOfWeek(Date))
        cout << "Yes end of week.\n";
    else
        cout << "No not end of week.\n";

    cout << "\n\nIs it Weekend?\n";

    if (IsWeekEnd(Date))
        cout << "Yes it is week.\n";
    else
        cout << "No today is " << DayShortName(DayOfWeekOrder(Date)) << endl;

    cout << "\n\nIs it Is Business Day?\n";

    if (IsBusinessDay(Date))
        cout << "Yes it is Business Day.\n";
    else
        cout << "No it is NOT Business Day.\n";


    cout << "Days Until End Of Week : " << DaysUntilEndOfWeek(Date) << " Day(s)" << endl;

    cout << "\nDays until end of month : " << DaysUntilEndOfMonth(Date) << " Day(s).";

    cout << "\nDays until end of year : " << DaysUntilEndOfYear(Date) << " Day(s).";
    

    return 0;
}
