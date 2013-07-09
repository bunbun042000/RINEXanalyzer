/*
 * RINEX_ObservationData.cpp
 *
 *  Created on: 2013/07/03
 *      Author: bun
 */

#include "RINEX_ObservationData.h"
#include <iostream>

RINEX_ObservationData::RINEX_ObservationData()
{
	PsudoRangeMap.clear();
	number_of_observationData = 0;
	ver = RINEX::Ver2;

}

RINEX_ObservationData::RINEX_ObservationData(const std::string fname)
{
	filename = fname;
	PsudoRangeMap.clear();
	number_of_observationData = 0;
	ver = RINEX::Ver2;

}

RINEX_ObservationData::RINEX_ObservationData(const RINEX_ObservationData &RIN_obs)
{
	filename = RIN_obs.filename;
	PsudoRangeMap = RIN_obs.PsudoRangeMap;
	number_of_observationData = RIN_obs.number_of_observationData;
	ver = RIN_obs.ver;

}

RINEX_ObservationData::~RINEX_ObservationData()
{
	PsudoRangeMap.clear();
	filename = "";

}

void RINEX_ObservationData::SetFileName(std::string fname)
{
	filename = fname;
}

std::multimap<GPS_Time, PsudoRange> RINEX_ObservationData::GetPsudoRange()
{

	int leapsec;

	std::string fname = filename + "o";
	std::ifstream ifs(fname.c_str());
	std::string buf;

	if (ifs == 0)
	{
		return PsudoRangeMap;
	}
	else
	{
		// Do nothing
	}

	if (false == ReadHeader(ifs, leapsec))
	{
		return PsudoRangeMap;
	}
	else
	{
		// Do nothing
	}

	if (false == ReadBody(ifs, leapsec))
	{
		return PsudoRangeMap;
	}
	else
	{
		// Do nothing
	}

	return PsudoRangeMap;
}

bool RINEX_ObservationData::ReadHeader(std::ifstream &ifs, int &leapsec)
{
	std::string buf;

	bool success_ver = false;
	bool success_dataType = false;
	bool success_end = false;
	number_of_observationData = 0;

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
		}

		if (buf.find("# / TYPES OF OBSERV") != std::string::npos)
		{
			int n = atoi(buf.substr(0, 6).c_str());
			int currentpos = 6;
			for (int i = 0; i < n; i++)
			{
				if (i > 0 && (i % MAX_Types_of_Observ_line) == 0)
				{
					if (!std::getline(ifs, buf))
					{
						break;
					}
					else
					{
						currentpos = 6;
					}
				}
				else
				{
					// Do nothing
				}
				std::string column = buf.substr(currentpos, 6);
				if (column.find("C1") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("P2") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::P2);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("L1") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("L2") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("P1") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::P1);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("CA") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::CA);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("LA") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::LA);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("SA") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::SA);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("S1") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("CB") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::CB);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("LB") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::LB);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("SB") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::SB);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("CC") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::CC);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("LC") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::LC);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("SC") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::SC);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("CD") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::CD);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("LD") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::LD);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("SD") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::SD);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("S2") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("C5") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C5);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("L5") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L5);
					currentpos += 6;
					number_of_observationData++;
				}
				else if (column.find("S5") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S5);
					currentpos += 6;
					number_of_observationData++;
				}
				else
				{
					columnOrder.push_back(PsudoRange::UNKNOWN);
					currentpos += 6;
					number_of_observationData++;
				}
			}
			success_dataType = true;
		}
		else if (buf.find("LEAP SECONDS") != std::string::npos)
		{
			leapsec = atol(buf.substr(0, 6).c_str());
		}
		else if (buf.find("END OF HEADER") != std::string::npos)
		{
			success_end = true;
			break;
		}
	}

	return (success_ver && success_dataType && success_end);

}

bool RINEX_ObservationData::ReadBody(std::ifstream &ifs, int leapsec)
{
	bool success = false;
	std::string buf;
	int number_of_satellites;
	std::vector<int> PRN_list;
	GPS_Time currentTime;

	while (ifs && std::getline(ifs, buf))
	{
		// Get Epoch
		bool valid_epoch = false;

		// Read epoch
		int year = atoi(buf.substr(0, 3).c_str());
		if (year < 80)
		{
			year += 2000;
		}
		else
		{
			year += 1900;
		}
		int month = atoi(buf.substr(3, 3).c_str());
		int day = atoi(buf.substr(6, 3).c_str());
		int hour = atoi(buf.substr(9, 3).c_str());
		int min = atoi(buf.substr(12, 3).c_str());
		long double sec;
		sscanf(buf.substr(15, 11).c_str(), "%LF", &sec);
		if ((month >= 0) && (day > 0))
		{
			currentTime = GPS_Time(year, month, day, hour, min, sec, leapsec);
			valid_epoch = true;
			success = true;
		}
		else
		{
			// Do nothing
		}

		int status = atoi(buf.substr(26, 3).c_str());
		number_of_satellites = atoi(buf.substr(29, 3).c_str());

		// if event flag is set, skip following lines until next epoch
		if (status >= 2)
		{
			if (status >= 6)
			{
				continue;
			}
			else
			{
				// Do nothing
			}
			for (int i = 0; i < number_of_satellites * ((number_of_observationData - 1) / MAX_observs_Line + 1); i++)
			{
				if (!ifs || !std::getline(ifs, buf))
				{
					break;
				}
				else
				{
					if (std::isalpha(*buf.substr(60, 1).c_str()))
					{
						i += (number_of_observationData - 1) / MAX_observs_Line;
					}
				}
			}
			continue;
		}

		// epoch is no valid -> skip following data until next epoch
		if (!valid_epoch)
		{
			for (int i = 0; i < number_of_satellites * ((number_of_observationData - 1) / MAX_observs_Line + 1); i++)
			{
				if(!ifs || !std::getline(ifs, buf))
				{
					break;
				}
				else
				{
					// Do nothing
				}
			}
			continue;
		}

		if(number_of_satellites < 1)
		{
			continue;
		}
		else
		{
			// Do nothing
		}

		// Read PRNs
		PRN_list.clear();

		for (int i = 0; i < number_of_satellites; i++)
		{

			if(i>0 && (i % MAX_PRNs_Line) == 0)
			{
				std::getline(ifs, buf);
				if (!ifs)
				{
					break;
				}
				else
				{
					// Do nothing
				}

			}

			int PRN;
			switch(*buf.substr(start_position_PRN + 3 * (i % MAX_PRNs_Line), 1).c_str())
			{
			case ' ':
			case 'G':
				PRN = atoi(buf.substr(start_position_PRN + 1 + 3 * (i % MAX_PRNs_Line), 2).c_str());
				if (PRN <= 0)
				{
					PRN = 0;
				}
				else
				{
					// Do nothing
				}
				PRN_list.push_back(PRN);
				break;
			case 'J':
				PRN = atoi(buf.substr(start_position_PRN + 1 + 3 * (i % MAX_PRNs_Line), 2).c_str());
				if (PRN <= 0)
				{
					PRN = 0;
				}
				else
				{
					// Do nothing
				}
				PRN_list.push_back(PRN + RINEX::QZSS_PRN_Offset);
				break;
			default:
				PRN_list.push_back(0);
				break;
			}

		}

		// Read Psudorange data
		PsudoRange Psr;

		for (int i = 0; i < number_of_satellites; i++)
		{
			Psr.clear();

			if (!ifs || !std::getline(ifs, buf))
			{
				break;
			}
			else
			{
				// Do nothing
			}
			for (int j = 0; j < number_of_observationData; j++)
			{
				if (j > 0 && (j % MAX_observs_Line)==0)
				{
					if (!ifs || !std::getline(ifs, buf))
					{
						break;
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
				if (PRN_list[i] > 0 && columnOrder[j] != PsudoRange::UNKNOWN)
				{
					Psr.SetPRN(PRN_list[i]);
					long double temp;
					sscanf(buf.substr(observationData_column_length * (j % MAX_observs_Line), observationData_length).c_str(),
							"%LF", &temp);
					Psr.SetData(temp, columnOrder[j]);
				}
				else
				{
					// Do nothing
				}
			}

			if (PRN_list[i] > 0)
			{
				PsudoRangeMap.insert(std::pair<GPS_Time, PsudoRange>(currentTime, Psr));
			}
			else
			{
				// Do nothing
			}
		}

	}

	return success;

}
