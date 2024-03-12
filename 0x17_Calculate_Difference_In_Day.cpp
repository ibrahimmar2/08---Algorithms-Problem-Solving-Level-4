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



int DiffrenceDate(stDate Date1, stDate Date2)
{
    return (NumberOfDays(Date1.Day, Date1.Month, Date1.Year) - NumberOfDays(Date2.Day, Date2.Month, Date2.Year)) * -1;
}

int DiffrenceDateEndDay(stDate Date1, stDate Date2)
{
    return ((NumberOfDays(Date1.Day, Date1.Month, Date1.Year) - NumberOfDays(Date2.Day, Date2.Month, Date2.Year)) * -1) + 1;

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




    cout << "Diffrence is: " << DiffrenceDate(Date1, Date2) << " Day (s)." << endl;
    cout << "Diffrence (Including End Day) is: " << DiffrenceDateEndDay(Date1, Date2) << " Day (s)." << endl;


    return 0;
} 
