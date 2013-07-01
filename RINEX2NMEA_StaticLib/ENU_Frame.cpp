/*
 * ENU_Frame.cpp
 *
 *  Created on: 2013/06/11
 *      Author: bun
 */

#include "ENU_Frame.h"
#include <cmath>

CENU_Frame::CENU_Frame()
{
	origin = WGS84_Frame();

	e = 0.0L;
	n = 0.0L;
	u = 0.0L;

}

CENU_Frame::CENU_Frame(long double e_enu, long double n_enu, long double u_enu, const WGS84_Frame &wgs84_orig)
{
	long double s1, c1, s2, c2;
	long double x0, y0, z0;

	e = e_enu;
	n = n_enu;
	u = u_enu;

	origin = wgs84_orig;


	s1 = sin(origin.GetLongi());
	c1 = cos(origin.GetLongi());
	s2 = sin(origin.GetLat());
	c2 = cos(origin.GetLat());

	x0 = -e * s1 - n * c1 * s2 + u * c1 * c2;
	y0 = e * c1 - n * s1 * s2 + u *s1 * c2;
	z0 = n * c2 + u * s2;

	x0 += origin.GetX();
	y0 += origin.GetY();
	z0 += origin.GetZ();

	position = WGS84_Frame(ECEF_Frame(x0, y0, z0));

}

CENU_Frame::CENU_Frame(const WGS84_Frame wgs84_f, const WGS84_Frame wgs84_orig)
{
	long double x1, y1, z1;
	long double s1, s2, c1, c2;

	position = wgs84_f;
	origin = wgs84_orig;

	x1 = position.GetX() - origin.GetX();
	y1 = position.GetY() - origin.GetY();
	z1 = position.GetZ() - origin.GetZ();

	s1 = sin(origin.GetLongi());
	c1 = cos(origin.GetLongi());
	s2 = sin(origin.GetLat());
	c2 = cos(origin.GetLat());

	e = -x1 * s1 + y1 * c1;
	n = -x1 * c1 * s2 - y1 * s1 * s2 + z1 * c2;
	u = x1 * c1 * c2 + y1 * s1 * c2 + z1 * s2;

}

CENU_Frame::~CENU_Frame()
{
	// Do nothing
}

long double CENU_Frame::GetElevation()
{

	return atan2(u, sqrt(e * e + n * n));

}

long double CENU_Frame::GetAzimuth()
{

	return atan2(e, n);

}
