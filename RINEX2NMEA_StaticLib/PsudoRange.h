/*
 * PsudoRange.h
 *
 *  Created on: 2013/07/03
 *      Author: bun
 */

#include <map>
#include "GPS_Time.h"

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

private:
	std::map<MeansType, long double>observation;
	int PRN;
	GPS_Time current;
	int event_flag;

};

