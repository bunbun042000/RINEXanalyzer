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
 * GPS_Time.h
 *
 *  Created on: 2013/06/07
 *      Author: bun
 */

#ifndef GPS_TIME_H_
#define GPS_TIME_H_

#include <ctime>
#include <stdint.h>
#include <stdio.h>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <string>

namespace GPS_Time_const
{
	static const int Time_t_Base_Year = 1970;
	static const int GPS_Week_Origin = 315964800L;
	static const long double GPS_Epoch_JD = 2444244.5;
	static const long int Days_in_Week = 7L;
	static const long int Seconds_in_Minute = 60L;
}

class GPS_Time {
public:
	GPS_Time();
	GPS_Time(int w, long double sec, int leap_second = 0);
	GPS_Time(int year, int month, int day, int hour, int min, long double sec, int leapsec = 0);
	GPS_Time(const GPS_Time &gpst);
	virtual ~GPS_Time();

	tm ToDate() const;

	long double operator-(const GPS_Time &gpst) const;
	GPS_Time &operator=(const GPS_Time gpst);

	bool operator>(const GPS_Time &gpst) const;
	bool operator<(const GPS_Time &gpst) const;
	bool operator>=(const GPS_Time &gpst) const;
	bool operator<=(const GPS_Time &gpst) const;
	bool operator==(const GPS_Time &gpst) const;
	bool operator!=(const GPS_Time &gpst) const;

	std::string nmea_time_str() const;
	std::string ISO8601_day() const;
	std::string ISO8601_time() const;

	int GetWeek() const
	{
		return week;
	};

	long double GetSecond() const
	{
		return second;
	};

	int GetLeapSecond() const
	{
		return leap_second;
	};

	static const long int Seconds_in_Hour = 3600L;
	static const long int Seconds_in_week = 604800L;
	static const long int Seconds_in_Day = 86400L;

private:
	int week;
	long double second;
	int leap_second;

	long double GetJulianDay(int year, int month, int day);
	int CalculateLeapSecond();

};

#endif /* GPS_TIME_H_ */
