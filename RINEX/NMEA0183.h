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
 * NMEA0183.h
 *
 *  Created on: 2013/07/19
 *      Author: bun
 */

#ifndef NMEA0183_H_
#define NMEA0183_H_

#include "ReceiverOutput.h"
#include <sstream>
#include <iomanip>
#include <string>

class NMEA0183
{
public:
	NMEA0183();
	virtual ~NMEA0183();

	std::multimap<GPS_Time, std::string> OutputNMEA0183(std::map<GPS_Time, ReceiverOutput>calculatedData);

private:
	std::string CreateCheckSum(std::string str);
	std::string CreateGPGGA(ReceiverOutput data);
	std::string CreateGPGSV(ReceiverOutput data);
	std::string CreateGPZDA(ReceiverOutput data);

	std::string CreateLatitude(ReceiverOutput data);
	std::string CreateLongitude(ReceiverOutput data);

	static const int GSV_Max_number_of_satellites_per_line = 4;
	static const int GSV_Max_number_of_lines = 9;
};

#endif /* NMEA0183_H_ */
