/*
 * ECEF_Frame.cpp
 *
 *  Created on: 2013/06/10
 *      Author: bun
 */

#include <cmath>
#include "ECEF_Frame.h"

CECEF_Frame::CECEF_Frame()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}
CECEF_Frame::CECEF_Frame(long double x0, long double y0, long double z0)
{
	x = x0;
	y = y0;
	z = z0;
}

CECEF_Frame::CECEF_Frame(const CECEF_Frame &ecef_f)
{
	this->x = ecef_f.x;
	this->y = ecef_f.y;
	this->z = ecef_f.z;
}

CECEF_Frame::~CECEF_Frame()
{
	// Do nothing
}

long double CECEF_Frame::Distance(const CECEF_Frame &origin)
{
	return sqrt(pow((x - origin.x),2) + pow((y - origin.y), 2) + pow((z - origin.z), 2));
}

