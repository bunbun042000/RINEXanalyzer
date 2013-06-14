/*
 * GPS_Time_Week.cpp
 *
 *  Created on: 2013/06/07
 *      Author: bun
 */
#include "GPS_Time_Week.h"
#include <time.h>
#include <math.h>

GPS_Time_Week::GPS_Time_Week()
{
  week = 0;
  second = 0.0;
}

GPS_Time_Week::GPS_Time_Week(int w, double sec)
{
  week = w;
  second = sec;
}

GPS_Time_Week::  GPS_Time_Week(struct tm tmbuf, long int leap_second)
{
 long double days;

 days = GetJulianDay(tmbuf) - GPS_Epoch_JD;

 week = (int)(days / Days_in_Week);
 second = (days - week * Days_in_Week) * Seconds_in_Day + tmbuf.tm_hour * Seconds_in_Hour +
     tmbuf.tm_min * Seconds_in_Minute + tmbuf.tm_sec + leap_second;
}

GPS_Time_Week::~GPS_Time_Week()
{
  // Do nothing
}

struct tm GPS_Time_Week::ToDate()
{
  time_t t;

  t = (long) week * Days_in_Week * Seconds_in_Day + GPS_Week_Origin
     +(long)((second>0.0)?second+0.5:second-0.5);
  return *gmtime(&t);
}


//time_t GPS_Time_Week::mktime2(tm tmbuf)
//{
//	return 0;
//}

long double GPS_Time_Week::GetJulianDay(tm tmbuf)
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

  return (long double)(floor(365.25 * y) + floor(30.6001 * (m + 1)) + tmbuf.tm_mday + 1720994.5 + b);

}
