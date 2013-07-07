/*
 * GPS_Time_Week.cpp
 *
 *  Created on: 2013/06/07
 *      Author: bun
 */
#include "GPS_Time.h"
#include <ctime>
#include <cmath>

GPS_Time::GPS_Time()
{
  week = 0;
  second = 0.0L;
  leap_second = 0;
}

GPS_Time::GPS_Time(int w = 0, long double sec = 0.0L, int leap_sec = 0)
{
  week = w;
  second = sec;
  leap_second = leap_sec;
}

GPS_Time::GPS_Time(tm tmbuf, long double sec = 0.0L, int leap_sec = 0)
{
	long double days;

	leap_second = leap_sec;

	days = GetJulianDay(tmbuf) - GPS_Epoch_JD;

	week = (int)(days / Days_in_Week);
	second = (days - week * Days_in_Week) * Seconds_in_Day + tmbuf.tm_hour * Seconds_in_Hour +
     tmbuf.tm_min * Seconds_in_Minute + tmbuf.tm_sec + sec;
 }

GPS_Time::GPS_Time(const GPS_Time &gpst)
{
	week = gpst.week;
	second = gpst.second;
	leap_second = gpst.leap_second;
}

GPS_Time::~GPS_Time()
{
  // Do nothing
}

tm GPS_Time::ToDate() const
{
  time_t t;

  t = (long) week * Days_in_Week * Seconds_in_Day + GPS_Week_Origin
     +(long)((second>0.0)?second+0.5:second-0.5) - leap_second;
  return *gmtime(&t);
}



long double GPS_Time::operator-(const GPS_Time &gpst) const
{
	return (week - gpst.week) * Days_in_Week * Seconds_in_Day + second - gpst.second;
}

GPS_Time &GPS_Time::operator=(const GPS_Time gpst)
{
	week = gpst.week;
	second = gpst.second;
	leap_second = gpst.leap_second;
	return *this;
}

bool GPS_Time::operator>(const GPS_Time &gpst) const
{
	return ((week - gpst.week) * Days_in_Week * Seconds_in_Day + second - gpst.second) > 0.0L;
}

bool GPS_Time::operator<(const GPS_Time &gpst) const
{
	return gpst > *this;
}

bool GPS_Time::operator>=(const GPS_Time &gpst) const
{
	return !(*this < gpst);
}

bool GPS_Time::operator<=(const GPS_Time &gpst) const
{
	return !((*this) > gpst);
}

bool GPS_Time::operator==(const GPS_Time &gpst) const
{
	return ((week == gpst.week) && (second == gpst.second));
}

bool GPS_Time::operator!=(const GPS_Time &gpst) const
{
	return !((*this) == gpst);
}

long double GPS_Time::GetJulianDay(tm tmbuf)
{
  int64_t y, m, a, b;

  if (tmbuf.tm_mon < 2)
    {
      y = tmbuf.tm_year + 1899;
      m = tmbuf.tm_mon + 13;
    }
  else
    {
      y = tmbuf.tm_year + 1900;
      m = tmbuf.tm_mon + 1;
    }

  a = (int64_t)(y / 100);
  b = (int64_t)(2 - a + (int64_t)(a / 4));

  return (long double)(floor(365.25L * y) + floor(30.6001 * (m + 1)) + tmbuf.tm_mday + 1720994.5L + b);

}

