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
 * PsudoRange.h
 *
 *  Created on: 2013/07/03
 *      Author: bun
 */

#include <map>
#include "GPS_Time.h"
#include "ENU_Frame.h"

#ifndef PSUDORANGE_H_
#define PSUDORANGE_H_

class PsudoRange
{

public:
	PsudoRange();
	PsudoRange(const PsudoRange &psur);
	virtual ~PsudoRange();

	enum MeansType
	{
		C1,
		P2,
		L1,
		L2,
		P1,
		CA,
		LA,
		SA,
		S1,
		CB,
		LB,
		SB,
		CC,
		LC,
		SC,
		CD,
		LD,
		SD,
		S2,
		C5,
		L5,
		S5,
		UNKNOWN
	};

	void SetPRN(const int prn)
	{
		PRN = prn;
	}

	int GetPRN()
	{
		return PRN;
	}

	void SetFlag(const int flag)
	{
		event_flag = flag;
	}

	int GetFlag()
	{
		return event_flag;
	}

	void SetData(const long double dat, MeansType type);
	long double GetData(MeansType type);
	void clear();

	ECEF_Frame GetSatellitePosition()
	{
		return satellitePosition;
	}

	void SetSatellitePosition(const ECEF_Frame satpos)
	{
		satellitePosition = satpos;
	}

	long double GetWeight()
	{
		return weight;
	}

	void SetWeight(const long double w)
	{
		weight = w;
	}

	long double GetCalculateRange()
	{
		return calculateDistance;
	}

	void SetCalculateRange(const long double r)
	{
		calculateDistance = r;
	}

private:
	std::map<MeansType, long double>observation;
	int PRN;
	GPS_Time current;
	int event_flag;
	ECEF_Frame satellitePosition;
	long double weight;
	long double calculateDistance;

};

#endif /* PSUDORANGE_H_ */
