/*
 * IonoSphere.h
 *
 *  Created on: 2013/07/02
 *      Author: bun
 */

#ifndef IONOSPHERE_H_
#define IONOSPHERE_H_

#include <map>
#include <cmath>

#include "ENU_Frame.h"
#include "GPS_Time.h"

class IonoSphere
{
public:
	IonoSphere();
	IonoSphere(const IonoSphere & ion);
	virtual ~IonoSphere();

	enum ION {
		A0,
		A1,
		A2,
		A3,
		B0,
		B1,
		B2,
		B3
	};

	void SetData(const long double dat, ION col);
	long double GetData(ION col);

	bool IsValid()
	{
		if (Ionosphere_parameter.size() == 8)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	long double GetIonoSphereDelayCorrection(ECEF_Frame satellitePosition, ECEF_Frame userPosition, GPS_Time currentTime);

private:
	std::map <ION, long double> Ionosphere_parameter;


	static const long double PER_Min = 72000.0L;
	static const long double Night_Delay = 5.0e-9;
	static const long double MAX_Delay_time = 50400.0L;


};


#endif /* IONOSPHERE_H_ */
