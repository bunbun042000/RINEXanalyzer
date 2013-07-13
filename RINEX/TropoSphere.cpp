/*
 * TropoSphere.cpp
 *
 *  Created on: 2013/07/02
 *      Author: bun
 */

#include "TropoSphere.h"

long double TropoSphere::GetTropoSphereCollection(ECEF_Frame satellitePosition, ECEF_Frame userPosition)
{
	long double d;

	WGS84_Frame userpos = WGS84_Frame(userPosition);

	if (userpos.GetG_Height() < 0.0)
	{
		d = 1.0;
	}
	else if (userpos.GetG_Height() > Tropo::Tropo_Scale_Height)
	{
		d = 0.0;
	}
	else
	{
		d = 1.0 - userpos.GetG_Height() / Tropo::Tropo_Scale_Height;
	}

	return -1.0 * Tropo::Tropo_Delay_Zenith * d * d * d * d * d
			/ (sin(ENU_Frame(satellitePosition, userPosition).GetElevation()) + 0.0121);
}



