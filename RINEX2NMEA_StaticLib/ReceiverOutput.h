/*
 * ReceiverOutput.h
 *
 *  Created on: 2013/07/09
 *      Author: bun
 */

#ifndef RECEIVEROUTPUT_H_
#define RECEIVEROUTPUT_H_

#include <map>
#include <cmath>
#include "GPS_Time.h"
#include "ENU_Frame.h"
#include "Matrix.h"
#include "PsudoRange.h"

class ReceiverOutput
{
public:
	ReceiverOutput();
	ReceiverOutput(GPS_Time &cur, ECEF_Frame &pos, std::map<int, PsudoRange> &sats, Matrix &cov);
	ReceiverOutput(const ReceiverOutput &recOut);
	virtual ~ReceiverOutput();

	void Set(GPS_Time cur, ECEF_Frame pos, std::map<int, PsudoRange> sats, Matrix cov);

	ECEF_Frame GetPosition()
	{
		return receiverPosition;
	}

	GPS_Time GetTime()
	{
		return currentTime;
	}

	long double GetHDOP();
	long double GetGDOP();
	long double GetPDOP();
	long double GetVDOP();
	std::map<int, ENU_Frame> GetENUSatellites();

private:
	GPS_Time currentTime;
	ECEF_Frame receiverPosition;
	std::map<int, PsudoRange> satellites;
	Matrix covariant;

};


#endif /* RECEIVEROUTPUT_H_ */
