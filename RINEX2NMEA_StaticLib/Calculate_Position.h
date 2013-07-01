/*
 * Calculate_Position.h
 *
 *  Created on: 2013/06/17
 *      Author: bun
 */

#ifndef CALCULATE_POSITION_H_
#define CALCULATE_POSITION_H_

#include "ECEF_Frame.h"
#include "Gaussian_Elimination.h"
#include "Ephemeris.h"
#include <iostream>
#include <cmath>
#include <vector>

class Calculate_Position
{
public:
	Calculate_Position();
	Calculate_Position(const Calculate_Position &cal);
	Calculate_Position(std::vector<ECEF_Frame> sats, Matrix dist, const int n_sats);
	Calculate_Position(std::map<int, Ephemeris> ephemeris, Matrix dist, GPS_Time currentTime);
	virtual ~Calculate_Position();

	ECEF_Frame GetPosition();

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
	std::vector<ECEF_Frame> satellites;
	Matrix distance;
	Matrix clockdiff;
	bool from_ephemeris;
	bool valid;
	GPS_Time current;

	const static long double max_diff = 1.0e8;
	const static long double min_diff = 1.0e-5;
	const static int max_loop = 10;
};


#endif /* CALCULATE_POSITION_H_ */
