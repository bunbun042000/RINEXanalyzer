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

#include "RINEX_constant.h"

namespace signalType
{
	enum Type
	{
		L1CA,
		L1C,
		L2C,
		L5
	};
};

class PsudoRange
{

public:
	PsudoRange();
	PsudoRange(const PsudoRange &psur);
	virtual ~PsudoRange();

	enum MeansType
	{
		// up to Ver2.11 
		C1, L1, D1, S1, // GPS/GLONASS/Galileo/SBAS L1
		C2, L2, D2, S2, // GPS/GLONASS L2
		C5,	L5,	D5,	S5, // GPS/Galileo/SBAS/QZSS L5
		C6, L6, D6, S6, // Galileo L6 / QZSS LEX
		C7, L7, D7, S7, // Galileo E5b
		C8, L8, D8, S8, // Galileo E5a+b
		// Ver 2.12 (modification for QZSS)
		CA,	LA,	DA, SA, // QZSS L1 C/A
		CB, LB, DB,	SB, // QZSS L1C
		CC, LC, DC, SC, // QZSS L2C
		CD, LD, DD, SD, // GLONASS L2 SA
		// Ver.3
		C1C, L1C, D1C, S1C, // GPS L1 C/A / GLONASS G1 C/A / Galileo E1C / SBAS L1 C/A
		C1S, L1S, D1S, S1S, // GPS L1C(M)
		C1L, L1L, D1L, S1L, // GPS L1C(L)
		C1X, L1X, D1X, S1X, // GPS L1C(M+L) / Galileo E1(B+C)
		C1P, L1P, D1P, S1P, // GPS L1P / GLONASS G1P
		C1W, L1W, D1W, S1W, // GPS L1 Z-tracking
		C1Y, L1Y, D1Y, S1Y, // GPS L1Y
		C1M, L1M, D1M, S1M, // GPS L1M
		     L1N, D1N, S1N, // GPS L1 codeless
		C2C, L2C, D2C, S2C, // GPS L2 C/A / GLONASS G2 C/A (GLONASS M)
		C2D, L2D, D2D, S2D, // GPS L2 L1(C/A)+(P2-P1)
		C2S, L2S, D2S, S2S, // GPS L2C(M)
		C2L, L2L, D2L, S2L, // GPS L2C(L)
		C2X, L2X, D2X, S2X, // GPS L2C(M+L) / Compass E2(I+Q)
		C2P, L2P, D2P, S2P, // GPS L2P / GLONASS G2P
		C2W, L2W, D2W, S2W, // GPS L2 Z-tracking
		C2Y, L2Y, D2Y, S2Y, // GPS L2Y
		C2M, L2M, D2M, S2M, // GPS L2M
		     L2N, D2N, S2N, // GPS L2 codeless
		C5I, L5I, D5I, S5I, // GPS L5I / Galileo E5aI / SBAS L5I
		C5Q, L5Q, D5Q, S5Q, // GPS L5Q / Galileo E5aQ / SBAS L5Q
		C5X, L5X, D5X, S5X, // GPS L5(I+Q) / Galileo E5a(I+Q) / SBAS L5 (I+Q)
		C1A, L1A, D1A, S1A, // Galileo E1A
		C1B, L1B, D1B, S1B, // Galileo E1B
		C1Z, L1Z, D1Z, S1Z, // Galileo E1(A+B+C)
		C7I, L7I, D7I, S7I, // Galileo E5bI / Compass E5bI
		C7Q, L7Q, D7Q, S7Q, // Galileo E5bQ / Compass E5bQ
		C7X, L7X, D7X, S7X, // Galileo E5b(I+Q) / Compass E5b(I+Q)
		C8I, L8I, D8I, S8I, // Galileo E5I
		C8Q, L8Q, D8Q, S8Q, // Galileo E5Q
		C8X, L8X, D8X, S8X, // Galileo E5(I+Q)
		C6A, L6A, D6A, S6A, // Galileo E6A
		C6B, L6B, D6B, S6B, // Galileo E6B
		C6C, L6C, D6C, S6C, // Galileo E6C
		C6X, L6X, D6X, S6X, // Galileo E6(B+C) / Compass E6(I+Q)
		C6Z, L6Z, D6Z, S6Z, // Galileo E6(A+B+C)
		C2I, L2I, D2I, S2I, // Compass E2I
		C2Q, L2Q, D2Q, S2Q, // Compass E2Q
		C6I, L6I, D6I, S6I, // Compass E6I
		C6Q, L6Q, D6Q, S6Q, // Compass E6Q
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

	void clear();

	void SetData(const long double dat, MeansType type, RINEX::_Version _ver);

	long double GetPsudoRange(signalType::Type type);
	long double GetSNR(signalType::Type type);


	void SetVersion(RINEX::_Version _ver)
	{
		ver = _ver;
	}

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
	RINEX::_Version ver;


};

#endif /* PSUDORANGE_H_ */
