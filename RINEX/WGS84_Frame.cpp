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
 * WGS84_Frame.cpp
 *
 *  Created on: 2013/06/10
 *      Author: bun
 */

#include "WGS84_Frame.h"
#include "ECEF_Frame.h"
#include <cmath>

WGS84_Frame::WGS84_Frame() : ECEF_Frame()
{
	Latitude = 0.0;
	Longitude = 0.0;
	Elipisoidal_Height = 0.0;

}

WGS84_Frame::WGS84_Frame(long double Lat, long double Longi, long double E_Height) : ECEF_Frame()
{
	Latitude = 0.0;
	Longitude = 0.0;
	Elipisoidal_Height = 0.0;

	this->Set(Lat, Longi, E_Height);

}

WGS84_Frame::WGS84_Frame(const WGS84_Frame &wgs84_f) : ECEF_Frame(wgs84_f)
{
	this->Latitude = wgs84_f.Latitude;
	this->Longitude = wgs84_f.Longitude;
	this->Elipisoidal_Height = wgs84_f.Elipisoidal_Height;
}

WGS84_Frame::WGS84_Frame(const ECEF_Frame &ecef_f) : ECEF_Frame(ecef_f)
{
	Latitude = 0.0;
	Longitude = 0.0;
	Elipisoidal_Height = 0.0;

	if (Distance(ECEF_Frame(0.0L, 0.0L, 0.0L)) < 1.0e-10)
	{
		Latitude = 0.0;
		Longitude = 0.0;
		Elipisoidal_Height = WGS84::R_Earth * (-1);
	}
	else
	{
		long double f = 1.0 / WGS84::F_Earth;	// Reciprocal of Flattening
		long double a = WGS84::R_Earth;			// Semi-major Axis
		long double e2 = f * (2.0 - f);			// Eccentricity^2
		long double b = a * (1.0 - f);			// Semi-minor Axis
		long double p = sqrt(x * x + y * y);
		long double r = sqrt(p * p + z * z);

		long double h = pow(a, 2) - pow(b, 2);
		long double t = atan2(z * (1 - f + e2 * a / r), p);
		long double sint = sin(t);
		long double cost = cos(t);

		Latitude = atan2(z + h / b * sint * sint *sint, p - h / a * cost * cost * cost);
		Longitude = atan2(y, x);
		Elipisoidal_Height = p * cos(Latitude) + z * sin(Latitude) - a * sqrt(1.0 - e2 * sin(Latitude) * sin(Latitude));
	}

}

WGS84_Frame::~WGS84_Frame()
{
	//Do Nothing
}

void WGS84_Frame::Set(long double Lat, long double Longi, long double E_Height)
{

	Latitude = Lat;
	Longitude = Longi;
	Elipisoidal_Height = E_Height;

	long double f = 1.0 / WGS84::F_Earth;	// Reciprocal of Flattening
	long double a = WGS84::R_Earth;			// Semi-major Axis
	long double e2 = f * (2.0 - f);			// Eccentricity^2

	long double n = a / sqrt(1.0 - e2 * sin(Latitude) * sin(Latitude));

	x = (n + Elipisoidal_Height) * cos(Latitude) * cos(Longitude);
	y = (n + Elipisoidal_Height) * cos(Latitude) * sin(Longitude);
	z = (n * (1.0 - e2) + Elipisoidal_Height) * sin(Latitude);

}

