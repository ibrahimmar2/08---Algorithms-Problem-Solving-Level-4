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


stDate DecreaseDateByOneDay(stDate Date)
{
        //  MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);

        if (Date.Day == 1)
        {
            if (Date.Month == 1)
            {
                Date.Month = 12;
                Date.Day = 31;
                Date.Year--;
            }
            else
            {
                Date.Month--;
                Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
            }
        }
        else
        {
            Date.Day--;
            ;
        }
        
        return Date;
}


stDate DecreaseDateByXDays(stDate Date, short XDays)
{
    for (short i = 0; i < XDays; i++)
    {
        Date.Day--;
    }
    return Date;
}

stDate DecreaseDateByOneWeek(stDate Date)
{
    for (short i = 0; i < 7; i++)
    {
        Date = DecreaseDateByOneDay(Date);
    }
    return Date;
}

stDate DecreaseDateByXWeek(stDate Date, short Week)
{
    for (short i = 0; i < Week; i++)
    {
        Date = DecreaseDateByOneWeek(Date);

    }
    return Date;
}

stDate DecreaseDateByOneMonths(stDate Date)
{
    if (Date.Month == 1)
    {
        Date.Month = 12;
        Date.Year--;
    }
    else
    {
        Date.Month--;
    }

    short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

    if (Date.Day > NumberOfDaysInCurrentMonth)
    {
        Date.Day = NumberOfDaysInCurrentMonth;
    }

    return Date;
}

stDate DecreaseDateByXMonths(stDate Date, short Month)
{
    for (short i = 0; i < Month; i++)
    {
        Date = DecreaseDateByOneMonths(Date);

    }
    return Date;
}

stDate DecreaseDateByOneYear(stDate Date)
{
    Date.Year--;

    return Date;
}

stDate DecreaseDateByXYear(stDate Date, short Year)
{
    for (short i = 0; i < Year; i++)
    {
        Date = DecreaseDateByOneYear(Date);

    }
    return Date;
}

stDate DecreaseDateByOneYearFaster(stDate Date, short Year)
{
    Date.Year -= Year;

    return Date;
}

stDate DecreaseDateByOneDecades(stDate Date)
{
    Date.Year -= 10;

    return Date;
}

stDate DecreaseDateByXDecades(stDate Date, short Decades)
{
    for (short i = 0; i < Decades; i++)
    {
        Date = DecreaseDateByOneDecades(Date);

    }
    return Date;
}

stDate DecreaseDateByOneDecadesFaster(stDate Date, short Decades)
{
    Date.Year -= Decades * 10;

    return Date;
}

stDate DecreaseDateByOneCentury(stDate Date)
{
    Date.Year -= 100;

    return Date;
}

stDate DecreaseDateByOneMillennium(stDate Date)
{
    Date.Year -= 1000;

    return Date;
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
    stDate Date = ReadFullDate();

    Date = DecreaseDateByOneDay(Date);
    cout << "01-Subtracting one day is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = DecreaseDateByXDays(Date, 10);
    cout << "02-Subtracting 10 day is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = DecreaseDateByOneWeek(Date);
    cout << "03-Subtracting one week is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = DecreaseDateByXWeek(Date, 10);
    cout << "04-Subtracting 10 week is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = DecreaseDateByOneMonths(Date);
    cout << "05-Subtracting one month is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = DecreaseDateByXMonths(Date, 5);
    cout << "06-Subtracting 5 month is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = DecreaseDateByOneYear(Date);
    cout << "07-Subtracting one year is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = DecreaseDateByXYear(Date, 10);
    cout << "08-Subtracting 10 year is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = DecreaseDateByOneYearFaster(Date, 10);
    cout << "09-Subtracting 10 year (faster) is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = DecreaseDateByOneDecades(Date);
    cout << "10-Subtracting one Decade is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = DecreaseDateByXDecades(Date, 10);
    cout << "11-Subtracting 10 Decades is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = DecreaseDateByOneDecadesFaster(Date, 10);
    cout << "12-Subtracting 10 Decades (faster) is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;


    Date = DecreaseDateByOneCentury(Date);
    cout << "13-Subtracting one Century is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;


    Date = DecreaseDateByOneMillennium(Date);
    cout << "14-Subtracting one Millennium is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;


    return 0;
}
