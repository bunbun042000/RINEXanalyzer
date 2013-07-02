/*
 * GPS_Time.h
 *
 *  Created on: 2013/06/07
 *      Author: bun
 */

#ifndef GPS_TIME_H_
#define GPS_TIME_H_

#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>


class GPS_Time {
private:
  int week;
  long double second;
  int leap_second;

  static const int Time_t_Base_Year = 1970;
  static const int GPS_Week_Origin = 315964800L;
  static const long double GPS_Epoch_JD = 2444244.5;
  static const long int Days_in_Week = 7L;
  static const long int Seconds_in_Minute = 60L;

  long double GetJulianDay(tm tmbuf);

public:
  GPS_Time();
  GPS_Time(int w, long double sec, int leap_second);
  GPS_Time(tm tmbuf, long double sec, int leap_seconds);
  GPS_Time(const GPS_Time &gpst);
  ~GPS_Time();

  tm ToDate();

  long double operator-(const GPS_Time gpst);

  int GetWeek()
  {
    return week;
  };

  long double GetSecond()
  {
    return second;
  };

  int GetLeapSecond()
  {
	  return leap_second;
  };

  static const long int Seconds_in_Hour = 3600L;
  static const long int Seconds_in_week = 604800L;
  static const long int Seconds_in_Day = 86400L;

};

#endif /* GPS_TIME_H_ */
