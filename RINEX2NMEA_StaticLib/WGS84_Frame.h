/*
 * WGS84_Frame.h
 *
 *  Created on: 2013/06/10
 *      Author: bun
 */

#ifndef WGS84_FRAME_H_
#define WGS84_FRAME_H_
#include "ECEF_Frame.h"

class WGS84_Frame : public ECEF_Frame
{
	friend WGS84_Frame ECEF2WGS84(const ECEF_Frame &ecef_f);
	friend WGS84_Frame ECEF2WGS84(const long double x0, const long double y0, const long double z0);
	friend ECEF_Frame WGS842ECEF(const WGS84_Frame &wgs84_f);
	friend ECEF_Frame WGS842ECEF(const long double Lat, const long double Longi, const long double G_Height);

public:
	WGS84_Frame();
	WGS84_Frame(long double Lat, long double Longi, long double G_Height);
	WGS84_Frame(const WGS84_Frame & wgs84_f);
	WGS84_Frame(const ECEF_Frame &ecef_f);
	virtual ~WGS84_Frame();

	static const long double GPS_Pi = 3.1415926535898; // From IS-GPS-200G(05 Sep. 2012) p.154
	static const long double C_velocity = 2.99792458e8; // From IS-GPS-200G(05 Sep. 2012) p.126
	static const long double GMe = 3986004.418e8; // From NIMA TR8350.2 Third Edition (03 Jan. 2000) p. 3-3
	static const long double Omega_E = 7292115e-11; // From NIMA TR8350.2 Third Edition (03 Jan. 2000) p. 3-4
	static const long double R_Earth = 6378137.0; // From NIMA TR8350.2 Third Edition (03 Jan. 2000) p. 3-5
	static const long double F_Earth = 298.257223563; // From NIMA TR8350.2 Third Edition (03 Jan. 2000) p. 3-5

	long double GetLat()
	{
		return Latitude;
	};

	long double GetLongi()
	{
		return Longitude;
	};

	long double GetG_Height()
	{
		return Geoidal_Height;
	}

	static long double Rad2Deg(long double rad)
	{
		return rad / GPS_Pi * 180.0L;
	};

	static long double Deg2Rad(long double deg)
	{
		return deg / 180.0L * GPS_Pi;
	};

	static long double Rad2Sc(long double rad)
	{
		return rad / GPS_Pi;
	};

	static long double Sc2Rad(long double sc)
	{
		return GPS_Pi * sc;
	};

protected:
	long double Latitude;
	long double Longitude;
	long double Geoidal_Height;

	void Set(long double Lat, long double Longi, long double G_Height);

};

#endif /* WGS84_FRAME_H_ */
