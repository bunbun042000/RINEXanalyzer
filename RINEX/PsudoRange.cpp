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
	ver = RINEX::Ver2;
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
	ver = psur.ver;
}

PsudoRange::~PsudoRange()
{
	observation.clear();
}

void PsudoRange::SetData(const long double dat, MeansType type, RINEX::_Version _ver)
{
	ver = _ver;
	observation.insert(std::pair<MeansType, long double>(type, dat));

}

long double PsudoRange::GetPsudoRange(signalType::Type type)
{
	long double ret_data = 0.0;
	if (type == signalType::L1CA)
	{
		if (ver == RINEX::Ver2)
		{
			ret_data = observation[C1];
		}
		else if (ver == RINEX::Ver210 || ver == RINEX::Ver211 || ver == RINEX::Ver212)
		{
			ret_data = observation[CA];
		}
		else if (ver == RINEX::Ver300 || ver == RINEX::Ver301 || ver == RINEX::Ver302)
		{
			ret_data = observation[C1C];
		}
		else
		{
			// Do nothing
		}

	}
	else if (type == signalType::L1C)
	{
		if (ver == RINEX::Ver2 || ver == RINEX::Ver210 || ver == RINEX::Ver211)
		{
			// Do nothing
		}
		else if (ver == RINEX::Ver212)
		{
			ret_data = observation[CB];
		}
		else if (ver == RINEX::Ver300 || ver == RINEX::Ver301 || ver == RINEX::Ver302)
		{
			ret_data = observation[C1S];
		}
		else
		{
			// Do nothing
		}
	}
	else if (type == signalType::L2C)
	{
		if (ver == RINEX::Ver2 || ver == RINEX::Ver210 || ver == RINEX::Ver211)
		{
			ret_data = observation[C2];
		}
		else if (ver == RINEX::Ver212)
		{
			ret_data = observation[CC];
		}
		else if (ver == RINEX::Ver300 || ver == RINEX::Ver301 || ver == RINEX::Ver302)
		{
			ret_data = observation[C2S];
		}
		else
		{
			// Do nothing
		}
	}
	else if (type == signalType::L5)
	{
		if (ver == RINEX::Ver2 || ver == RINEX::Ver210 || ver == RINEX::Ver211)
		{
			ret_data = observation[C5];
		}
		else if (ver == RINEX::Ver212)
		{
			ret_data = observation[C5];
		}
		else if (ver == RINEX::Ver300 || ver == RINEX::Ver301 || ver == RINEX::Ver302)
		{
			ret_data = observation[C5I];
		}
		else
		{
			// Do nothing
		}
	}
	else
	{
		// Do nothing
	}

	return ret_data;
}

long double PsudoRange::GetSNR(signalType::Type type)
{
	long double ret_data = 0.0;
	if (type == signalType::L1CA)
	{
		if (ver == RINEX::Ver2)
		{
			ret_data = observation[S1];
		}
		else if (ver == RINEX::Ver210 || ver == RINEX::Ver211 || ver == RINEX::Ver212)
		{
			ret_data = observation[SA];
		}
		else if (ver == RINEX::Ver300 || ver == RINEX::Ver301 || ver == RINEX::Ver302)
		{
			ret_data = observation[S1C];
		}
		else
		{
			// Do nothing
		}

	}
	else if (type == signalType::L1C)
	{
		if (ver == RINEX::Ver2 || ver == RINEX::Ver210 || ver == RINEX::Ver211)
		{
			// Do nothing
		}
		else if (ver == RINEX::Ver212)
		{
			ret_data = observation[SB];
		}
		else if (ver == RINEX::Ver300 || ver == RINEX::Ver301 || ver == RINEX::Ver302)
		{
			ret_data = observation[S1S];
		}
		else
		{
			// Do nothing
		}
	}
	else if (type == signalType::L2C)
	{
		if (ver == RINEX::Ver2 || ver == RINEX::Ver210 || ver == RINEX::Ver211)
		{
			ret_data = observation[S2];
		}
		else if (ver == RINEX::Ver212)
		{
			ret_data = observation[SC];
		}
		else if (ver == RINEX::Ver300 || ver == RINEX::Ver301 || ver == RINEX::Ver302)
		{
			ret_data = observation[S2S];
		}
		else
		{
			// Do nothing
		}
	}
	else if (type == signalType::L5)
	{
		if (ver == RINEX::Ver2 || ver == RINEX::Ver210 || ver == RINEX::Ver211)
		{
			ret_data = observation[S5];
		}
		else if (ver == RINEX::Ver212)
		{
			ret_data = observation[S5];
		}
		else if (ver == RINEX::Ver300 || ver == RINEX::Ver301 || ver == RINEX::Ver302)
		{
			ret_data = observation[S5I];
		}
		else
		{
			// Do nothing
		}
	}
	else
	{
		// Do nothing
	}

	return ret_data;

}

void PsudoRange::clear()
{
	observation.clear();
	PRN = 0;
	event_flag = 0;
}
