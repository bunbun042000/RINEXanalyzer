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


class Calculate_Position
{
public:
	Calculate_Position();
	Calculate_Position(std::vector<ECEF_Frame> sats, std::vector<long double> dist, const int n_sats);
	Calculate_Position(std::map<int, Ephemeris> ephemeris, std::map<int, PsudoRange> range, PsudoRange::MeansType _type, GPS_Time currentTime, IonoSphere ion);
	virtual ~Calculate_Position();

	ReceiverOutput GetPosition();

	bool IsValid()
	{
	    std::vector<ECEF_Frame>::iterator begin;

		if (satellites.empty()){
			std::cerr << "satellites is not initialized!\n";
			return false;
		}
		else
		{
			begin = satellites.begin();
			if (fabs(begin->GetX()) < min_diff)
			{
				return false;
			}
			else
			{
				// Do nothing
			}
		}
		return valid;
	};

private:
	int number_of_satellites;
	std::map<int, Ephemeris> ephemeris;
	std::map<int, PsudoRange> psudodistance;
	std::vector<ECEF_Frame> satellites;
	std::vector<long double> distance;
	std::vector<long double> original_distance;
	std::vector<long double> clockdiff;
	std::vector<int> valid_PRN;
	bool from_ephemeris;
	bool valid;
	GPS_Time current;
	GPS_Time modifiedCurrent;
	IonoSphere ionosphere;
	PsudoRange::MeansType type;

	void GetCurrentSatellites(ECEF_Frame position, PsudoRange::MeansType _type, long double clockdiff);

	const static long double max_diff = 1.0e8;
	const static long double min_diff = 1.0e-5;
	const static int max_loop = 10;
};


#endif /* CALCULATE_POSITION_H_ */
