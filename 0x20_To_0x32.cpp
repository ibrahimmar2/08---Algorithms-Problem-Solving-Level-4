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


stDate Adding_One_Day(stDate Date)
{
    short Days;
    Days = 1;

    short RenainingDays = Days + NumberOfDays(Date.Day, Date.Month, Date.Year);
    short MonthDays = 0;

    Date.Month = 1;

    while (true)
    {
        MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);

        if (RenainingDays > MonthDays)
        {
            RenainingDays -= MonthDays;
            Date.Month++;

            if (Date.Month > 12)
            {
                Date.Month = 1;
                Date.Year++;
            }

        }
        else
        {
            Date.Day = RenainingDays;
            break;
        }
    }

    return Date;
}

stDate IncreaseDateByXDays(stDate Date, short XDays)
{
    for (short i = 0; i < XDays; i++)
    {
        Date.Day++;
    }
    return Date;
}

stDate IncreaseDateByOneWeek(stDate Date)
{
    for (short i = 0; i < 7; i++)
    {
        Date = Adding_One_Day(Date);
    }
    return Date;
}

stDate IncreaseDateByXWeek(stDate Date, short Week)
{
    for (short i = 0; i < Week; i++)
    {
        Date = IncreaseDateByOneWeek(Date);

    }
    return Date;
}

stDate IncreaseDateByOneMonths(stDate Date)
{
    if (Date.Month == 12)
    {
        Date.Month = 1;
        Date.Year++;
    }
    else
    {
        Date.Month++;
    }

    short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

    if (Date.Day > NumberOfDaysInCurrentMonth)
    {
        Date.Day = NumberOfDaysInCurrentMonth;
    }

    return Date;
}

stDate IncreaseDateByXMonths(stDate Date, short Month)
{
    for (short i = 0; i < Month; i++)
    {
        Date = IncreaseDateByOneMonths(Date);

    }
    return Date;
}

stDate IncreaseDateByOneYear(stDate Date)
{
    Date.Year++;

    return Date;
}

stDate IncreaseDateByXYear(stDate Date, short Year)
{
    for (short i = 0; i < Year; i++)
    {
        Date = IncreaseDateByOneYear(Date);

    }
    return Date;
}

stDate IncreaseDateByOneYearFaster(stDate Date, short Year)
{
    Date.Year += Year;

    return Date;
}

stDate IncreaseDateByOneDecades(stDate Date)
{
    Date.Year += 10;
 
    return Date;
}

stDate IncreaseDateByXDecades(stDate Date, short Decades)
{
    for (short i = 0; i < Decades; i++)
    {
        Date = IncreaseDateByOneDecades(Date);

    }
    return Date;
}

stDate IncreaseDateByOneDecadesFaster(stDate Date, short Decades)
{
    Date.Year += Decades * 10;

    return Date;
}

stDate IncreaseDateByOneCentury(stDate Date)
{
    Date.Year += 100;

    return Date;
}

stDate IncreaseDateByOneMillennium(stDate Date)
{
    Date.Year += 1000;

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

    Date = Adding_One_Day(Date);
    cout << "01-Adding one day is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = IncreaseDateByXDays(Date, 10);
    cout << "02-Adding 10 day is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = IncreaseDateByOneWeek(Date);
    cout << "03-Adding one week is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = IncreaseDateByXWeek(Date, 10);
    cout << "04-Adding 10 week is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = IncreaseDateByOneMonths(Date);
    cout << "05-Adding one month is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = IncreaseDateByXMonths(Date, 5);
    cout << "06-Adding 5 month is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = IncreaseDateByOneYear(Date);
    cout << "07-Adding one year is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = IncreaseDateByXYear(Date, 10);
    cout << "08-Adding 10 year is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = IncreaseDateByOneYearFaster(Date, 10);
    cout << "09-Adding 10 year (faster) is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = IncreaseDateByOneDecades(Date);
    cout << "10-Adding one Decade is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = IncreaseDateByXDecades(Date, 10);
    cout << "11-Adding 10 Decades is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;

    Date = IncreaseDateByOneDecadesFaster(Date, 10);
    cout << "12-Adding 10 Decades (faster) is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;


    Date = IncreaseDateByOneCentury(Date);
    cout << "13-Adding one Century is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;


    Date = IncreaseDateByOneMillennium(Date);
    cout << "14-Adding one Millennium is : " << Date.Day << " / " << Date.Month << " / " << Date.Year << endl;


    return 0;
}
