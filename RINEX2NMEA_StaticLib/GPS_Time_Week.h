/*
 * GPS_Time_Week.h
 *
 *  Created on: 2013/06/07
 *      Author: bun
 */

#ifndef GPS_TIME_WEEK_H_
#define GPS_TIME_WEEK_H_

#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>


class GPS_Time_Week {
private:
  int week;
  double second;

  static const long int Seconds_in_Day = 86400L;
  static const int Time_t_Base_Year = 1970;
  static const int GPS_Week_Origin = 315964800L;
  static const long double GPS_Epoch_JD = 2444244.5;
  static const long int Days_in_Week = 7L;
  static const long int Seconds_in_Hour = 3600L;
  static const long int Seconds_in_Minute = 60L;

  long double GetJulianDay(struct tm tmbuf);

public:
  GPS_Time_Week();
  GPS_Time_Week(int w, double sec);
  GPS_Time_Week(struct tm tmbuf, long int leap_second);
  ~GPS_Time_Week();

  struct tm ToDate();

  int GetWeek()
  {
    return week;
  };

  double GetSecond()
  {
    return second;
  };

};



#endif /* GPS_TIME_WEEK_H_ */
