#include "airline_ticket.h"
#include "test_runner.h"
#include <algorithm>
#include <numeric>
#include <fstream>
using namespace std;

#define SORT_BY(field)                                          \
[](const AirlineTicket& lhs, const AirlineTicket& rhs) {        \
    return (lhs.field < rhs.field);                             \
}

bool operator <(const Date &date1, const Date &date2)
{
//    if (date1.year == date2.year)
//    {
//        if (date1.month == date2.month)
//            return date1.day < date2.day;
//        return date1.month < date2.month;
//    }
//    return date1.year < date2.year;
    return tie(date1.year, date1.month, date1.day) < tie(date2.year, date2.month, date2.day);
}

bool operator <(const Time &time1, const Time &time2)
{
    return tie(time1.hours, time1.minutes) < tie(time2.hours, time2.minutes);
}

bool operator == (const Time &time1, const Time &time2)
{
    if (time1.hours == time2.hours && time1.minutes == time2.minutes)
        return true;
    return false;
}
bool operator == (const Date &date1, const Date &date2)
{
    if (date1.year == date2.year && date1.month == date2.month && date1.month == date2.month)
        return true;
    return false;
}

ostream& operator << (ostream &os ,const Date &date)
{
    return os << date.year << "-" << date.month << "-" << date.day;
}
ostream& operator << (ostream &os ,const Time &time)
{
    return os << time.hours << ":" << time.minutes;
}
// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time

void TestSortBy() {
  vector<AirlineTicket> tixs = {
    {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
    {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
    {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
    {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
    {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
  };

  sort(begin(tixs), end(tixs), SORT_BY(price));
  ASSERT_EQUAL(tixs.front().price, 1200);
  ASSERT_EQUAL(tixs.back().price, 9000);

  sort(begin(tixs), end(tixs), SORT_BY(from));
  ASSERT_EQUAL(tixs.front().from, "AER");
  ASSERT_EQUAL(tixs.back().from, "VKO");

  sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
  ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
  ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSortBy);
}
