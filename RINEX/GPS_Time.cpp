//----------------------------------------------------------------------
//Copyright (c) 2013 Yamagata Fumihiro.
//All rights reserved. This program and the accompanying materials
//are made available under the terms of the GNU Lesser Public License v2.1
//which accompanies this distribution, and is available at
//http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
//
//Contributors:
//    Yamagata Fumihiro - initial API and implementation
//----------------------------------------------------------------------
/*
 * GPS_Time_Week.cpp
 *
 *  Created on: 2013/06/07
 *      Author: bun
 */

#define _CRT_SECURE_NO_WARNINGS

#include "GPS_Time.h"
#include <ctime>
#include <cmath>

GPS_Time::GPS_Time()
{
  week = 0;
  second = 0.0L;
  leap_second = GPS_Time_const::leap_sec_base;
}

GPS_Time::GPS_Time(int w, long double sec, int leapsec)
{
  week = w;
  second = sec;
	if (leapsec == GPS_Time_const::leap_sec_base)
	{
		leap_second = CalculateLeapSecond();
	}
	else
	{
		leap_second = leapsec;
	}

}


GPS_Time::GPS_Time(int year, int month, int day, int hour, int min, long double sec, int leapsec)
{
	long double days;

	days = GetJulianDay(year, month, day) - GPS_Time_const::GPS_Epoch_JD;
	week = (int)(days / GPS_Time_const::Days_in_Week);
	second = (days - week * GPS_Time_const::Days_in_Week) * Seconds_in_Day + hour * Seconds_in_Hour +
     min * GPS_Time_const::Seconds_in_Minute + sec;

	if (leapsec == GPS_Time_const::leap_sec_base)
	{
		leap_second = CalculateLeapSecond();
	}
	else
	{
		leap_second = leapsec;
	}

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

  t = (time_t) week * GPS_Time_const::Days_in_Week * Seconds_in_Day + GPS_Time_const::GPS_Week_Origin
     +(time_t)((second>0.0)?second+0.5:second-0.5) - leap_second;
  return *gmtime(&t);
}



long double GPS_Time::operator-(const GPS_Time &gpst) const
{
	return (week - gpst.week) * GPS_Time_const::Days_in_Week * Seconds_in_Day + second - gpst.second;
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
	return ((week - gpst.week) * GPS_Time_const::Days_in_Week * Seconds_in_Day + second - gpst.second) > 0.0L;
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

std::string GPS_Time::nmea_time_str() const
{
	std::ostringstream stream;

	tm tmbuf = ToDate();
	stream << std::setw(2) << std::setfill('0');
	stream << tmbuf.tm_hour;
	stream << std::setw(2) << std::setfill('0');
	stream << tmbuf.tm_min;
	stream << std::setw(6) << std::setfill('0') << std::fixed;
	stream << std::setprecision(3);
	double temp1 = (double)(second - leap_second);
	double sec = fmod(temp1, 60);
	stream << sec;

	return stream.str();

}
std::string GPS_Time::ISO8601_day() const
{
	std::ostringstream stream;
	tm tmbuf = ToDate();
	stream << std::fixed << std::setw(4) << std::setfill('0') << tmbuf.tm_year + 1900 << '-';
	stream << std::fixed << std::setw(2) << std::setfill('0') << tmbuf.tm_mon + 1 << '-';
	stream << std::fixed << std::setw(2) << std::setfill('0') << tmbuf.tm_mday;

	return stream.str();

}
std::string GPS_Time::ISO8601_time() const
{
	std::ostringstream stream;
	tm tmbuf = ToDate();
	stream << std::fixed << std::setw(2) << std::setfill('0') << tmbuf.tm_hour << ':';
	stream << std::fixed << std::setw(2) << std::setfill('0') << tmbuf.tm_min << ':';
	stream << std::fixed << std::setw(2) << std::setfill('0') << tmbuf.tm_sec;

	return stream.str();

}


long double GPS_Time::GetJulianDay(int year, int month, int day)
{
  int64_t y, m, a, b;

  if (month < 3)
    {
      y = year - 1;
      m = month + 12;
    }
  else
    {
      y = year;
      m = month;
    }

  a = (int64_t)(y / 100);
  b = (int64_t)(2 - a + (int64_t)(a / 4));

  return (long double)(floor(365.25L * y) + floor(30.6001 * (m + 1)) + day + 1720994.5L + b);

}

int GPS_Time::CalculateLeapSecond()
{
	int leapsec = 0;

	if(*this < GPS_Time(1981, 7, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(1982, 7, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(1983, 7, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(1985, 7, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(1988, 1, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(1990, 1, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(1991, 1, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(1992, 7, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(1993, 7, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(1994, 7, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(1996, 1, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(1997, 7, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(1999, 1, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(2006, 1, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(2009, 1, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	if(*this < GPS_Time(2012, 7, 1, 0, 0, 0.0L + leapsec, leapsec))
	{
		return leapsec;
	}
	else
	{
		leapsec++;
	}

	return leapsec;
}
