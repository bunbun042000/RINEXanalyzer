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


struct SatellitesInView
{
	int PRN;
	long double azimuth;
	long double elevation;
	long double SNR;
	long double psudodistance;
	long double truedistance;
	long double distancediff;
};

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

	std::map<int, SatellitesInView> GetSkyPlot(ECEF_Frame pos);

	int GetNumberOfSatellites()
	{
		return satellites.size();
	}

private:
	GPS_Time currentTime;
	ECEF_Frame receiverPosition;
	std::map<int, PsudoRange> satellites;
	Matrix covariant;

};


#endif /* RECEIVEROUTPUT_H_ */
