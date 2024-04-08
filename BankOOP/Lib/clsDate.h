#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>
using namespace std;

class clsDate
{
private:

    short Year = 1;
    short Month = 1;
    short Day = 1900;

    vector<string> split_string(string date, string delim)
    {
        size_t pos = 0;
        string word = "";
        vector <string> vstring;
        while ((pos = date.find(delim)) != std::string::npos)
        {
            word = date.substr(0, pos);
            if (word != "")
                vstring.push_back(word);
            date.erase(0, pos + delim.length());
        }
        if (date != "")
            vstring.push_back(date);
        return vstring;
    }

public:

    clsDate() {

        time_t t = time(0);
        tm* ltm = localtime(&t);

        this->Year = ltm->tm_year + 1900;
        this->Month = ltm->tm_mon + 1;
        this->Day = ltm->tm_mday;

    }

    clsDate(string Date) {
        vector <string> vstring = split_string(Date, "/");
        this->Day = stoi(vstring[0]);
        this->Month = stoi(vstring[1]);
        this->Year = stoi(vstring[2]);
    }

    clsDate(short Day, short Month, short Year) {

        this->Year = Year;
        this->Month = Month;
        this->Day = Day;
    }

    clsDate(short DayOrder, short Year) {
        this->Year = Year;

    }

    void SetDay(short Day) {
        this->Day = Day;
    }

    short GetDay() {
        return Day;
    }

    __declspec(property(get = GetDay, put = SetDay)) short Day;
    void SetMonth(short Month) {
        this->Month = Month;
    }

    short GetMonth() {
        return Month;
    }

    __declspec(property(get = GetMonth, put = SetMonth)) short Month;

    void SetYear(short Year) {
        this->Year = Year;
    }

    short GetYear() {
        return Year;
    }

    __declspec(property(get = GetYear, put = SetYear)) short Year;

    static bool IsLeapYear(short Year)
    {
        return ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0);
    }

    bool IsLeapYear() {
        return IsLeapYear(this->Year);
    }
    static short NumberOfDaysInYear(short Year)
    {
        return (IsLeapYear(Year) ? 366 : 365);
    }

    short NumberOfDaysInYear() {
        return (NumberOfDaysInYear(this->Year));
    }

    static short NumberOfHoursInYear(short Year)
    {
        return (NumberOfDaysInYear(Year) * 24);
    }

    short NumberOfHoursInYear() {
        return (NumberOfDaysInYear(this->Year) * 24);
    }

    static int NumberOfMinutesInYear(short Year)
    {
        return (NumberOfHoursInYear(Year) * 60);
    }

    int NumberOfMinutesInYear() {
        return (NumberOfHoursInYear(this->Year) * 60);
    }

    static int NumberOfSecondsInYear(short Year)
    {
        return (NumberOfMinutesInYear(Year) * 60);
    }

    int NumberOfSecondsInYear() {
        return (NumberOfMinutesInYear(this->Year) * 60);
    }

    static void PrintYearInfo(short Year)
    {
        cout << "\nNumber of days in Year    [" << Year << "] is " << NumberOfDaysInYear(Year);
        cout << "\nNumber of hours in Year   [" << Year << "] is " << NumberOfHoursInYear(Year);
        cout << "\nNumber of minutes in Year [" << Year << "] is " << NumberOfMinutesInYear(Year);
        cout << "\nNumber of seconds in Year [" << Year << "] is " << NumberOfSecondsInYear(Year);
    }

    void PrintYearInfo() {
        PrintYearInfo(this->Year);
    }

    static short MonthDays(short Month, short Year)
    {
        if (Month < 1 || Month > 12)
            return 0;
        short arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return (IsLeapYear(Year) && Month == 2 ? 29 : arr[Month]);
    }

    short MonthDays() {
        return MonthDays(this->Month, this->Year);
    }

    static short NumberOfDaysInMonth(short Year, short Month)
    {
        return ((IsLeapYear(Year) && Month == 2) ? 29 : MonthDays(Month, Year));
    }

    short NumberOfDaysInMonth() {
        return NumberOfDaysInMonth(this->Year, this->Month);
    }

    static short NumberOfHoursInMonth(short Year, short Month)
    {
        return (NumberOfDaysInMonth(Year, Month) * 24);
    }

    short NumberOfHoursInMonth() {
        return (NumberOfHoursInMonth(this->Year, this->Month));
    }

    static int NumberOfMinutesInMonth(short Year, short Month)
    {
        return (NumberOfHoursInMonth(Year, Month) * 60);
    }

    int NumberOfMinutesInMonth() {
        return NumberOfMinutesInMonth(this->Year, this->Month);
    }

    static int NumberOfSecondsInMonth(short Year, short Month)
    {
        return (NumberOfMinutesInMonth(Year, Month) * 60);
    }

    int NumberOfSecondsInMonth() {
        return (NumberOfSecondsInMonth(this->Year, this->Month));
    }

    static void PrintMonthInfo(short Year, short Month)
    {
        cout << "\nNumber of days in Year    [" << Year << "] is " << NumberOfDaysInMonth(Year, Month);
        cout << "\nNumber of hours in Year   [" << Year << "] is " << NumberOfHoursInMonth(Year, Month);
        cout << "\nNumber of minutes in Year [" << Year << "] is " << NumberOfMinutesInMonth(Year, Month);
        cout << "\nNumber of seconds in Year [" << Year << "] is " << NumberOfSecondsInMonth(Year, Month);
    }

    void PrintMonthInfo() {
        PrintMonthInfo(this->Year, this->Month);
    }

    static bool IsValidDate(clsDate date) {
        return (date.Day > 0 && date.Day < NumberOfDaysInMonth(date.Year, date.Month)) && (date.Month > 0 && date.Month < 13);
    }

    bool IsValidDate() {
        return IsValidDate(*this);
    }

    static string DateToString(clsDate Date)
    {
        return  to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
    }

    string DateToString()
    {
        return  DateToString(*this);
    }

    static string DayName(short D)
    {
        switch (D)
        {
        case 0:
            return "Sunday";
        case 1:
            return "Monday";
        case 2:
            return "Tuesday";
        case 3:
            return "Wednesday";
        case 4:
            return "Thursday";
        case 5:
            return "Friday";
        case 6:
[O            return "Saturday";
        }
    }

    string DayName() {
        return DayName(DayOrder(*this));
    }

    static string MonthName(short M)
    {
        switch (M)
        {
        case 1:
            return "Jan";
        case 2:
            return "Feb";
        case 3:
            return "Mar";
        case 4:
            return "Apr";
        case 5:
            return "May";
        case 6:
            return "Jun";
        case 7:
            return "Jul";
        case 8:
            return "Aug";
        case 9:
            return "Sep";
        case 10:
            return "Oct";
        case 11:
            return "Nov";
        case 12:
            return "Dec";
        }
    }

    string MonthName() {
        return MonthName(this->Month);
    }

    static short DayOrder(short Year, short Month, short Day)
    {
        short a = (14 - Month) / 12;
        short y = Year - a;
        short m = Month + (12 * a) - 2;
        short d = (Day + y + (y / 4) - (y / 100) + y / 400 + ((31 * m) / 12)) % 7;
        return d;
    }

    static short DayOrder(clsDate Date)
    {
        return (DayOrder(Date.Year, Date.Month, Date.Day));
    }

    short DayOrder() {
        return DayOrder(*this);
    }

    static void Print(clsDate Date) {
        cout << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
    }

    void Print() {
        Print(*this);
    }

    static void PrintMonthCalendar(short Year, short Month)
    {
        cout << "\n________________" << MonthName(Month) << "________________\n\n";
        cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";
        short current = DayOrder(Year, Month, 1);
        short NumberOfDays = NumberOfDaysInMonth(Year, Month);
        short i;
        for (i = 0; i < current; i++)
        {
            cout << "     ";
        }
        for (short j = 1; j <= NumberOfDays; j++)
        {
            printf("%5d", j);
            if (++i == 7)
            {
                i = 0;
                cout << "\n";
            }
        }
        cout << "\n__________________________________\n";
    }

    void PrintMonthCalendar() {
        PrintMonthCalendar(this->Year, this->Month);
    }

    static void PrintYearCalendar(short Year)
    {
        cout << "\n__________________________________\n";
        cout << "\n__________" << "Calendar - " << Year << "_________\n\n";
        cout << "\n__________________________________\n";
        for (short j = 1; j <= 12; j++)
        {
            PrintMonthCalendar(Year, j);
        }
    }

    void PrintYearCalendar() {
        PrintYearCalendar(this->Year);
    }

    static short NumberOfDaysFromTheBeginningOfYear(short Year, short Month, short Day)
    {
        short n_days = 0;
        for (short j = 1; j < Month; j++)
        {
            n_days += NumberOfDaysInMonth(Year, j);
        }
        n_days += Day;
        return (n_days);
    }

    short NumberOfDaysFromTheBeginningOfYear() {
        return NumberOfDaysFromTheBeginningOfYear(this->Year, this->Month, this->Day);
    }

    static clsDate DateFromDayOrderInYear(short Year, short DayOrder)
    {
        clsDate Date;
        Date.Year = Year;
        short current_month;
        for (current_month = 1; current_month <= 12; current_month++)
        {
            if (DayOrder <= NumberOfDaysInMonth(Year, current_month))
                break;
            DayOrder -= NumberOfDaysInMonth(Year, current_month);
        }
        Date.Month = current_month;
        Date.Day = DayOrder;
        return Date;
    }

    clsDate DateFromDayOrderInYear(short DayOrder) {
        return DateFromDayOrderInYear(this->Year, DayOrder);
    }

    static clsDate FutureDateAfterAddingDays(short Year, short Month, short Day, short Added)
    {
        short still_days_in_year = 0;
        if (Added > (still_days_in_year = NumberOfDaysInYear(Year) - NumberOfDaysFromTheBeginningOfYear(Year, Month, Day)))
        {
            Added -= still_days_in_year;
            Year++;
        }
        else
        {
            return(DateFromDayOrderInYear(Year, NumberOfDaysFromTheBeginningOfYear(Year, Month, Day) + Added));
        }
        while (Added > (still_days_in_year = NumberOfDaysInYear(Year)))
        {
            Added -= still_days_in_year;
            Year++;
        }
        return (DateFromDayOrderInYear(Year, Added));
    }

    clsDate FutureDateAfterAddingDays(short Added) {
        return FutureDateAfterAddingDays(this->Year, this->Month, this->Day, Added);
    }

    static clsDate GetSystemDate() {
        clsDate CurrentDate;
        time_t t = time(0);
        tm* ltm = localtime(&t);

        CurrentDate.Year = ltm->tm_year + 1900;
        CurrentDate.Month = ltm->tm_mon + 1;
        CurrentDate.Day = ltm->tm_mday;
        return CurrentDate;
    }

    static string GetSystemDateTimeString()
    {
        //system datetime string
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day, Month, Year, Hour, Minute, Second;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;

        return (to_string(Day) + "/" + to_string(Month) + "/"
            + to_string(Year) + " - "
            + to_string(Hour) + ":" + to_string(Minute)
            + ":" + to_string(Second));

    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {
        if (Date1.Year < Date2.Year)
            return 1;
        else
        {
            if (Date1.Month < Date2.Year)
                return 1;
            else
            {
                if (Date1.Day < Date2.Day)
                    return 1;
                else
                    return 0;
            }
        }
    }

    bool IsDateBeforeDate2(clsDate Date2) {
        return IsDate1BeforeDate2(*this, Date2);
    }

    static bool IsDate1EqualToDate2(clsDate Date1, clsDate Date2) {
        return (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day);
    }

    bool IsDateEqualToDate2(clsDate Date2)
    {
        return IsDate1EqualToDate2(*this, Date2);
    }

    static bool IsLastDayInMonth(clsDate Date)
    {
        return (Date.Day == NumberOfDaysInMonth(Date.Year, Date.Month));
    }

    bool IsLastDayInMonth() {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }

    bool IsLastMonthInYear() {
        return IsLastMonthInYear(this->Month);
    }

    static void IncreaseDateByOneDay(clsDate& Date)
    {
        Date.
            Day++;
        if (Date.Day > NumberOfDaysInMonth(Date.Year, Date.Month))
        {
            Date.Day = 1;
            Date.Month++;
            if (Date.Month > 12)
            {
                Date.Month = 1;
                Date.Year++;
            }
        }
    }

    void IncreaseDateByOneDay() {
        IncreaseDateByOneDay(*this);
    }

    static short DifferenceBetweenTwoDates(clsDate Date1, clsDate Date2, bool EndDayIncluded = false)
    {
        short diff = 0;
        if (IsDate1BeforeDate2(Date1, Date2))
        {
            while (!IsDate1EqualToDate2(Date1, Date2))
            {
                diff++;
                IncreaseDateByOneDay(Date1);
            }
            return (EndDayIncluded ? ++diff : diff);
        }
        else if (IsDate1EqualToDate2(Date2, Date1))
        {
            while (!IsDate1EqualToDate2(Date1, Date2))
            {
                diff++;
                IncreaseDateByOneDay(Date2);
            }
            return (EndDayIncluded ? -(++diff) : -diff);
        }
        else
            return 0;
    }

    short DifferenceBetweenDateAndDate2(clsDate Date2, bool EndDayIncluded = false) {
        return DifferenceBetweenTwoDates(*this, Date2, EndDayIncluded);
    }

    static short AgeInDays(clsDate BirthDate)
    {
        clsDate current_date;
        time_t t = time(0);
        tm* ltm = localtime(&t);

        current_date.Year = ltm->tm_year + 1900;
        current_date.Month = ltm->tm_mon + 1;
        current_date.Day = ltm->tm_mday;
        return (DifferenceBetweenTwoDates(BirthDate, current_date));
    }

    static void IncreaseDateByXDays(clsDate& date, short X)
    {
        for (short i = 0; i < X; i++)
            IncreaseDateByOneDay(date);

    }

    void IncreaseDateByXDays(short X) {
        IncreaseDateByXDays(*this, X);
    }

    static void IncreaseDateByOneWeek(clsDate& date)
    {
        for (short i = 0; i < 7; i++)
            IncreaseDateByOneDay(date);

    }

    void IncreaseDateByOneWeek() {
        IncreaseDateByOneWeek(*this);
    }

    static void  IncreaseDateByXWeeks(clsDate& date, short X)
    {
        for (short i = 0; i < X; i++)
            IncreaseDateByOneWeek(date);

    }

    void IncreaseDateByXWeeks(short X) {
        IncreaseDateByXWeeks(*this, X);
    }

    static void IncreaseDateByOneMonth(clsDate& date)
    {
        if (IsLastMonthInYear(date.Month))
        {
            date.Month = 1;
            date.Year++;
        }
        else
            date.Month++;
        short number_of_days = NumberOfDaysInMonth(date.Year, date.Month);
        if (date.Day > number_of_days)
            date.Day = number_of_days;

    }

    void IncreaseDateByOneMonth() {
        IncreaseDateByOneMonth(*this);
    }

    static void IncreaseDateByXMonth(clsDate& date, short X)
    {
        for (short i = 0; i < X; i++)
            IncreaseDateByOneMonth(date);

    }

    void IncreaseDateByXMonth(short X) {
        IncreaseDateByXMonth(*this, X);
    }

    static void IncreaseDateByXYears(clsDate& date, short X)
    {
        date.Year += X;
    }

    void IncreaseDateByXYears(short X) {
        IncreaseDateByXYears(*this, X);
    }

    static void IncreaseDateByOneDecade(clsDate& date)
    {
        date.Year += 10;
    }

    void IncreaseDateByOneDecade() {
        IncreaseDateByOneDecade(*this);
    }

    static void IncreaseDateByXDecades(clsDate& date, short X)
    {
        date.Year += (X * 10);
    }

    void IncreaseDateByXDecades(short X) {
        IncreaseDateByXDecades(*this, X);
    }

    static void IncreaseDateByOneCentury(clsDate& date)
    {
        date.Year += 100;
    }

    void IncreaseDateByOneCentury() {
        IncreaseDateByOneCentury(*this);
    }

    static bool IsFirstDayOnMonth(short Day) {
        return Day == 1;
    }

    bool IsFirstDayOnMonth() {
        return IsFirstDayOnMonth(this->Day);
    }

    static void DecreaseDateByOneDay(clsDate& date)
    {
        if (IsFirstDayOnMonth(date.Day))
        {
            if (date.Month == 1)
            {
                date.Day = 31;
                date.Month = 12;
                date.Year--;
                return;
            }
            date.Month--;
            date.Day = NumberOfDaysInMonth(date.Year, date.Month);
            return;
        }
        date.Day--;
        return;
    }

    static void DecreaseDateByXDays(clsDate& date, short X)
    {
        for (short i = 0; i < X; i++)
            DecreaseDateByOneDay(date);

    }

    void DecreaseDateByXDays(short X)
    {
        for (short i = 0; i < X; i++)
            DecreaseDateByOneDay(*this);

    }

    static void DecreaseDateByOneWeek(clsDate& date)
    {
        DecreaseDateByXDays(date, 7);
    }

    void DecreaseDateByOneWeek() {
        DecreaseDateByXDays(*this, 7);
    }

    static void DecreaseDateByOneMonth(clsDate& date)
    {
        if (date.Month == 1)
        {
            date.Month = 12;
            date.Year--;
            return;
        }
        if (IsLastDayInMonth(date))
        {
            date.Month--;
            date.Day = NumberOfDaysInMonth(date.Year, date.Month);
            return;
        }
        date.Month--;
        return;
    }

    void DecreaseDateByOneMonth() {
        DecreaseDateByOneMonth(*this);
    }

    static void DecreaseDateByXMonths(clsDate& date, short X)
    {
        for (short i = 0; i < X; i++)
            DecreaseDateByOneMonth(date);

    }

    void DecreaseDateByXMonths(short X) {
        DecreaseDateByXMonths(*this, X);
    }

    static void DecreaseDateByOneYear(clsDate& date)
    {
        DecreaseDateByXMonths(date, 12);
    }

    void DecreaseDateByOneYear()
    {
        DecreaseDateByXMonths(*this, 12);
    }

    static void DecreaseDateByXYears(clsDate& date, short X)
    {
        date.Year -= X;
    }

    void DecreaseDateByXYears(short X)
    {
        DecreaseDateByXYears(*this, X);
    }

    static void DecreaseDateByOneDecade(clsDate& date)
    {
        date.Year -= 10;
    }

    void DecreaseDateByOneDecade() {
        DecreaseDateByOneDecade(*this);
    }

    static void DecreaseDateByXDecade(clsDate& date, short X)
    {
        date.Year -= 10 * X;

    }

    void DecreaseDateByXDecade(short X) {
        DecreaseDateByXDecade(*this, X);
    }

    static void DecreaseDateByOneCentury(clsDate& date)
    {
        date.Year -= 100;

    }

    void DecreaseDateByOneCentury() {
        DecreaseDateByOneCentury(*this);
    }

    static bool IsEndOfWeek(clsDate date)
    {
        return (DayOrder(date) == 6);
    }

    bool IsEndOfWeek()
    {
        return (IsEndOfWeek(*this));
    }

    static bool IsWeekEnd(clsDate date)
    {
        short d_order = DayOrder(date);
        return (d_order == 5 || d_order == 6);
    }

    bool IsWeekEnd()
    {
        return (IsWeekEnd(*this));
    }

    static bool IsBusinessDay(clsDate date)
    {
        return (!IsWeekEnd(date));
    }

    static short DaysUntilEndOfWeek(clsDate date)
    {
        return (6 - DayOrder(date));
    }

    short DaysUntilEndOfWeek()
    {
        return (DaysUntilEndOfWeek(*this));
    }

    static short DaysUntilEndOfMonth(clsDate date)
    {
        return (NumberOfDaysInMonth(date.Year, date.Month) - date.Day + 1);
    }

    short DaysUntilEndOfMonth()
    {
        return (DaysUntilEndOfMonth(*this));
    }

    static short DaysUntilEndOfYear(clsDate  date)
    {
        short year_days = (IsLeapYear(date.Year) ? 366 : 365);
        return (year_days - NumberOfDaysFromTheBeginningOfYear(date.Year, date.Month, date.Day) + 1);
    }

    short DaysUntilEndOfYear()
    {
        return (DaysUntilEndOfYear(*this));
    }

    static short ActualVacationDays(clsDate date_1, clsDate date_2)
    {
        short vacation_ds = 0;
        if (IsDate1BeforeDate2(date_1, date_2))
        {
            while (!IsDate1EqualToDate2(date_1, date_2))
            {
                if (IsBusinessDay(date_1))
                    vacation_ds++;
                IncreaseDateByOneDay(date_1);
            }
        }
        else
            cout << "Please enter a valid date! (date2 should be bigger than date1!)\n";
        return (vacation_ds);
    }

    static clsDate VacationReturnDate(clsDate dateFrom, short vacation_days)
    {
        while (vacation_days != 0)
        {
            if (IsBusinessDay(dateFrom))
                vacation_days--;

            IncreaseDateByOneDay(dateFrom);
        }
        return (dateFrom);
    }

    static void SwapDates(clsDate& date1, clsDate& date2) {
        clsDate temp = date1;
        date1 = date2;
        date2 = temp;
    }

    static bool IsDate1AfterDate2(clsDate date1, clsDate date2) {
        return (!IsDate1BeforeDate2(date1, date2) && !IsDate1EqualToDate2(date1, date2));
    }

    bool IsDateAfterDate2(clsDate date2) {
        return (IsDate1AfterDate2(*this, date2));
    }

    enum enDateCompare { Before = -1, Equal = 0, After = 1 };

    static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return enDateCompare::Before;

        if (IsDate1EqualToDate2(Date1, Date2))
            return enDateCompare::Equal;

        /* if (IsDate1AfterDate2(Date1,Date2))
             return enDateCompare::After;*/

             //this is faster
        return enDateCompare::After;

    }

    enDateCompare CompareDates(clsDate Date2)
    {
        return CompareDates(*this, Date2);
    }

};


