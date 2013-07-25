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

	if (userpos.GetE_Height() < 0.0)
	{
		d = 1.0;
	}
	else if (userpos.GetE_Height() > Tropo::Tropo_Scale_Height)
	{
		d = 0.0;
	}
	else
	{
		d = 1.0 - userpos.GetE_Height() / Tropo::Tropo_Scale_Height;
	}

	return -1.0 * Tropo::Tropo_Delay_Zenith * d * d * d * d * d
			/ (sin(ENU_Frame(satellitePosition, userPosition).GetElevation()) + 0.0121);
}



