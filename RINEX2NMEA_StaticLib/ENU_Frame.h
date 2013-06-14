/*
 * ENU_Frame.h
 *
 *  Created on: 2013/06/11
 *      Author: bun
 */

#ifndef ENU_FRAME_H_
#define ENU_FRAME_H_

#include "WGS84_Frame.h"

class CENU_Frame
{

public:
	CENU_Frame();
	CENU_Frame(const CENU_Frame &enu_f);
	CENU_Frame(long double x_enu, long double y_enu, long double z_enu, const CWGS84_Frame &wgs84_orig);
	CENU_Frame(const CWGS84_Frame wgs84_f, const CWGS84_Frame wgs84_orig);
	virtual ~CENU_Frame();

	CWGS84_Frame GetPosition()
	{
		return position;
	};

	CWGS84_Frame GetOrigin()
	{
		return origin;
	};

	long double GetE()
	{
		return e;
	};

	long double GetN()
	{
		return n;
	};

	long double GetU()
	{
		return u;
	};

	long double GetElevation();
	long double GetAzimuth();

protected:
	CWGS84_Frame position;
	CWGS84_Frame origin;
	long double e;
	long double n;
	long double u;


};

#endif /* ENU_FRAME_H_ */
