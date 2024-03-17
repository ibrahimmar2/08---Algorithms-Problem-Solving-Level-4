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

int IsActucalVaction(stDate Start, stDate End)
{
    int DaysCount = 0;

    while (IsDate1BeforeDate2(Start, End))
    {
        if (IsBusinessDay(Start))
            DaysCount++;

        Start = IncreaseDateByOneDay(Start);
    }

    return DaysCount;
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

    cout << "Vacation Starts: \n";
    stDate Starts = ReadFullDate();


    cout << "Vacation Ends: \n";
    stDate Ends = ReadFullDate();

    cout << "Vacation From  : " << DayShortName(DayOfWeekOrder(Starts))<< " , " << Starts.Day << " / " << Starts.Month << " / " << Starts.Year << endl;

    cout << "Vacation To  : " << DayShortName(DayOfWeekOrder(Ends)) << " , " << Ends.Day << " / " << Ends.Month << " / " << Ends.Year << endl;

    cout << "\n\nActucal Vaction Days is : " << IsActucalVaction(Starts, Ends) << endl;



    return 0;
}
