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
 * Ephemeris.cpp
 *
 *  Created on: 2013/06/20
 *      Author: bun
 */

#include "Ephemeris.h"
#include <iostream>
#include <iomanip>

Ephemeris::Ephemeris()
{
	// Do nothing
	PRN = 0;
	data.clear();
}

Ephemeris::Ephemeris(const int prn)
{
	PRN = prn;
	data.clear();
}

Ephemeris::Ephemeris(const Ephemeris &rin)
{
	data = rin.data;
	time_of_clock = rin.time_of_clock;
	transmission_time = rin.transmission_time;
	time_of_ephemeris = rin.time_of_ephemeris;
	PRN = rin.PRN;
}

Ephemeris::~Ephemeris()
{
	data.clear();
}

void Ephemeris::SetData(const long double dat, Ephemeris_column col)
{

	if (col == TOC)
	{
		// Do nothing
	}
	else if (col == TOE)
	{
		time_of_ephemeris = GPS_Time(time_of_clock.GetWeek(), dat, time_of_clock.GetLeapSecond());
	}
	else if (col == TOT)
	{
		transmission_time = GPS_Time(time_of_clock.GetWeek(), dat, time_of_clock.GetLeapSecond());
	}
	else if (col == week)
	{
		long double t = (time_of_clock.GetWeek() - dat) * GPS_Time::Seconds_in_week;
		t += time_of_clock.GetSecond();
		time_of_clock = GPS_Time((int)dat, t, time_of_clock.GetLeapSecond());
	}
	else if (col == NONE1 || col == NONE2)
	{
		// Do nothing
	}
	else
	{
		data.insert(std::map<Ephemeris_column, long double>::value_type(col, dat));
	}

}

long double Ephemeris::GetData(Ephemeris_column col)
{

	if (col == NONE1 || col == NONE2 || col == END)
	{
		return 0.0L;
	}
	else if (col == TOC)
	{
		return time_of_clock.GetSecond();
	}
	else if (col == TOE)
	{
		return time_of_ephemeris.GetSecond();
	}
	else if (col == TOT)
	{
		return transmission_time.GetSecond();
	}
	else if (col == week)
	{
		return time_of_clock.GetWeek();
	}
	else
	{
		return data[col];

	}

}

long double Ephemeris::GetClock(GPS_Time currentTime, const long double psudorange)
{

	long double Ek = CalculateEk(currentTime, psudorange);

	long double tr = -2.0 * sqrt(IS_GPS_200::GMe) / IS_GPS_200::C_velocity / IS_GPS_200::C_velocity
			* data[eccentricity] * data[sqrtA] * sin(Ek);

	long double tk0 = currentTime - time_of_clock;
	long double tk = tk0 - psudorange / IS_GPS_200::C_velocity;

	long double dt = data[Af0] + data[Af1] * tk + data[Af2] * tk * tk;

	return dt + tr - data[TGD];
}

ECEF_Frame Ephemeris::GetPosition(GPS_Time currentTime, const long double psudorange)
{

	long double e = data[eccentricity];

	long double tk0 = currentTime - time_of_ephemeris;
	long double tk = tk0 - psudorange / IS_GPS_200::C_velocity;

	long double Ek = CalculateEk(currentTime, psudorange);

	long double rk = data[sqrtA] * data[sqrtA] * (1.0 - e * cos(Ek));
	long double vk = atan2((sqrt(1.0 - e * e) * sin(Ek)), (cos(Ek) - e));
	long double pk = vk + data[omega];

	long double d_uk = data[Cus] * sin(2.0 * pk) + data[Cuc] * cos(2.0 * pk);
	long double d_rk = data[Crs] * sin(2.0 * pk) + data[Crc] * cos(2.0 * pk);
	long double d_ik = data[Cis] * sin(2.0 * pk) + data[Cic] * cos(2.0 * pk);
	long double uk = pk + d_uk;
	rk = rk + d_rk;
	long double ik = data[i0] + d_ik + data[di] * tk;

	long double xk = rk * cos(uk);
	long double yk = rk * sin(uk);

	// ascending node
	long double Omegak = data[OMEGA0] + (data[OMEGA_dot] - IS_GPS_200::Omega_E) * tk0
			- IS_GPS_200::Omega_E * time_of_ephemeris.GetSecond();

	long double x = xk * cos(Omegak) - yk * sin(Omegak) * cos(ik);
	long double y = xk * sin(Omegak) + yk * cos(Omegak) * cos(ik);
	long double z = yk * sin(ik);


	ECEF_Frame sat_pos = ECEF_Frame(x, y, z);

//	tm tmbuf = currentTime.ToDate();
//	std::cout << std::setw(4) << std::right << std::setfill('0') << tmbuf.tm_year + 1900 << "-";
//	std::cout << std::setw(2) << std::right << std::setfill('0') << tmbuf.tm_mon + 1 << "-";
//	std::cout << std::setw(2) << std::right << std::setfill('0') << tmbuf.tm_mday << " ";
//	std::cout << std::setw(2) << std::right << std::setfill('0') << tmbuf.tm_hour << ":";
//	std::cout << std::setw(2) << std::right << std::setfill('0') << tmbuf.tm_min << ":";
//	std::cout << std::setw(2) << std::right << std::setfill('0') << tmbuf.tm_sec << std::endl;
//	std::cout << "PRN = " << PRN << std::endl;
//	std::cout << "x   = " << std::fixed << sat_pos.GetX() << std::endl;
//	std::cout << "y   = " << std::fixed << sat_pos.GetY() << std::endl;
//	std::cout << "z   = " << std::fixed << sat_pos.GetZ() << std::endl;

	return sat_pos;
}

long double Ephemeris::CalculateEk(GPS_Time currentTime, const long double psudorange)
{
	long double tk0 = currentTime - time_of_ephemeris;
	long double tk = tk0 - psudorange / IS_GPS_200::C_velocity;

	long double sqrt_A = data[sqrtA];
	long double e = data[eccentricity]; // Eccentricity
	long double n = sqrt(IS_GPS_200::GMe) / sqrt_A / sqrt_A / sqrt_A + data[d_n];
	long double Mk = data[M0] + n * tk; // mean anomaly
	long double Ek = Mk;
	for (int i = 0; i < 10; i++)
	{
		Ek = Mk + e * sin(Ek); // Kepler equation;
	}

	return Ek;
}
