/*
 * RINEX_NavigationMessage.cpp
 *
 *  Created on: 2013/06/22
 *      Author: bun
 */

#include "RINEX_NavigationMessage.h"
#include <iostream>
#include <ctime>

RINEX_NavigationMessage::RINEX_NavigationMessage(std::string fname = "")
{
	filename = fname;
	week = -1;

	Ionosphere_parameterA[A0] = 0.0L;
	Ionosphere_parameterA[A1] = 0.0L;
	Ionosphere_parameterA[A2] = 0.0L;
	Ionosphere_parameterA[A3] = 0.0L;

	Ionosphere_parameterB[B0] = 0.0L;
	Ionosphere_parameterB[B1] = 0.0L;
	Ionosphere_parameterB[B2] = 0.0L;
	Ionosphere_parameterB[B3] = 0.0L;


}

RINEX_NavigationMessage::RINEX_NavigationMessage(const RINEX_NavigationMessage &nRIN)
{
	filename = nRIN.filename;
	ephem_map = nRIN.ephem_map;
	week = nRIN.week;

	Ionosphere_parameterA = nRIN.Ionosphere_parameterA;
	Ionosphere_parameterB = nRIN.Ionosphere_parameterB;

}

RINEX_NavigationMessage::~RINEX_NavigationMessage()
{
	filename = "";
	ephem_map.clear();
	week = -1;

	Ionosphere_parameterA.clear();
	Ionosphere_parameterB.clear();

}

bool RINEX_NavigationMessage::Read()
{
	int leap_second = 0;

	std::ifstream ifs(filename.c_str());
	std::string buf;

	if (ifs == 0)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	if (false == ReadHeader(ifs, leap_second))
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	if (false == ReadBody(ifs, leap_second))
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	return true;

}

void RINEX_NavigationMessage::SetFileName(std::string fname)
{
	filename = fname;
}

std::map<int, Ephemeris> RINEX_NavigationMessage::GetEphemeris(GPS_Time current_gpst, const int IODE)
{

	if(ephem_map.empty())
	{
		ephemeris_m.clear();
		return ephemeris_m;
	}
	else
	{
		// Do following procedure
	}

	std::multimap<int, Ephemeris>::iterator it = ephem_map.begin();
	std::pair<std::multimap<int, Ephemeris>::iterator,
	std::multimap<int, Ephemeris>::iterator> range = ephem_map.equal_range(it->first);

	do
	{
		Ephemeris current_Ephem;
		bool exist = false;
		std::map<int, Ephemeris>::iterator candidator = range.first;

		for (std::multimap<int, Ephemeris>::iterator its = range.first; its != range.second; its++)
		{

			if (((its->second).GetTot() - (candidator->second).GetTot() >= 0) && (current_gpst - (its->second).GetTot() >= 0))
			{
				long double freshness = its->second.GetData(Ephemeris::FIT) * GPS_Time::Seconds_in_Hour / 2.0;

				if (freshness < 1.0e-10 || freshness < Ephemeris_Default_Freshness)
				{
					freshness = Ephemeris_Default_Freshness;
				}
				else
				{
					// Do nothing
				}

				if (fabs((its->second).GetToc() - current_gpst) > freshness)
				{
					continue;
				}
				else
				{
					if (IODE >= 0)
					{
						if(((*its).second).GetData(Ephemeris::IODE) != IODE)
						{
							continue;
						}
						else
						{
							// Do nothing
						}
					}

					candidator = its;
					exist = true;
				}

			}
		}

		if (exist)
		{
			ephemeris_m.insert(std::pair<int, Ephemeris>(candidator->first, candidator->second));
		}
		else
		{
			// Do nothing
		}

		it = range.second;
		if (it != ephem_map.end())
		{
			range = ephem_map.equal_range(it->first);
		}
		else
		{
			break;
		}

	} while (it != ephem_map.end());

	return ephemeris_m;
}

long double RINEX_NavigationMessage::GetLongDouble(std::string str)
{
	unsigned int posD = str.find("D");
	unsigned int posd = str.find("d");
	if (posD != std::string::npos)
	{
		str.replace(posD, 1, "E");
	}
	else if (posd != std::string::npos)
	{
		str.replace(posd, 1, "E");
	}

	long double temp;
	sscanf(str.c_str(), "%LF", &temp);
	return temp;

}

bool RINEX_NavigationMessage::ReadHeader(std::ifstream &ifs, int &leap_sec)
{
	std::string buf;

	bool success = false;
	while (ifs && std::getline(ifs, buf))
	{
		if (buf.find("ION ALPHA") != std::string::npos)
		{
			Ionosphere_parameterA[A0] = GetLongDouble(buf.substr(0, 14));
			Ionosphere_parameterA[A1] = GetLongDouble(buf.substr(14, 12));
			Ionosphere_parameterA[A2] = GetLongDouble(buf.substr(26, 12));
			Ionosphere_parameterA[A3] = GetLongDouble(buf.substr(38, 12));
			success = true;
		}
		else if (buf.find("ION BETA") != std::string::npos)
		{
			Ionosphere_parameterB[B0] = GetLongDouble(buf.substr(0, 14));
			Ionosphere_parameterB[B1] = GetLongDouble(buf.substr(14, 12));
			Ionosphere_parameterB[B2] = GetLongDouble(buf.substr(26, 12));
			Ionosphere_parameterB[B3] = GetLongDouble(buf.substr(38, 12));
			success = true;
		}
		else if (buf.find("LEAP SECONDS") != std::string::npos)
		{
			leap_sec = atol(buf.substr(0, 6).c_str());
			success = true;
		}
		else if (buf.find("END OF HEADER") != std::string::npos)
		{
			success = true;
			break;
		}
	}

	return success;

}
bool RINEX_NavigationMessage::ReadBody(std::ifstream &ifs, int leap_sec)
{
	bool success = false;
	std::string buf;

	while (ifs)
	{
		Ephemeris ephem;
		int prn = 0;
		for (Ephemeris::Ephemeris_column column = Ephemeris::TOC; column < Ephemeris::END; column = (Ephemeris::Ephemeris_column)(column + 4))
		{
			std::getline(ifs, buf);
			if (!ifs)
			{
				break;
			}
			else
			{
				if (column == Ephemeris::TOC)
				{
					prn = atoi(buf.substr(0, 2).c_str());
					ephem.SetPRN(prn);
					tm tmbuf;
					tmbuf.tm_year = atoi(buf.substr(2, 3).c_str());
					if (tmbuf.tm_year < 80)
					{
						tmbuf.tm_year += 100;
					}
					else
					{
						// Do nothing
					}
					tmbuf.tm_mon = atoi(buf.substr(5, 3).c_str()) - 1;
					tmbuf.tm_mday = atoi(buf.substr(8, 3).c_str());
					tmbuf.tm_hour = atoi(buf.substr(11, 3).c_str());
					tmbuf.tm_min = atoi(buf.substr(14, 3).c_str());
					tmbuf.tm_sec = 0;
					long double temp;
					sscanf(buf.substr(17, 5).c_str(), "%LF", &temp);
					ephem.SetToc(GPS_Time(tmbuf, temp, leap_sec));
					success = true;
				}
				else
				{
					ephem.SetData(GetLongDouble(buf.substr(0, RINEX_TOP_FIELD_WIDTH)), column);
				}

				if (column != Ephemeris::TOT)
				{
					for (int i = 1; i < RINEX_NAV_FIELDS_LINE; i++)
					{
						ephem.SetData(GetLongDouble(buf.substr(RINEX_TOP_FIELD_WIDTH + (i - 1) * RINEX_NORMAL_FIELD_WIDTH, RINEX_NORMAL_FIELD_WIDTH)), (Ephemeris::Ephemeris_column)(column + i));
					}

				}
				else
				{
					ephem.SetData(GetLongDouble(buf.substr(RINEX_TOP_FIELD_WIDTH, RINEX_NORMAL_FIELD_WIDTH)), Ephemeris::FIT);
				}


			}
		}

		if (prn < 1)
		{
			continue;
		}
		else
		{
			// Do nothing
		}

		ephem_map.insert(std::multimap<int, Ephemeris>::value_type(prn, ephem));

	}

	return success;
}


