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
 * RINEX_ObservationData.cpp
 *
 *  Created on: 2013/07/03
 *      Author: bun
 */

#define _CRT_SECURE_NO_WARNINGS

#include "RINEX_ObservationData.h"
#include <iostream>

RINEX_ObservationData::RINEX_ObservationData()
{
	PsudoRangeMap.clear();
	number_of_observationData = 0;
	ver = RINEX::Ver2;
	leapSecond = GPS_Time_const::leap_sec_base;

}

RINEX_ObservationData::RINEX_ObservationData(const std::string fname, const int leapsec)
{
	filename = fname;
	PsudoRangeMap.clear();
	number_of_observationData = 0;
	ver = RINEX::Ver2;
	leapSecond = leapsec;

}

RINEX_ObservationData::RINEX_ObservationData(const RINEX_ObservationData &RIN_obs)
{
	filename = RIN_obs.filename;
	PsudoRangeMap = RIN_obs.PsudoRangeMap;
	number_of_observationData = RIN_obs.number_of_observationData;
	ver = RIN_obs.ver;
	leapSecond = RIN_obs.leapSecond;

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

	std::string buf;

	std::string fname = filename + "o";
	std::ifstream ifs(fname.c_str());

	if (!ifs.is_open())
	{
		std::string fname2 = filename + ".obs";
		ifs.open(fname2.c_str());
	}
	else
	{
		// Do nothing
	}


	if (ifs == 0)
	{
		return PsudoRangeMap;
	}
	else
	{
		// Do nothing
	}

	if (false == ReadHeader(ifs, leapSecond))
	{
		return PsudoRangeMap;
	}
	else
	{
		// Do nothing
	}


	if (false == ReadBody(ifs, leapSecond))
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

				// Ver.3
				// C1C, L1C, D1C, S1C, // GPS L1 C/A / GLONASS G1 C/A / Galileo E1C / SBAS L1 C/A
				if (column.find("C1C") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1C);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L1C") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1C);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1C") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1C);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1C") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1C);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C1S, L1S, D1S, S1S, // GPS L1C(M)
				else if (column.find("C1S") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1S);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L1S") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1S);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1S") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1S);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1S") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1S);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C1L, L1L, D1L, S1L, // GPS L1C(L)
				else if (column.find("C1L") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1L);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L1L") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1L);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1L") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1L);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1L") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1L);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C1X, L1X, D1X, S1X, // GPS L1C(M+L) / Galileo E1(B+C)
				else if (column.find("C1X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L1X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C1P, L1P, D1P, S1P, // GPS L1P / GLONASS G1P
				else if (column.find("C1P") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1P);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L1P") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1P);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1P") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1P);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1P") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1P);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C1W, L1W, D1W, S1W, // GPS L1 Z-tracking
				else if (column.find("C1W") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1W);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L1W") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1W);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1W") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1W);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1W") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1W);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C1Y, L1Y, D1Y, S1Y, // GPS L1Y
				else if (column.find("C1Y") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1Y);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L1Y") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1Y);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1Y") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1Y);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1Y") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1Y);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C1M, L1M, D1M, S1M, // GPS L1M
				else if (column.find("C1M") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1M);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L1M") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1M);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1M") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1M);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1M") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1M);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				//     L1N, D1N, S1N, // GPS L1 codeless
				else if (column.find("L1N") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1N);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1N") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1N);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1N") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1N);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C2C, L2C, D2C, S2C, // GPS L2 C/A / GLONASS G2 C/A (GLONASS M)
				else if (column.find("C2C") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2C);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L2C") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2C);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2C") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2C);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2C") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2C);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C2D, L2D, D2D, S2D, // GPS L2 L1(C/A)+(P2-P1)
				else if (column.find("C2D") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2D);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L2D") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2D);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2D") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2D);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2D") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2D);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C2S, L2S, D2S, S2S, // GPS L2C(M)
				else if (column.find("C2S") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2S);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L2S") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2S);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2S") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2S);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2S") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2S);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C2L, L2L, D2L, S2L, // GPS L2C(L)
				else if (column.find("C2L") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2L);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L2L") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2L);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2L") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2L);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2L") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2L);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C2X, L2X, D2X, S2X, // GPS L2C(M+L) / Compass E2(I+Q)
				else if (column.find("C2X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L2X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C2P, L2P, D2P, S2P, // GPS L2P / GLONASS G2P
				else if (column.find("C2P") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2P);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L2P") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2P);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2P") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2P);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2P") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2P);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C2W, L2W, D2W, S2W, // GPS L2 Z-tracking
				else if (column.find("C2W") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2W);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L2W") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2W);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2W") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2W);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2W") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2W);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C2Y, L2Y, D2Y, S2Y, // GPS L2Y
				else if (column.find("C2Y") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2Y);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L2Y") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2Y);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2Y") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2Y);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2Y") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2Y);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C2M, L2M, D2M, S2M, // GPS L2M
				else if (column.find("C2M") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2M);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L2M") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2M);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2M") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2M);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2M") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2M);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				//      L2N, D2N, S2N, // GPS L2 codeless
				else if (column.find("L2N") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2N);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2N") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2N);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2N") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2N);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C5I, L5I, D5I, S5I, // GPS L5I / Galileo E5aI / SBAS L5I
				else if (column.find("C5I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C5I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L5I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L5I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D5I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D5I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S5I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S5I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C5Q, L5Q, D5Q, S5Q, // GPS L5Q / Galileo E5aQ / SBAS L5Q
				else if (column.find("C5Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C5Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L5Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L5Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D5Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D5Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S5Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S5Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C5X, L5X, D5X, S5X, // GPS L5(I+Q) / Galileo E5a(I+Q) / SBAS L5 (I+Q)
				else if (column.find("C5X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C5X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L5X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L5X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D5X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D5X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S5X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S5X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C1A, L1A, D1A, S1A, // Galileo E1A
				else if (column.find("C1A") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1A);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L1A") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1A);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1A") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1A);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1A") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1A);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C1B, L1B, D1B, S1B, // Galileo E1B
				else if (column.find("C1B") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1B);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L1B") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1B);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1B") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1B);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1B") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1B);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C1Z, L1Z, D1Z, S1Z, // Galileo E1(A+B+C)
				else if (column.find("C1Z") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1Z);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L1Z") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1Z);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1Z") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1Z);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1Z") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1Z);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else
				{
					// Do nothing
				}

				// C7I, L7I, D7I, S7I, // Galileo E5bI / Compass E5bI
				if (column.find("C7I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C7I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L7I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L7I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D7I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D7I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S7I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S7I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C7Q, L7Q, D7Q, S7Q, // Galileo E5bQ / Compass E5bQ
				else if (column.find("C7Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C7Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L7Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L7Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D7Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D7Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S7Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S7Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C7X, L7X, D7X, S7X, // Galileo E5b(I+Q) / Compass E5b(I+Q)
				else if (column.find("C7X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C7X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L7X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L7X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D7X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D7X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S7X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S7X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C8I, L8I, D8I, S8I, // Galileo E5I
				else if (column.find("C8I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C8I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L8I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L8I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D8I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D8I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S8I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S8I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C8Q, L8Q, D8Q, S8Q, // Galileo E5Q
				else if (column.find("C8Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C8Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L8Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L8Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D8Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D8Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S8Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S8Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C8X, L8X, D8X, S8X, // Galileo E5(I+Q)
				else if (column.find("C8X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C8X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L8X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L8X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D8X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D8X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S8X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S8X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C6A, L6A, D6A, S6A, // Galileo E6A
				else if (column.find("C6A") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C6A);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L6A") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L6A);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D6A") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D6A);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S6A") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S6A);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C6B, L6B, D6B, S6B, // Galileo E6B
				else if (column.find("C6B") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C6B);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L6B") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L6B);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D6B") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D6B);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S6B") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S6B);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C6C, L6C, D6C, S6C, // Galileo E6C
				else if (column.find("C6C") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C6C);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L6C") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L6C);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D6C") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D6C);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S6C") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S6C);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C6X, L6X, D6X, S6X, // Galileo E6(B+C) / Compass E6(I+Q)
				else if (column.find("C6X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C6X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L6X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L6X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D6X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D6X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S6X") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S6X);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C6Z, L6Z, D6Z, S6Z, // Galileo E6(A+B+C)
				else if (column.find("C6Z") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C6Z);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L6Z") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L6Z);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D6Z") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D6Z);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S6Z") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S6Z);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C2I, L2I, D2I, S2I, // Compass E2I
				else if (column.find("C2I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L2I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C2Q, L2Q, D2Q, S2Q, // Compass E2Q
				else if (column.find("C2Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L2Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C6I, L6I, D6I, S6I, // Compass E6I
				else if (column.find("C6I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C6I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L6I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L6I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D6I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D6I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S6I") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S6I);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C6Q, L6Q, D6Q, S6Q, // Compass E6Q
				else if (column.find("C6Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C6Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L6Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L6Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D6Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D6Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S6Q") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S6Q);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else
				{
					// Do nothing
				}

				// for below Ver.2.12
				if (column.find("C1") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("P1") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C1);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L1") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L1);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D1") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D1);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S1") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S1);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("C2") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("P2") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C2);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L2") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L2);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D2") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D2);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S2") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S2);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("C5") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C5);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L5") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L5);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D5") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D5);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S5") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S5);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C6, L6, D6, S6, // Galileo L6 / QZSS LEX
				else if (column.find("C6") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C6);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L6") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L6);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D6") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D6);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S6") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S6);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C7, L7, D7, S7, // Galileo E5b
				else if (column.find("C7") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C7);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L7") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L7);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D7") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D7);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S7") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S7);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// C8, L8, D8, S8, // Galileo E5a+b
				else if (column.find("C8") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::C8);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("L8") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::L8);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("D8") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::D8);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("S8") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::S8);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// CA,	LA,	DA, SA, // QZSS L1 C/A
				else if (column.find("CA") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::CA);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("LA") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::LA);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("DA") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::DA);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("SA") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::SA);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// CB, LB, DB,	SB, // QZSS L1C
				else if (column.find("CB") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::CB);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("LB") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::LB);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("DB") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::DB);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("SB") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::SB);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// CC, LC, DC, SC, // QZSS L2C
				else if (column.find("CC") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::CC);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("LC") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::LC);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("DC") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::DC);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("SC") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::SC);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// CD, LD, DD, SD, // GLONASS L2 SA
				else if (column.find("CD") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::CD);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("LD") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::LD);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("DD") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::DD);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				else if (column.find("SD") != std::string::npos)
				{
					columnOrder.push_back(PsudoRange::SD);
					currentpos += 6;
					number_of_observationData++;
					continue;
				}
				// for unknown
				else
				{
					columnOrder.push_back(PsudoRange::UNKNOWN);
					currentpos += 6;
					number_of_observationData++;
					continue;
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
		sscanf(buf.substr(15, 11).c_str(), "%Lf", &sec);
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
							"%Lf", &temp);
					Psr.SetData(temp, columnOrder[j], ver);
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
