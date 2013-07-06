/*
 * Calculate_Position.cpp
 *
 *  Created on: 2013/06/17
 *      Author: bun
 */

#include "Calculate_Position.h"
#include <iostream>
#include <vector>

Calculate_Position::Calculate_Position()
{
	number_of_satellites = 0;
	satellites.clear();
	valid = false;
	from_ephemeris = false;

}

Calculate_Position::Calculate_Position(const Calculate_Position &cal)
{
	number_of_satellites = cal.number_of_satellites;
	satellites = cal.satellites;
	distance = cal.distance;
	valid = cal.valid;
	current = cal.current;
	clockdiff = cal.clockdiff;
	from_ephemeris = cal.from_ephemeris;
	ionosphere = cal.ionosphere;

}

Calculate_Position::Calculate_Position(std::vector<ECEF_Frame> sats, std::vector<long double> dist, const int n_sats)
{

	valid = false;

	if (sats.size() == dist.size())
	{
		number_of_satellites = sats.size();
	}
	else
	{
		return;
	}

	satellites = sats;
	distance = dist;

	valid = true;
	from_ephemeris = false;
	IsValid();

}

Calculate_Position::Calculate_Position(std::map<int, Ephemeris> ephem, std::map<int, long double> dist, GPS_Time currentTime, IonoSphere ion)
{

	current = currentTime;

	ephemeris = ephem;
	psudodistance = dist;
	GetCurrentSatellites(ECEF_Frame(0.0L, 0.0L, 0.0L), 0.0L);

	ionosphere = ion;
	from_ephemeris = true;

	valid = true;
}

Calculate_Position::~Calculate_Position()
{

	number_of_satellites = 0;
	ephemeris.clear();
	psudodistance.clear();
	satellites.clear();
	distance.clear();
	original_distance.clear();
	clockdiff.clear();
	valid_PRN.clear();

	from_ephemeris = false;
	valid = false;

}

ECEF_Frame Calculate_Position::GetPosition()
{

	IsValid();

	ECEF_Frame ans = ECEF_Frame(0.0L, 0.0L, 0.0L);
	Matrix G = Matrix(number_of_satellites, 4);
	Matrix dr = Matrix(number_of_satellites, 1);
	int i;
	int j = 0;
	long double r;


	long double diff;
	diff = max_diff;

	long double receiver_clockdiff = 0.0L;

	while(diff > min_diff)
	{
		if (from_ephemeris)
		{
			GetCurrentSatellites(ans, receiver_clockdiff);
		}
		else
		{
			// Do nothing
		}

		// Create Observation matrix
		for (i = 0; i < number_of_satellites; i++)
		{
			r = satellites[i].Distance(ans);
			ENU_Frame enu(satellites[i], ans);
			G.SetData(-enu.GetE()/r, i, 0);
			G.SetData(-enu.GetN()/r, i, 1);
			G.SetData(-enu.GetU()/r, i, 2);
			G.SetData(1.0, i, 3);

			if(from_ephemeris)
			{
				dr.SetData(original_distance[i] + clockdiff[i] * IS_GPS_200::C_velocity - r - receiver_clockdiff, i, 0);
			}
			else
			{
				dr.SetData((distance[i] - r), i, 0);
			}

			if (j > 3 && from_ephemeris)
			{
				long double atomospheric_delay = TropoSphere::GetTropoSphereCollection(satellites[i], ans);
				if (ionosphere.IsValid())
				{
					atomospheric_delay += ionosphere.GetIonoSphereDelayCorrection(satellites[i], ans, current);
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

		Gaussian_Elimination gauss(GtG, Gtdr);

		Gtdr = gauss.GetAnswer();

		ans = ENU_Frame(Gtdr.GetData(0, 0), Gtdr.GetData(1, 0), Gtdr.GetData(2, 0), WGS84_Frame(ans)).GetPosition();

//		std::cout << "x = " << std::fixed << ans.GetX() << std::endl;
//		std::cout << "y = " << std::fixed << ans.GetY() << std::endl;
//		std::cout << "z = " << std::fixed << ans.GetZ() << std::endl;

		if(from_ephemeris)
		{
			receiver_clockdiff += Gtdr.GetData(3, 0);
		}
		else
		{
			// Do nothing
		}

		diff = ECEF_Frame(Gtdr).Distance(ECEF_Frame(0, 0, 0));

		if (j > max_loop)
		{
			break;
		}
		else
		{
			//Do nothing
		}
		j++;
	}

	return ans;
}

void Calculate_Position::GetCurrentSatellites(ECEF_Frame position, long double clock_diff)
{
	int i = 0;

	satellites.clear();
	original_distance.clear();
	clockdiff.clear();
	distance.clear();

	modifiedCurrent = GPS_Time(current.GetWeek(), current.GetSecond() - clock_diff / IS_GPS_200::C_velocity, current.GetLeapSecond());

	std::map<int, long double>::iterator current_dist_it = psudodistance.begin();
	for (std::map <int, Ephemeris>::iterator it = ephemeris.begin(); it != ephemeris.end(); it++)
	{
		for (std::map<int, long double>::iterator dist_it = current_dist_it; dist_it != psudodistance.end(); dist_it++)
		{
			if (dist_it->first == it->first)
			{
				original_distance.push_back(dist_it->second);
				long double r = dist_it->second - clock_diff;
				long double satellite_clock = (it->second).GetClock(modifiedCurrent, r);
				r = dist_it->second - clock_diff + satellite_clock * IS_GPS_200::C_velocity;
				satellite_clock = (it->second).GetClock(modifiedCurrent, r);
				ECEF_Frame satellite_position = (it->second).GetPosition(modifiedCurrent, r);
				satellites.push_back(satellite_position);
				clockdiff.push_back(satellite_clock);
				distance.push_back(satellite_position.Distance(position));
				current_dist_it = dist_it;
				i++;
				break;
			}
		}
	}


	number_of_satellites = i;

	from_ephemeris = true;

	valid = true;

}
