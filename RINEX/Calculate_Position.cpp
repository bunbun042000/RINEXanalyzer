/*
 * Calculate_Position.cpp
 *
 *  Created on: 2013/06/17
 *      Author: bun
 */

#include "Calculate_Position.h"
#include <iostream>

Calculate_Position::Calculate_Position()
{
	type = PsudoRange::C1;

}


Calculate_Position::Calculate_Position(std::map<int, Ephemeris> ephem, std::map<int, PsudoRange> range, PsudoRange::MeansType _type, GPS_Time currentTime, IonoSphere ion)
{

	current = currentTime;

	ephemeris = ephem;
	originalpsudodistance = range;
	type = _type;

	ionosphere = ion;
	std::vector<ECEF_Frame> satellites;
	GPS_Time modifiedCurrent;
	std::vector<long double> original_distance;
	std::vector<long double> distance;

}

Calculate_Position::~Calculate_Position()
{

	ephemeris.clear();
	originalpsudodistance.clear();

}

ReceiverOutput Calculate_Position::GetPosition()
{

	ECEF_Frame position = ECEF_Frame(0.0L, 0.0L, 0.0L);
	Matrix G; //= Matrix(number_of_satellites, 4);
	Matrix dr; //= Matrix(number_of_satellites, 1);
	int i;
	int j = 0;
	long double r;
	Matrix cov;

	int number_of_satellites = 0;

	std::vector<ECEF_Frame> satellites;
	std::map<int, PsudoRange> psudodistance;
	GPS_Time modifiedCurrent;
	std::vector<long double> original_distance;
	std::vector<long double> distance;
	std::vector<long double> clockdiff;

	long double diff;
	diff = calc_pos::max_diff;

	long double receiver_clockdiff = 0.0L;

	while(diff > calc_pos::min_diff)
	{
		i = 0;

		satellites.clear();
		original_distance.clear();
		clockdiff.clear();
		distance.clear();

		modifiedCurrent = GPS_Time(current.GetWeek(), current.GetSecond() - receiver_clockdiff / IS_GPS_200::C_velocity, current.GetLeapSecond());

		std::map<int, PsudoRange>::iterator current_dist_it = originalpsudodistance.begin();
		for (std::map <int, Ephemeris>::iterator it = ephemeris.begin(); it != ephemeris.end(); it++)
		{
			for (std::map<int, PsudoRange>::iterator dist_it = current_dist_it; dist_it != originalpsudodistance.end(); dist_it++)
			{
				if (dist_it->first == it->first)
				{
					original_distance.push_back(dist_it->second.GetData(type));

					long double r = dist_it->second.GetData(type) - receiver_clockdiff;
					long double satellite_clock = (it->second).GetClock(modifiedCurrent, r);
					r = dist_it->second.GetData(type) - receiver_clockdiff + satellite_clock * IS_GPS_200::C_velocity;

					dist_it->second.SetCalculateRange(r);

					satellite_clock = (it->second).GetClock(modifiedCurrent, r);

					ECEF_Frame satellite_position = (it->second).GetPosition(modifiedCurrent, r);
					satellites.push_back(satellite_position);

					dist_it->second.SetSatellitePosition(satellite_position);
					psudodistance.insert(std::pair<int, PsudoRange>(dist_it->first, dist_it->second));

					clockdiff.push_back(satellite_clock);
					distance.push_back(satellite_position.Distance(position));
					current_dist_it = dist_it;
					i++;
					break;
				}
				else
				{
					continue;
				}
			}
		}


		number_of_satellites = i;
		G.SetSize(number_of_satellites, 4);
		dr.SetSize(number_of_satellites, 1);

		// Create Observation matrix
		for (i = 0; i < number_of_satellites; i++)
		{
			r = satellites[i].Distance(position);
			ENU_Frame enu(satellites[i], position);
			G.SetData(-enu.GetE()/r, i, 0);
			G.SetData(-enu.GetN()/r, i, 1);
			G.SetData(-enu.GetU()/r, i, 2);
			G.SetData(1.0, i, 3);

			dr.SetData(original_distance[i] + clockdiff[i] * IS_GPS_200::C_velocity - r - receiver_clockdiff, i, 0);

			if (j > 3)
			{
				long double atomospheric_delay = TropoSphere::GetTropoSphereCollection(satellites[i], position);
				if (ionosphere.IsValid())
				{
					atomospheric_delay += ionosphere.GetIonoSphereDelayCorrection(satellites[i], position, current);
				}
				else
				{
					// Do nothing
				}
				dr.SetData(dr.GetData(i, 0) + atomospheric_delay, i, 0);
			}
		}

		Matrix Gt = G.Tranposed();
		Matrix GtG = Gt * G;
		Matrix Gtdr = Gt * dr;

		Gaussian_Elimination gauss;

		cov = gauss.GetAnswer(GtG, Gtdr);

		position= ENU_Frame(Gtdr.GetData(0, 0), Gtdr.GetData(1, 0), Gtdr.GetData(2, 0), WGS84_Frame(position)).GetPosition();


		receiver_clockdiff += Gtdr.GetData(3, 0);

		diff = ECEF_Frame(Gtdr).Distance(ECEF_Frame(0, 0, 0));

		if (j > calc_pos::max_loop)
		{
			break;
		}
		else
		{
			//Do nothing
		}
		j++;
	}

	ReceiverOutput ret = ReceiverOutput(modifiedCurrent, position, psudodistance, cov);
	return ret;
}
