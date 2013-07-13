/*
 * IonoSphere.cpp
 *
 *  Created on: 2013/07/02
 *      Author: bun
 */

#include "IonoSphere.h"

IonoSphere::IonoSphere()
{
	Ionosphere_parameter.clear();
}


IonoSphere::IonoSphere(const IonoSphere & ion)
{
	Ionosphere_parameter = ion.Ionosphere_parameter;
}

IonoSphere::~IonoSphere()
{
	Ionosphere_parameter.clear();
}

void IonoSphere::SetData(const long double dat, ION col)
{
	Ionosphere_parameter.insert(std::map<ION, long double>::value_type(col, dat));
}


long double IonoSphere::GetData(ION col)
{
	return Ionosphere_parameter[col];
}

long double IonoSphere::GetIonoSphereDelayCorrection(ECEF_Frame satellitePosition, ECEF_Frame userPosition, GPS_Time currentTime)
{
	if (IsValid())
	{
		long double elevation = WGS84_Frame::Rad2Sc(ENU_Frame(satellitePosition, userPosition).GetElevation());
		long double azimuth = WGS84_Frame::Rad2Sc(ENU_Frame(satellitePosition, userPosition).GetAzimuth());

		WGS84_Frame userpos = WGS84_Frame(userPosition);
		long double psi = 0.0137 / (elevation + 0.11) - 0.022;
		long double phi_i = WGS84_Frame::Rad2Sc(userpos.GetLat()) + psi * cos(azimuth * IS_GPS_200::GPS_Pi);

		if (phi_i > 0.416)
		{
			phi_i = 0.416;
		}
		else if (phi_i < -0.416)
		{
			phi_i = -0.416;
		}

		long double lam_i = WGS84_Frame::Rad2Sc(userpos.GetLongi()) + psi * sin(azimuth * IS_GPS_200::GPS_Pi) / cos(phi_i * WGS84::Pi);
		long double phi_m = phi_i + 0.064 * cos((lam_i - 1.617) * IS_GPS_200::GPS_Pi);

		// Local time
		long double lt = GPS_Time::Seconds_in_Day / 2.0 * lam_i + currentTime.GetSecond();
		while (lt > GPS_Time::Seconds_in_Day)
		{
			lt -= GPS_Time::Seconds_in_Day;
		}
		while (lt < 0.0L)
		{
			lt += GPS_Time::Seconds_in_Day;
		}

		// Amplitude

		long double amp = Ionosphere_parameter[A0] + Ionosphere_parameter[A1] * phi_m
				+ Ionosphere_parameter[A2] * pow(phi_m, 2) + Ionosphere_parameter[A3] * pow(phi_m, 3);
		long double per = Ionosphere_parameter[B0] + Ionosphere_parameter[B1] * phi_m
				+ Ionosphere_parameter[B2] * pow(phi_m, 2) + Ionosphere_parameter[A3] * pow(phi_m, 3);

		if (amp < 0.0)
		{
			amp = 0.0;
		}
		else
		{
			// Do nothing
		}

		if (per < Ion::PER_Min)
		{
			per = Ion::PER_Min;
		}
		else
		{
			// Do nothing
		}

		long double x = 0.53 - elevation;
		long double f = 1.0 + 16.0 * x * x * x;

		x = 2.0 * IS_GPS_200::GPS_Pi * (lt - Ion::MAX_Delay_time) / per;
		while (x > IS_GPS_200::GPS_Pi)
		{
			x -= 2.0 * IS_GPS_200::GPS_Pi;
		}
		while (x < -1.0 * IS_GPS_200::GPS_Pi)
		{
			x += 2.0 * IS_GPS_200::GPS_Pi;
		}

		long double y = 0.0L;
		if(fabs(x) < 1.57)
		{
			y = amp * (1.0 - x * x * (0.5 + x * x / 24.0));
		}
		else
		{
			y = 0.0;
		}

		return -f * (Ion::Night_Delay + y) * IS_GPS_200::C_velocity;
	}
	else
	{
		return 0.0;
	}
}

