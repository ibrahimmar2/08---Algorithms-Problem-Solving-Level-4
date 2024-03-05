#include <iostream>

using namespace std;


struct sDate
{
    short Year;
    short Month;
    short Day;
};


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



sDate DateAddDays(short Days, sDate Date)
{

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


int AddDays()
{
    int AddDay;
    cout << "How many days to add? ";
    cin >> AddDay;
    return AddDay;
}

sDate ReadFullDate()
{
    sDate Date;  
    Date.Day = ReadDay(); 
    Date.Month = ReadMonth();  
    Date.Year = ReadYear(); 
    
    return Date;
}

int main()
{
    sDate Date = ReadFullDate();
    short Days = AddDays();
 
    Date = DateAddDays(Days, Date);
    cout << "Date for [" << Days << "] is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;
    return 0;
}

