/*
 * Ephemeris.h
 *
 *  Created on: 2013/06/20
 *      Author: bun
 */

#ifndef EPHEMERIS_H_
#define EPHEMERIS_H_

#include <cmath>
#include <map>
#include "GPS_Time.h"
#include "WGS84_Frame.h"


class Ephemeris
{
public:
	Ephemeris();
	Ephemeris(const Ephemeris &rin);
	Ephemeris(const int prn);
	~Ephemeris();

	enum Ephemeris_column {
		TOC,
		Af0,
		Af1,
		Af2,
		IODE,
		Crs,
		d_n,
		M0,
		Cuc,
		eccentricity,
		Cus,
		sqrtA,
		TOE,
		Cic,
		OMEGA0,
		Cis,
		i0,
		Crc,
		omega,
		OMEGA_dot,
		di,
		CAonL2,
		week,
		L2P,
		accuracy,
		health,
		TGD,
		IODC,
		TOT,
		FIT,
		NONE1,
		NONE2,
		END
	};

	void SetToc(const GPS_Time &toc)
	{
		time_of_clock = toc;
	}

	GPS_Time GetToc()
	{
		return time_of_clock;
	}

	GPS_Time GetTot()
	{
		return transmission_time;
	}

	void SetPRN(const int prn)
	{
		PRN = prn;
	}

	int GetPRN()
	{
		return PRN;
	}

	void SetData(const long double dat, Ephemeris_column col);
	long double GetData(Ephemeris_column col);

	ECEF_Frame GetPosition(GPS_Time currentTime);
	long double GetClock(GPS_Time currentTime);


private:
	std::map<Ephemeris_column, long double> data;
	GPS_Time time_of_clock;
	GPS_Time transmission_time;
	GPS_Time time_of_ephemeris;
	int PRN;

};


#endif /* EPHEMERIS_H_ */
