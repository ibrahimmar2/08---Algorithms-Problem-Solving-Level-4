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



bool CheckDate(stDate Date1, stDate Date2)
{
    return  (Date1.Year == Date2.Year) ? (Date1.Month == Date2.Month ? Date1.Day == Date2.Day : true) : false;
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

    if (CheckDate(Date1, Date2))
        cout << "Yes, Date1 is Equal Date2." << endl;
    else
        cout << "No, Date1 is Not Equal Date2." << endl;


    return 0;
}
