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
 * TropoSphere.h
 *
 *  Created on: 2013/07/02
 *      Author: bun
 */

#ifndef TROPOSPHERE_H_
#define TROPOSPHERE_H_

#include "ENU_Frame.h"

namespace Tropo
{
	static const long double Tropo_Delay_Zenith = 2.47;
	static const long double Tropo_Scale_Height = 1.0 / 2.3e-5;
}

class TropoSphere
{
public:
	TropoSphere();
	TropoSphere(const TropoSphere &tropo);
	virtual ~TropoSphere();

	static long double GetTropoSphereCollection(ECEF_Frame satellitePosition, ECEF_Frame userPosition);

private:

};


#endif /* TROPOSPHERE_H_ */
