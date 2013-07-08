/*
 * RINEX_ObservationData.h
 *
 *  Created on: 2013/07/03
 *      Author: bun
 */

#ifndef RINEX_OBSERVATIONDATA_H_
#define RINEX_OBSERVATIONDATA_H_

#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>

#include "PsudoRange.h"
#include "RINEX.h"


class RINEX_ObservationData
{
public:
	RINEX_ObservationData();
	RINEX_ObservationData(const std::string fname);
	RINEX_ObservationData(const RINEX_ObservationData &RIN_obs);
	virtual ~RINEX_ObservationData();

	void SetFileName(std::string fname);

	std::multimap<GPS_Time, PsudoRange> GetPsudoRange();

private:
	std::multimap<GPS_Time, PsudoRange> PsudoRangeMap;
	std::string filename;
	std::vector<PsudoRange::MeansType> columnOrder;
	int number_of_observationData;
	RINEX::_Version ver;


	bool ReadHeader(std::ifstream &ifs, int &leapSecond);
	bool ReadBody(std::ifstream &ifs, int leapSecond);

	static const int MAX_observs_Line = 5;
	static const int MAX_Types_of_Observ_line = 9;
	static const int MAX_PRNs_Line = 12;
	static const int MAX_Observs = 32;
	static const int start_position_PRN = 32;
	static const int observationData_column_length = 16;
	static const int observationData_length = 14;
};


#endif /* RINEX_OBSERVATIONDATA_H_ */
