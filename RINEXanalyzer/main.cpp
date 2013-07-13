/*
 * RINEX2NMEA.cpp
 *
 *  Created on: 2013/06/08
 *      Author: bun
 */

#include "stdafx.h"

#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

#include "RINEX.h"

int main(int argc, char **argv)
{
  if (argc == 0)
    {
      return 0;
    }
  else
    {
      // Do nothing
    }

  std::string filename = argv[1];

  std::map<GPS_Time, ReceiverOutput> outdata;

  outdata.clear();

  RINEX_NavigationMessage nav_message(filename);

  nav_message.Read();

  RINEX_ObservationData obs_data(filename);


  std::multimap<GPS_Time, PsudoRange> psuRange = obs_data.GetPsudoRange();

  std::map<int, PsudoRange> range;
  GPS_Time cur;

  std::multimap<GPS_Time, PsudoRange>::iterator it = psuRange.begin();
  std::pair<std::multimap<GPS_Time, PsudoRange>::iterator,
  std::multimap<GPS_Time, PsudoRange>::iterator> r_it = psuRange.equal_range(it->first);

  do
  {
          range.clear();


          for (std::multimap<GPS_Time, PsudoRange>::iterator its = r_it.first; its != r_it.second; its++)
          {
                  range.insert(std::pair<int, PsudoRange>((its->second).GetPRN(), its->second));
                  cur = its->first;

          }
          std::map <int, Ephemeris> ephem_map = nav_message.GetEphemeris(cur, -1, true);
          Calculate_Position cal(ephem_map, range, PsudoRange::CA, cur, nav_message.GetIon());

          ReceiverOutput position = cal.GetPosition();

          outdata.insert(std::pair<GPS_Time, ReceiverOutput>(position.GetTime(), position));

          ECEF_Frame origin(position.GetPosition());

          it = r_it.second;
          if (it != psuRange.end())
          {
                  r_it = psuRange.equal_range(it->first);
          }
          else
          {
                  break;
          }

  } while (it != psuRange.end());

  ECEF_Frame pos(0.0L, 0.0L, 0.0L);
  int i = 0;

  for(std::map<GPS_Time, ReceiverOutput>::iterator it = outdata.begin(); it != outdata.end(); it++)
    {
      i++;
      ECEF_Frame posA = it->second.GetPosition();
      pos = (i - 1.0L) / i * pos + 1.0L / i * posA;
    }

  for(std::map<GPS_Time, ReceiverOutput>::iterator it = outdata.begin(); it != outdata.end(); it++)
    {
      ENU_Frame enu_pos(it->second.GetPosition(), pos);
      tm tmbuf = (it->first).ToDate();
      std::cout << std::fixed << std::setw(4) << std::setfill('0') << tmbuf.tm_year + 1900 << "-";
      std::cout << std::fixed << std::setw(2) << std::setfill('0') << tmbuf.tm_mon + 1 << "-";
      std::cout << std::fixed << std::setw(2) << std::setfill('0') << tmbuf.tm_mday << " ";
      std::cout << std::fixed << std::setw(2) << std::setfill('0') << tmbuf.tm_hour << ":";
      std::cout << std::fixed << std::setw(2) << std::setfill('0') << tmbuf.tm_min << ":";
      std::cout << std::fixed << std::setw(2) << std::setfill('0') << tmbuf.tm_sec << " ";

			std::cout << std::fixed << enu_pos.GetE() << " ";
			std::cout << std::fixed << enu_pos.GetN() << " ";
			std::cout << std::fixed << enu_pos.GetU() << std::endl;

    }

  return 0;
}



