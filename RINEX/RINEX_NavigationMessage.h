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
#include "IonoSphere.h"
#include "RINEX_constant.h"

class RINEX_NavigationMessage
{
public:
	RINEX_NavigationMessage();
	RINEX_NavigationMessage(std::string fname);
	RINEX_NavigationMessage(const RINEX_NavigationMessage &pRIN);
	virtual ~RINEX_NavigationMessage();

	bool Read();
	void SetFileName(std::string fname);
	IonoSphere GetIon()
	{
		return ion;
	}

	std::map<int, Ephemeris> GetEphemeris(GPS_Time current_gpst, const int IODE, const bool use_qzss);
	std::map<int, long double> GetIonoDelayCorrection(ECEF_Frame userPosition, GPS_Time currentTime, const int IODE);

	std::multimap <int, Ephemeris> ephem_map; // PRN and Ephemeris_Data


private:
	static const int RINEX_NAV_FIELDS_LINE = 4;
	static const int RINEX_NORMAL_FIELD_WIDTH = 19;
	static const int RINEX_TOP_FIELD_WIDTH_Normal = 22;
	static const int RINEX_TOP_FIELD_WIDTH_QZS_and_300_above = 23;
	static const long int Ephemeris_Default_Freshness = 7200L; // 2 hours

	IonoSphere ion;

	std::string filename;

	enum _FileType
	{
		GPS_Navigation,
		QZSS_Navigation
	};

	long double GetLongDouble(std::string str);
	bool _Read(std::ifstream &ifs);
	bool ReadHeader(std::ifstream &ifs, int &leap_sec);
	bool ReadBody(std::ifstream &ifs, int leap_sec);

	RINEX::_Version ver;
	_FileType type;

};


#endif /* RINEX_NAVIGATION_MESSAGE_H_ */
