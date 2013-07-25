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
 * WGS84_Frame.h
 *
 *  Created on: 2013/06/10
 *      Author: bun
 */

#ifndef WGS84_FRAME_H_
#define WGS84_FRAME_H_
#include "ECEF_Frame.h"
#include "IS-GPS-200.h"
#include <cmath>

namespace WGS84
{
	static const long double Pi = 6*asin( 0.5 );
	static const long double R_Earth = 6378137.0; // From NIMA TR8350.2 Third Edition (03 Jan. 2000) p. 3-5
	static const long double F_Earth = 298.257223563; // From NIMA TR8350.2 Third Edition (03 Jan. 2000) p. 3-5

}

class WGS84_Frame : public ECEF_Frame
{

public:
	WGS84_Frame();
	WGS84_Frame(long double Lat, long double Longi, long double E_Height);
	WGS84_Frame(const WGS84_Frame & wgs84_f);
	WGS84_Frame(const ECEF_Frame &ecef_f);
	virtual ~WGS84_Frame();


	long double GetLat()
	{
		return Latitude;
	};

	long double GetLongi()
	{
		return Longitude;
	};

	long double GetE_Height()
	{
		return Elipisoidal_Height;
	}

	static long double Rad2Deg(long double rad)
	{
		return rad / WGS84::Pi * 180.0L;
	};

	static long double Deg2Rad(long double deg)
	{
		return deg / 180.0L * WGS84::Pi;
	};

	static long double Rad2Sc(long double rad)
	{
		return rad / WGS84::Pi;
	};

	static long double Sc2Rad(long double sc)
	{
		return WGS84::Pi * sc;
	};

protected:
	long double Latitude;
	long double Longitude;
	long double Elipisoidal_Height;

	void Set(long double Lat, long double Longi, long double E_Height);

};

#endif /* WGS84_FRAME_H_ */
