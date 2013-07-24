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
 * ENU_Frame.h
 *
 *  Created on: 2013/06/11
 *      Author: bun
 */

#ifndef ENU_FRAME_H_
#define ENU_FRAME_H_

#include "WGS84_Frame.h"

class ENU_Frame
{

public:
	ENU_Frame();
	ENU_Frame(long double e_enu, long double n_enu, long double u_enu, const WGS84_Frame &wgs84_orig);
	ENU_Frame(const WGS84_Frame wgs84_f, const WGS84_Frame wgs84_orig);
	virtual ~ENU_Frame();

	WGS84_Frame GetPosition()
	{
		return position;
	};

	WGS84_Frame GetOrigin()
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
	WGS84_Frame position;
	WGS84_Frame origin;
	long double e;
	long double n;
	long double u;


};

#endif /* ENU_FRAME_H_ */
