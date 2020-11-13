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
        // to-do
    }
    return "";


}


int main()
{
    std::cout << "Hello World!\n";
}