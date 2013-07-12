/*
 * ECEF_Frame.cpp
 *
 *  Created on: 2013/06/10
 *      Author: bun
 */

#include <cmath>
#include "ECEF_Frame.h"
#include <iostream>
ECEF_Frame::ECEF_Frame()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}
ECEF_Frame::ECEF_Frame(long double x0, long double y0, long double z0)
{
	x = x0;
	y = y0;
	z = z0;
}

ECEF_Frame::ECEF_Frame(const ECEF_Frame &orig)
{
	x = orig.x;
	y = orig.y;
	z = orig.z;
}

ECEF_Frame::ECEF_Frame(Matrix &m)
{
	x = m.GetData(0, 0);
	y = m.GetData(1, 0);
	z = m.GetData(2, 0);
}

ECEF_Frame::~ECEF_Frame()
{
	// Do nothing
}


long double ECEF_Frame::Distance(const ECEF_Frame &origin)
{
	return sqrt((x - origin.x) * (x - origin.x) + (y - origin.y) * (y - origin.y) + (z - origin.z) * (z - origin.z));
}

ECEF_Frame &ECEF_Frame::operator*(const long double r)
{
	x *= r;
	y *= r;
	z *= r;
	return *this;
}
ECEF_Frame ECEF_Frame::operator+(const ECEF_Frame &pos)
{
	ECEF_Frame posA;
	posA.x = x + pos.x;
	posA.y = y + pos.y;
	posA.z = z + pos.z;
	return posA;
}

ECEF_Frame &ECEF_Frame::operator+=(const ECEF_Frame &pos)
{
	x += pos.x;
	y += pos.y;
	z += pos.z;
	return *this;
}

ECEF_Frame operator*(long double r, ECEF_Frame &pos)
{
	return pos * r;
}
