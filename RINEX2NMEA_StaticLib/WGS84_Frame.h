/*
 * WGS84_Frame.h
 *
 *  Created on: 2013/06/10
 *      Author: bun
 */

#ifndef WGS84_FRAME_H_
#define WGS84_FRAME_H_
#include "ECEF_Frame.h"

class CWGS84_Frame : public CECEF_Frame
{
	friend CWGS84_Frame ECEF2WGS84(const CECEF_Frame &ecef_f);
	friend CWGS84_Frame ECEF2WGS84(const long double x0, const long double y0, const long double z0);
	friend CECEF_Frame WGS842ECEF(const CWGS84_Frame &wgs84_f);
	friend CECEF_Frame WGS842ECEF(const long double Lat, const long double Longi, const long double G_Height);

public:
	CWGS84_Frame();
	CWGS84_Frame(long double Lat, long double Longi, long double G_Height);
	CWGS84_Frame(const CWGS84_Frame & wgs84_f);
	CWGS84_Frame(const CECEF_Frame &ecef_f);
	virtual ~CWGS84_Frame();

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

protected:
	static const long double GPS_Pi = 3.1415926535898; // From IS-GPS-200G(05 Sep. 2012) p.154
	static const long double C_velocity = 2.99792458e8; // From IS-GPS-200G(05 Sep. 2012) p.126
	static const long double GMe = 3986004.418e8; // From NIMA TR8350.2 Third Edition (03 Jan. 2000) p. 3-3
	static const long double Omega_E = 7292115e-11; // From NIMA TR8350.2 Third Edition (03 Jan. 2000) p. 3-4
	static const long double R_Earth = 6378137.0; // From NIMA TR8350.2 Third Edition (03 Jan. 2000) p. 3-5
	static const long double F_Earth = 298.257223563; // From NIMA TR8350.2 Third Edition (03 Jan. 2000) p. 3-5

	long double Latitude;
	long double Longitude;
	long double Geoidal_Height;

	void Set(long double Lat, long double Longi, long double G_Height);

	long double Rad2Deg(long double rad)
	{
		return rad / GPS_Pi * 180.0L;
	};
	long double Deg2Rad(long double deg)
	{
		return deg / 180.0L * GPS_Pi;
	};
	long double Rad2Sc(long double rad)
	{
		return rad / GPS_Pi;
	};
	long double Sc2Rad(long double sc)
	{
		return GPS_Pi * sc;
	};
};

#endif /* WGS84_FRAME_H_ */
