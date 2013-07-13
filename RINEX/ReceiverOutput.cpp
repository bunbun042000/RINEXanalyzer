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

ReceiverOutput::ReceiverOutput(GPS_Time &cur, ECEF_Frame &pos, std::map<int, PsudoRange> &sats, Matrix &cov)
{
	Set(cur, pos, sats, cov);
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

void ReceiverOutput::Set(GPS_Time cur, ECEF_Frame pos, std::map<int, PsudoRange> sats, Matrix cov)
{
	currentTime = cur;
	receiverPosition = pos;
	satellites = sats;
	covariant = cov;

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

std::multimap<long double, long double> ReceiverOutput::GetElevationVsSatelliteDistanceDiff(ECEF_Frame &pos)
{
	std::multimap<long double, long double>elevationVsSatDistance;

	ECEF_Frame origin;
	if (pos.Distance(ECEF_Frame(0.0L, 0.0L, 0.0L)) < 1.0e-10)
	{
		origin = receiverPosition;
	}
	else
	{
		origin = pos;
	}

	for (std::map<int, PsudoRange>::iterator it = satellites.begin(); it != satellites.end(); it++)
	{
		long double elevation_deg = WGS84_Frame::Rad2Deg(ENU_Frame(it->second.GetSatellitePosition(), origin).GetElevation());
		long double distance_diff = it->second.GetCalculateRange() - it->second.GetSatellitePosition().Distance(origin);
		elevationVsSatDistance.insert(std::pair<long double, long double>(elevation_deg, distance_diff));

	}

	return elevationVsSatDistance;
}

std::multimap<long double, long double> ReceiverOutput::GetSkyPlot()
{
	std::multimap<long double, long double> skyplot;


	for (std::map<int, PsudoRange>::iterator it = satellites.begin(); it != satellites.end(); it++)
	{
		long double elevation_deg = WGS84_Frame::Rad2Deg(ENU_Frame(it->second.GetSatellitePosition(), receiverPosition).GetElevation());
		long double azimuth_deg = WGS84_Frame::Rad2Deg(ENU_Frame(it->second.GetSatellitePosition(), receiverPosition).GetAzimuth());
		skyplot.insert(std::pair<long double, long double>(elevation_deg, azimuth_deg));

	}

	return skyplot;

}
