/*
 * WGS84_Frame.cpp
 *
 *  Created on: 2013/06/10
 *      Author: bun
 */

#include "WGS84_Frame.h"
#include "ECEF_Frame.h"
#include <cmath>

CWGS84_Frame::CWGS84_Frame() : CECEF_Frame()
{
	Latitude = 0.0;
	Longitude = 0.0;
	Geoidal_Height = 0.0;

}

CWGS84_Frame::CWGS84_Frame(long double Lat, long double Longi, long double G_Height) : CECEF_Frame()
{
	Latitude = 0.0;
	Longitude = 0.0;
	Geoidal_Height = 0.0;

	this->Set(Lat, Longi, G_Height);

}

CWGS84_Frame::CWGS84_Frame(const CWGS84_Frame &wgs84_f) : CECEF_Frame(wgs84_f)
{
	this->Latitude = wgs84_f.Latitude;
	this->Longitude = wgs84_f.Longitude;
	this->Geoidal_Height = wgs84_f.Geoidal_Height;
}

CWGS84_Frame::CWGS84_Frame(const CECEF_Frame &ecef_f) : CECEF_Frame(ecef_f)
{
	Latitude = 0.0;
	Longitude = 0.0;
	Geoidal_Height = 0.0;

	long double a,b,e,f,n,h,p,t,sint,cost;

	if (Distance(CECEF_Frame(0.0L, 0.0L, 0.0L)) < 1.0e-10)
	{
		Latitude = 0.0;
		Longitude = 0.0;
		Geoidal_Height = R_Earth * (-1);
	}
	else
	{
		f = 1.0 / F_Earth;			// Reciprocal of Flattening
		a = R_Earth;				// Semi-major Axis
		b = a * (1.0 - f);			// Semi-minor Axis
		e = sqrt(f * (2.0 - f));	// Eccentricity

		h = pow(a, 2) - pow(b, 2);
		p = sqrt(pow(x, 2) + pow(y, 2));
		t = atan2(z * a, p * b);
		sint = sin(t);
		cost = cos(t);

		Latitude = atan2(z + h / b * sint * sint *sint, p - h / a * cost * cost * cost);
		n = a / sqrt(1.0 - e * e* sin(Latitude) * sin(Latitude));
		Longitude = atan2(y, x);
		Geoidal_Height = p / cos(Latitude) - n;
	}

}

CWGS84_Frame::~CWGS84_Frame()
{
	//Do Nothing
}

void CWGS84_Frame::Set(long double Lat, long double Longi, long double G_Height)
{
	long double a, b, e, f, n;

	Latitude = Lat;
	Longitude = Longi;
	Geoidal_Height = G_Height;

	f = 1.0 / F_Earth;			// Reciprocal of Flattening
	a = R_Earth;				// Semi-major Axis
	b = a * (1.0 - f);			// Semi-minor Axis
	e = sqrt(f * (2.0 - f));	// Eccentricity

	n = a / sqrt(1.0 - e * e * sin(Latitude) * sin(Latitude));

	x = (n + Geoidal_Height) * cos(Latitude) * cos(Longitude);
	y = (n + Geoidal_Height) * cos(Latitude) * sin(Longitude);
	z = (n * (1.0 - e * e) + Geoidal_Height) * sin(Latitude);

}

