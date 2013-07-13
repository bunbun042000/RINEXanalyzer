/*
 * PsudoRange.cpp
 *
 *  Created on: 2013/07/03
 *      Author: bun
 */

#include "PsudoRange.h"

PsudoRange::PsudoRange()
{
	PRN = 0;
	observation.clear();
	event_flag = 0;
	satellitePosition = ECEF_Frame(0.0L, 0.0L, 0.0L);
	weight= 0.0L;
	calculateDistance = 0.0L;
}

PsudoRange::PsudoRange(const PsudoRange &psur)
{
	observation = psur.observation;
	current = psur.current;
	PRN = psur.PRN;
	event_flag = psur.event_flag;
	satellitePosition = psur.satellitePosition;
	weight = psur.weight;
	calculateDistance = psur.calculateDistance;
}

PsudoRange::~PsudoRange()
{
	observation.clear();
}

void PsudoRange::SetData(const long double dat, MeansType type)
{

	observation.insert(std::pair<MeansType, long double>(type, dat));

}

long double PsudoRange::GetData(MeansType type)
{

	return observation[type];

}

void PsudoRange::clear()
{
	observation.clear();
	PRN = 0;
	event_flag = 0;
}