/*
 * TropoSphere.h
 *
 *  Created on: 2013/07/02
 *      Author: bun
 */

#ifndef TROPOSPHERE_H_
#define TROPOSPHERE_H_

#include "ENU_Frame.h"

class TropoSphere
{
public:
	TropoSphere();
	TropoSphere(const TropoSphere &tropo);
	virtual ~TropoSphere();

	static long double GetTropoSphereCollection(ECEF_Frame satellitePosition, ECEF_Frame userPosition);

private:
	static const long double Tropo_Delay_Zenith = 2.47;
	static const long double Tropo_Scale_Height = 1.0 / 2.3e-5;

};


#endif /* TROPOSPHERE_H_ */
