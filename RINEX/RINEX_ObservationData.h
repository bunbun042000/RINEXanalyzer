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
#include "RINEX_constant.h"


class RINEX_ObservationData
{
public:
	RINEX_ObservationData();
	RINEX_ObservationData(const std::string fname, const int leapsec);
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
	int leapSecond;


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
