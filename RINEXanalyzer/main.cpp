/*
 * RINEX2NMEA.cpp
 *
 *  Created on: 2013/06/08
 *      Author: bun
 */
// ----------------------------------------------------------------------
// Copyright (c) 2013 Yamagata Fumihiro.
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the GNU Public License v2.0
// which accompanies this distribution, and is available at
// http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
// 
// Contributors:
//     Yamagata Fumihiro - initial API and implementation
// ----------------------------------------------------------------------

#include "stdafx.h"

#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

// Need for GetPot
#include <cstring>
// From http://getpot.sourceforge.net/
#include <GetPot>
#include "RINEX.h"

void print_simplehelp(const std::string targetname);
void print_help(const std::string targetname);

const static std::string ver = "0.01";

int main(int argc, char **argv)
{

	GetPot cl(argc, argv);

	if(cl.size() == 1)
	{
		print_simplehelp(cl[0]);
	}
	else if (cl.search(2, "--help", "-h"))
	{
		print_help(cl[0]);
	}
	else
	{
		// Do nothing
	}

  std::string input_filename = cl.follow("default-input.00", "-i");

  std::map<GPS_Time, ReceiverOutput> outdata;

  outdata.clear();

  RINEX_NavigationMessage nav_message(input_filename);

  nav_message.Read();

  RINEX_ObservationData obs_data(input_filename);


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
  NMEA0183 getnmea;
  std::multimap<GPS_Time, std::string> nmea0183 = getnmea.OutputNMEA0183(outdata);
  for(std::multimap<GPS_Time, std::string>::iterator it = nmea0183.begin(); it != nmea0183.end(); it++)
  {
	  std::cout << it->second;

  }


  return 0;
}


void print_simplehelp(const std::string targetname)
{
	std::cout << "RINEXanalyzer version " << ver << std::endl;
	std::cout << std::endl;
	std::cout << "usage: " << targetname << "[options] -i <infile> [outfile]" << std::endl;
	std::cout << std::endl;
	std::cout << "    [outfile] can be blank which means stdout." << std::endl;
	std::cout << std::endl;
	std::cout << "Try:" << std::endl;
	std::cout << "    \"" << targetname << " --help\"" << std::endl;
	std::cout << " or:" << std::endl;
	std::cout << "    \"" << targetname << " -h\"\t\tfor general usage information" << std::endl;

	exit(0);

}

void print_help(const std::string targetname)
{

	std::cout << "RINEXanalyzer version " << ver << std::endl;
	std::cout << std::endl;
	std::cout << "usage: " << targetname << "[options] -i <infile> [outfile]" << std::endl;
	std::cout << std::endl;
	std::cout << "    [outfile] can be blank which means stdout." << std::endl;
	std::cout << std::endl;
	std::cout << "OPTIONS:" << std::endl;
	std::cout << "    -n                       output NMEA0183 GPGGA, GPGSV and GPZDA sentences." << std::endl;
	std::cout << "                             (default)" << std::endl;
	std::cout << "    -r [<lat> <long> <hgt>]  output difference from average position or " << std::endl;
	std::cout << "                             [<lat> <long> <hgt>]." << std::endl;
	std::cout << "                             The output is UTC and difference in ENU Frame." << std::endl;
	std::cout << "                             -n and -r are exclusive." << std::endl;
	std::cout << "                             <lat> and <long> should be degree. " << std::endl;
	std::cout << "                             <hgt> should be meter." << std::endl;
	std::cout << "                             <lat> from -90.0000 to 90.0000." << std::endl;
	std::cout << "                             <long> from -180.0000 to 180.0000." << std::endl;
	std::cout << "    -m <mask>                elevation mask in calculation." << std::endl;
	std::cout << "                             <mask> should be degree." << std::endl;
	std::cout << "                             <mask> from 0.0000 to 90.0000." << std::endl;
	std::cout << "    -w                       using elevation weight in calculation." << std::endl;
	std::cout << "                             -m and -w are exclusive." << std::endl;

	exit(0);


	exit(0);
}
