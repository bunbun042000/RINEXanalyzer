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

}

Calculate_Position::Calculate_Position(std::vector<ECEF_Frame> sats, Matrix dist, const int n_sats)
{

	valid = false;

	if ((n_sats != 0) && (dist.GetMaxRow() == n_sats))
	{
		number_of_satellites = n_sats;
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

Calculate_Position::Calculate_Position(std::map<int, Ephemeris> ephemeris, Matrix dist, GPS_Time currentTime)
{

	number_of_satellites = ephemeris.size();

	if((number_of_satellites != 0) && (dist.GetMaxRow() == number_of_satellites))
	{
		// Do nothing
	}
	else
	{
		return;
	}

	clockdiff = Matrix(number_of_satellites, 1);
	current = currentTime;

	int i = 0;
	for (std::map <int, Ephemeris>::iterator it = ephemeris.begin(); it != ephemeris.end(); it++)
	{
		satellites.push_back((it->second).GetPosition(current));
		clockdiff.SetData((it->second).GetClock(current), i, 0);
		i++;
	}

	from_ephemeris = true;

	distance = dist;
	valid = true;
}

Calculate_Position::~Calculate_Position()
{

	number_of_satellites = 0;
	satellites.clear();

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
		// Create Observation matrix
		for (i = 0; i < number_of_satellites; i++)
		{
			r = satellites[i].Distance(ans);
			G.SetData((ans.GetX() - satellites[i].GetX())/r, i, 0);
			G.SetData((ans.GetY() - satellites[i].GetY())/r, i, 1);
			G.SetData((ans.GetZ() - satellites[i].GetZ())/r, i, 2);
			G.SetData(1.0, i, 3);

			if(from_ephemeris)
			{
				dr.SetData(distance.GetData(i, 0) + clockdiff.GetData(i, 0) * WGS84_Frame::C_velocity - r - receiver_clockdiff, i, 0);
			}
			else
			{
				dr.SetData((distance.GetData(i, 0) - r), i, 0);
			}
		}

		Matrix Gt = G.Tranposed();
		Matrix GtG = Gt * G;
		Matrix Gtdr = Gt * dr;

		Gaussian_Elimination gauss = Gaussian_Elimination(GtG, Gtdr);

		Gtdr = gauss.GetAnswer();

		ans = ECEF_Frame(ans.GetX() + Gtdr.GetData(0, 0), ans.GetY() + Gtdr.GetData(1, 0), ans.GetZ() + Gtdr.GetData(2, 0));

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
