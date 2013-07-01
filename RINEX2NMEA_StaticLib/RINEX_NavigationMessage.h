/*
 * RINEX_Navigation_Message.h
 *
 *  Created on: 2013/06/22
 *      Author: bun
 */

#ifndef RINEX_NAVIGATION_MESSAGE_H_
#define RINEX_NAVIGATION_MESSAGE_H_

#include <map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include "Ephemeris.h"

class RINEX_NavigationMessage
{
public:
	RINEX_NavigationMessage();
	RINEX_NavigationMessage(std::string fname);
	RINEX_NavigationMessage(const RINEX_NavigationMessage &pRIN);
	~RINEX_NavigationMessage();

	bool Read();
	void SetFileName(std::string fname);

	std::map<int, Ephemeris> GetEphemeris(GPS_Time current_gpst, const int IODE);

	enum ION_alpha {
		A0,
		A1,
		A2,
		A3
	};

	enum ION_beta {
		B0,
		B1,
		B2,
		B3
	};

	std::multimap <int, Ephemeris> ephem_map; // PRN and Ephemeris_Data

private:
	static const int RINEX_NAV_FIELDS_LINE = 4;
	static const int RINEX_NORMAL_FIELD_WIDTH = 19;
	static const int RINEX_TOP_FIELD_WIDTH = 22;
	static const long int Ephemeris_Default_Freshness = 7200L; // 2 hours

	std::string filename;
	int week;

	std::map <int, Ephemeris> ephemeris_m;

	std::map <ION_alpha, long double> Ionosphere_parameterA;
	std::map <ION_beta, long double> Ionosphere_parameterB;

	long double GetLongDouble(std::string str);
	bool ReadHeader(std::ifstream &ifs, int &leap_sec);
	bool ReadBody(std::ifstream &ifs, int leap_sec);

};


#endif /* RINEX_NAVIGATION_MESSAGE_H_ */
