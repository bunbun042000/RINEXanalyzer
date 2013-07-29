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
 * ReceiverOutput.cpp
 *
 *  Created on: 2013/07/09
 *      Author: bun
 */

#include "ReceiverOutput.h"

ReceiverOutput::ReceiverOutput()
{

}

ReceiverOutput::ReceiverOutput(GPS_Time &cur, ECEF_Frame &pos, std::map<int, PsudoRange> &sats, Matrix &cov, signalType::Type _type)
{
	Set(cur, pos, sats, cov, _type);
}

ReceiverOutput::ReceiverOutput(const ReceiverOutput &recOut)
{
	currentTime = recOut.currentTime;
	receiverPosition = recOut.receiverPosition;
	satellites = recOut.satellites;
	covariant = recOut.covariant;

}

ReceiverOutput::~ReceiverOutput()
{
	satellites.clear();
}

void ReceiverOutput::Set(GPS_Time cur, ECEF_Frame pos, std::map<int, PsudoRange> sats, Matrix cov, signalType::Type _type)
{
	currentTime = cur;
	receiverPosition = pos;
	satellites = sats;
	covariant = cov;
	type = _type;

}

long double ReceiverOutput::GetHDOP()
{
	return sqrt(covariant.GetData(0, 0) + covariant.GetData(1, 1));
}

long double ReceiverOutput::GetGDOP()
{
	return sqrt(covariant.GetData(0, 0) + covariant.GetData(1, 1) + covariant.GetData(2, 2) + covariant.GetData(3, 3));
}

long double ReceiverOutput::GetPDOP()
{
	return sqrt(covariant.GetData(0, 0) + covariant.GetData(1, 1) + covariant.GetData(2, 2));
}

long double ReceiverOutput::GetVDOP()
{
	return sqrt(covariant.GetData(2, 2));
}

std::map<int, ENU_Frame> ReceiverOutput::GetENUSatellites()
{
	std::map<int, ENU_Frame> ENUSats;

	for(std::map<int, PsudoRange>::iterator it = satellites.begin(); it != satellites.end(); it++)
	{
		ENUSats.insert(std::pair<int, ENU_Frame>(it->first, ENU_Frame(WGS84_Frame(it->second.GetSatellitePosition()), WGS84_Frame(receiverPosition))));
	}

	return ENUSats;
}


std::map<int, SatellitesInView> ReceiverOutput::GetSkyPlot(ECEF_Frame pos)
{
	std::map<int, SatellitesInView> skyplot;
	ECEF_Frame origin = pos;

	if (origin.Distance(ECEF_Frame(0.0L, 0.0L, 0.0L)) < 1.0e-10)
	{
		origin = receiverPosition;
	}
	else
	{
		// Do nothing
	}

	for (std::map<int, PsudoRange>::iterator it = satellites.begin(); it != satellites.end(); it++)
	{
		SatellitesInView sat;
		sat.elevation = WGS84_Frame::Rad2Deg(ENU_Frame(it->second.GetSatellitePosition(), origin).GetElevation());
		sat.azimuth = WGS84_Frame::Rad2Deg(ENU_Frame(it->second.GetSatellitePosition(), origin).GetAzimuth());
		if (sat.azimuth < 0.0)
		{
			sat.azimuth += 360.0L;
		}
		else
		{
			// Do nothing
		}
		sat.PRN = it->first;
		sat.SNR = it->second.GetSNR(type);
		sat.psudodistance = it->second.GetCalculateRange();
		sat.truedistance = it->second.GetSatellitePosition().Distance(origin);
		sat.distancediff = sat.psudodistance - sat.truedistance;
		skyplot.insert(std::pair<int, SatellitesInView>(sat.PRN, sat));

	}

	return skyplot;

}
