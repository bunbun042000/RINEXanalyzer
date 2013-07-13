/*
 * Calculate_Position.h
 *
 *  Created on: 2013/06/17
 *      Author: bun
 */

#ifndef CALCULATE_POSITION_H_
#define CALCULATE_POSITION_H_

#include <iostream>
#include <cmath>
#include <vector>

#include "IS-GPS-200.h"
#include "ECEF_Frame.h"
#include "Gaussian_Elimination.h"
#include "Ephemeris.h"
#include "IonoSphere.h"
#include "TropoSphere.h"
#include "PsudoRange.h"
#include "ReceiverOutput.h"

namespace calc_pos
{
	const static long double max_diff = 1.0e8;
	const static long double min_diff = 1.0e-5;
	const static int max_loop = 10;
}

class Calculate_Position
{
public:
	Calculate_Position();
	Calculate_Position(std::vector<ECEF_Frame> sats, std::vector<long double> dist, const int n_sats);
	Calculate_Position(std::map<int, Ephemeris> ephemeris, std::map<int, PsudoRange> range, PsudoRange::MeansType _type, GPS_Time currentTime, IonoSphere ion);
	virtual ~Calculate_Position();

	ReceiverOutput GetPosition();


private:
	std::map<int, Ephemeris> ephemeris;
	std::map<int, PsudoRange> originalpsudodistance;

	GPS_Time current;
	IonoSphere ionosphere;
	PsudoRange::MeansType type;

};


#endif /* CALCULATE_POSITION_H_ */