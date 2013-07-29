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
 * RINEX_NavigationMessage.cpp
 *
 *  Created on: 2013/06/22
 *      Author: bun
 */

#define _CRT_SECURE_NO_WARNINGS

#include "RINEX_NavigationMessage.h"
#include <iostream>
#include <ctime>

RINEX_NavigationMessage::RINEX_NavigationMessage(std::string fname = "")
{
	filename = fname;

	ver = RINEX::Ver2;
	type = GPS_Navigation;
}

RINEX_NavigationMessage::RINEX_NavigationMessage(const RINEX_NavigationMessage &nRIN)
{
	filename = nRIN.filename;
	ephem_map = nRIN.ephem_map;
	ion = nRIN.ion;
	ver = nRIN.ver;
	type = nRIN.type;

}

RINEX_NavigationMessage::~RINEX_NavigationMessage()
{
	filename = "";
	ephem_map.clear();

}

bool RINEX_NavigationMessage::Read(const bool withQZSS)
{

	std::ifstream ifs;
	bool flag_gnss = false;
	bool flag_qzss = false;
	bool from_RTKconv = false;

	std::string fname = filename + "n";
	ifs.open(fname.c_str());
	if (!ifs.is_open())
	{
		std::string fname = filename + ".nav";
		ifs.open(fname.c_str());
		if (!ifs.is_open())
		{
			return flag_gnss;
		}
		else
		{
			from_RTKconv = true;
		}
	}
	else
	{
		// Do nothing
	}

	flag_gnss = _Read(ifs);
	ifs.close();

	if (!from_RTKconv && withQZSS)
	{
		fname = filename + "q";
		ifs.open(fname.c_str());
		if (!ifs.is_open())
		{
			return flag_gnss;
		}
		else
		{
			flag_qzss = _Read(ifs);
		}
	}
	else
	{
		return flag_gnss;
	}

	return (flag_gnss && flag_qzss);

}

void RINEX_NavigationMessage::SetFileName(std::string fname)
{
	filename = fname;
}

std::map<int, Ephemeris> RINEX_NavigationMessage::GetEphemeris(GPS_Time current_gpst, const int IODE, const bool use_qzss)
{

	std::map <int, Ephemeris> ephemeris_m;

	ephemeris_m.clear();

	if(ephem_map.empty())
	{
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
		std::multimap<int, Ephemeris>::iterator candidator = range.first;

		for (std::multimap<int, Ephemeris>::iterator its = range.first; its != range.second; its++)
		{

			if(!use_qzss && candidator->first > RINEX::QZSS_PRN_Offset)
			{
				continue;
			}
			else if (((its->second).GetTot() >= (candidator->second).GetTot()) && (current_gpst >= (its->second).GetTot()))
			{
				long double freshness = its->second.GetData(Ephemeris::FIT) * GPS_Time::Seconds_in_Hour / 2.0;

				if (freshness < Ephemeris_Default_Freshness)
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
					else
					{
						// Do nothing
					}

					// Health check
					if (((its->first) <= RINEX::QZSS_PRN_Offset) && ((its->second).GetData(Ephemeris::health) != 0.0L))
					{
						continue;
					}
					else if ((its->first) > RINEX::QZSS_PRN_Offset && ((its->second).GetData(Ephemeris::health) > 1.0L))
					{
						continue;
					}
					else
					{
						// Do nothing
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
	size_t posD = str.find("D");
	size_t posd = str.find("d");
	if (posD != std::string::npos)
	{
		str.replace(posD, 1, "E");
	}
	else if (posd != std::string::npos)
	{
		str.replace(posd, 1, "E");
	}

	long double temp;
	sscanf(str.c_str(), "%Lf", &temp);
	return temp;

}

bool RINEX_NavigationMessage::_Read(std::ifstream &ifs)
{
	int leap_second = 0;

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

bool RINEX_NavigationMessage::ReadHeader(std::ifstream &ifs, int &leap_sec)
{
	std::string buf;

	bool success_ver = false;
	bool success_type = false;
	bool success_end = false;

	while (ifs && std::getline(ifs, buf))
	{
		if (buf.find("RINEX VERSION / TYPE") != std::string::npos)
		{
			std::string ver_str = buf.substr(0, 9);
			if (ver_str.find("2  ") != std::string::npos)
			{
				ver = RINEX::Ver2;
				success_ver = true;
			}
			else if(ver_str.find("2.10") != std::string::npos)
			{
				ver = RINEX::Ver210;
				success_ver = true;
			}
			else if(ver_str.find("2.11") != std::string::npos)
			{
				ver = RINEX::Ver211;
				success_ver = true;
			}
			else if(ver_str.find("2.12") != std::string::npos)
			{
				ver = RINEX::Ver212;
				success_ver = true;
			}
			else if(ver_str.find("3.00") != std::string::npos)
			{
				ver = RINEX::Ver300;
				success_ver = true;
			}
			else if(ver_str.find("3.01") != std::string::npos)
			{
				ver = RINEX::Ver301;
				success_ver = true;
			}
			else if(ver_str.find("3.02") != std::string::npos)
			{
				ver = RINEX::Ver302;
				success_ver = true;
			}
			else
			{
				break;
			}

			std::string file_type = buf.substr(20,1);
			if (file_type == "N")
			{
				type = GPS_Navigation;
				success_type = true;
			}
			else if (file_type == "J")
			{
				type = QZSS_Navigation;
				success_type = true;
			}
			else
			{
				break;
			}

		}
		else if (buf.find("ION ALPHA") != std::string::npos)
		{
			ion.SetData(GetLongDouble(buf.substr(0, 14)), IonoSphere::A0);
			ion.SetData(GetLongDouble(buf.substr(14, 12)), IonoSphere::A1);
			ion.SetData(GetLongDouble(buf.substr(26, 12)), IonoSphere::A2);
			ion.SetData(GetLongDouble(buf.substr(38, 12)), IonoSphere::A3);
		}
		else if (buf.find("ION BETA") != std::string::npos)
		{
			ion.SetData(GetLongDouble(buf.substr(0, 14)), IonoSphere::B0);
			ion.SetData(GetLongDouble(buf.substr(14, 12)), IonoSphere::B1);
			ion.SetData(GetLongDouble(buf.substr(26, 12)), IonoSphere::B2);
			ion.SetData(GetLongDouble(buf.substr(38, 12)), IonoSphere::B3);
		}
		else if (buf.find("LEAP SECONDS") != std::string::npos)
		{
			leap_sec = atol(buf.substr(0, 6).c_str());
		}
		else if (buf.find("END OF HEADER") != std::string::npos)
		{
			success_end = true;
			break;
		}
	}

	return (success_ver && success_end && success_type);

}

bool RINEX_NavigationMessage::ReadBody(std::ifstream &ifs, int leap_sec)
{
	bool success = false;
	std::string buf;
	int top_field_length;

	if ((type == GPS_Navigation) && ((ver == RINEX::Ver2) || (ver == RINEX::Ver210) || (ver == RINEX::Ver211) || (ver == RINEX::Ver212)))
	{
		top_field_length = RINEX_TOP_FIELD_WIDTH_Normal;
	}
	else
	{
		top_field_length = RINEX_TOP_FIELD_WIDTH_QZS_and_300_above;
	}

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
					int Epoch_offset;
					if ((type == GPS_Navigation) && ((ver == RINEX::Ver2) || (ver == RINEX::Ver210) || (ver == RINEX::Ver211) || (ver == RINEX::Ver212)))
					{
						prn = atoi(buf.substr(0, 2).c_str());
						Epoch_offset = 2;
					}
					else
					{
						std::string satellite_type = buf.substr(0, 1);
						if (satellite_type == "G")
						{
							prn = atoi(buf.substr(1, 2).c_str());
						}
						else if (satellite_type == "J")
						{
							prn = atoi(buf.substr(1, 2).c_str()) + RINEX::QZSS_PRN_Offset;
						}
						Epoch_offset = 3;
					}

					ephem.SetPRN(prn);
					int year = atoi(buf.substr(Epoch_offset, 3).c_str());
					if (year < 80)
					{
						year += 2000;
					}
					else
					{
						year += 1900;
					}
					int month = atoi(buf.substr(Epoch_offset + 3, 3).c_str());
					int day = atoi(buf.substr(Epoch_offset + 6, 3).c_str());
					int hour = atoi(buf.substr(Epoch_offset + 9, 3).c_str());
					int minute = atoi(buf.substr(Epoch_offset + 12, 3).c_str());
					long double sec;
					sscanf(buf.substr(Epoch_offset + 15, 5).c_str(), "%Lf", &sec);
					ephem.SetToc(GPS_Time(year, month, day, hour, minute, sec, leap_sec));
					success = true;
				}
				else
				{
					ephem.SetData(GetLongDouble(buf.substr(0, top_field_length)), column);
				}

				if (column != Ephemeris::TOT)
				{
					for (int i = 1; i < RINEX_NAV_FIELDS_LINE; i++)
					{
						ephem.SetData(GetLongDouble(buf.substr(top_field_length + (i - 1) * RINEX_NORMAL_FIELD_WIDTH, RINEX_NORMAL_FIELD_WIDTH)), (Ephemeris::Ephemeris_column)(column + i));
					}

				}
				else
				{
					ephem.SetData(GetLongDouble(buf.substr(top_field_length, RINEX_NORMAL_FIELD_WIDTH)), Ephemeris::FIT);
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


