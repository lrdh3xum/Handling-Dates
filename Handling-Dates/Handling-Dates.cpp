#include <iostream>
#include "Date.h"
#include <string>

using std::cout;
using std::endl;
using std::string;

Date::Date(int year, int month, int day)
    : m_year(year),
    m_month(month),
    m_day(day),
    m_weekDay(DayOfTheWeek_Unknown)
{}

Date::~Date()
{}

Date::Date(const Date& p)
    : m_year(p.m_year),
    m_month(p.m_month),
    m_day(p.m_day),
    m_weekDay(p.m_weekDay),
    m_holidays(p.m_holidays)
{}

Date& Date::operator=(const Date& p)
{
    if (&p != this)
    {
        m_day = p.m_day;
        m_month = p.m_month;
        m_year = p.m_year;
        m_weekDay = p.m_weekDay;
        m_holidays = p.m_holidays;
    }
    return *this;
}

bool Date::operator<(const Date& d) const
{
    if (m_year < d.m_year) return true;
    if (m_year == d.m_year && m_month < d.m_month) return true;
    if (m_year == d.m_year && m_month == d.m_month && m_day < d.m_day) return true;

    return false;
}

bool Date::operator==(const Date& d) { return d.m_day == m_day && d.m_month == m_month && d.m_year == m_year; }

void Date::setHolidays(const std::vector<Date>& days) { m_holidays = days; }

bool Date::isHoliday() { return std::find(m_holidays.begin(), m_holidays.end(), *this) != m_holidays.end(); }

std::string Date::month()
{
    switch (m_month)
    {
    case Month_January: return "January";
    case Month_Feburary: return "Feburary";
    case Month_March: return "March";
    case Month_April: return "April";
    case Month_May: return "May";
    case Month_June: return "June";
    case Month_July: return "Junly";
    case Month_August: return "August";
    case Month_September: return "September";
    case Month_October: return "October";
    case Month_November: return "November";
    case Month_December: return "December";
    default: throw std::runtime_error("unknown month");
    }
    return "";
}

#define self this

std::string Date::dayOfWeek()
{
    switch (this->dayOfTheWeek())
    {
    case DayOfTheWeek_Sunday: return "Sunday";
    case DayOfTheWeek_Monday: return "Monday";
    case DayOfTheWeek_Tuesday: return "Tuesday";
    case DayOfTheWeek_Wednesday: return "Wednesday";
    case DayOfTheWeek_Thursday: return "Thursday";
    case DayOfTheWeek_Friday: return "Friday";
    case DayOfTheWeek_Saturday: return "Saturday";
    }
}

void Date::addTradingDays(int numDays)
{
    while (!isTradingDay())
    {
        ++*this;
    }

    for (int i = 0; i < numDays; i++)
    {
        ++* this;
        while (!isTradingDay())
        {
            ++* this;
        }

    }
}

void Date::subtract(int numDays)
{
    for (int i = 0; i < numDays; i++)
    {
        --* this;
    }
}

void Date::subtractTradingDays(int numDays)
{
    while (!isTradingDay())
    {
        --* this;
    }

    for (int i = 0; i < numDays; i++)
    {
        --* this;
        while (!isTradingDay())
        {
            --* this;
        }
    }
}

int Date::dateDifference(const Date& date)
{
    Date d = *this;

    if (d < date)
    {
        int diff = 0;
        
        while (d < date)
        {
            ++d;
            ++diff;
        }
        return diff;
    }

    int diff = 0;
    while (date < d)
    {
        --d;
        --diff;
    }
    return diff;
}

int Date::tradingDateDifference(const Date& date)
{
    Date d = *this;

    if (d < date)
    {
        int diff = 0;
        while (!d.isTradingDay()) ++d;
        while (d < date)
        {
            ++d;
            ++diff;
            while (!d.isTradingDay()) ++d;
        }
        return diff;
    }

    int diff = 0;
    while (!d.isTradingDay()) --d;
    while (date < d)
    {
        --d;
        --diff;
        while(!d.isTradingDay()) --d;
    }
    return diff;
}

DayOfTheWeek Date::dayOfTheWeek()
{
    if (m_weekDay != DayOfTheWeek_Unknown) return m_weekDay;

    int day = 1;
    Date d(1900, 1, 1);
    for (;d < *this; ++d)
    {
        if (day == 6) day = 0;
        else day++;
    }
    m_weekDay = static_cast<DayOfTheWeek>(day);
    return m_weekDay;
}

bool Date::isWeekDay()
{
    DayOfTheWeek dayOfWeek = dayOfTheWeek();

    if (dayOfWeek == DayOfTheWeek_Sunday || dayOfWeek == DayOfTheWeek_Saturday)
    {
        return false;
    }
    return true;
}

int main()
{
    std::cout << "Hello World!\n";
}