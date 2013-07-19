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

};

#endif /* NMEA0183_H_ */
