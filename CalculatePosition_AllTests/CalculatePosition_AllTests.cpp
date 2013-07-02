/*
 * CalculatePosition_AllTests.cpp
 *
 *  Created on: 2013/06/17
 *      Author: bun
 */

#include <gtest/gtest.h>
#include <cmath>
#include <iostream>
#include <vector>

#include "Calculate_Position.h"
#include "Matrix.h"
#include "Gaussian_Elimination.h"
#include "ECEF_Frame.h"
#include "RINEX_NavigationMessage.h"


TEST(Gaussian_Elimination, GetAnswer)
{
	Matrix matA = Matrix(3, 3);

	matA.SetData(2.0L, 0, 0);
	matA.SetData(3.0L, 0, 1);
	matA.SetData(3.0L, 0, 2);
	matA.SetData(3.0L, 1, 0);
	matA.SetData(2.0L, 1, 1);
	matA.SetData(-1.0L, 1, 2);
	matA.SetData(5.0L, 2, 0);
	matA.SetData(4.0L, 2, 1);
	matA.SetData(2.0L, 2, 2);

	Matrix vecB = Matrix(3, 1);

	vecB.SetData(5.0L, 0, 0);
	vecB.SetData(-4.0L, 1, 0);
	vecB.SetData(3.0L, 2, 0);

	Gaussian_Elimination Gauss = Gaussian_Elimination(matA, vecB);

	if (Gauss.IsValid())
	{
		SUCCEED();
	}
	else
	{
		FAIL();
	}

	Matrix vecX;
	vecX = Gauss.GetAnswer();

	ASSERT_DOUBLE_EQ(1.0L, vecX.GetData(0, 0));
	ASSERT_DOUBLE_EQ(-2.0L, vecX.GetData(1, 0));
	ASSERT_DOUBLE_EQ(3.0L, vecX.GetData(2, 0));

}

TEST(Calculate_Position, TEST1)
{


	std::vector<ECEF_Frame> sat;
	Matrix range = Matrix(5, 1);
	sat.push_back(ECEF_Frame(-13897607.6294L, -10930188.6233L, 19676689.6804L));
	sat.push_back(ECEF_Frame(-17800899.1998L, 15689920.8120L, 11943543.3888L));
	sat.push_back(ECEF_Frame(-1510958.2282L, 26280096.7818L, -3117646.1949L));
	sat.push_back(ECEF_Frame(-12210758.3517L, 20413597.0201L, -11649499.5474L));
	sat.push_back(ECEF_Frame(-170032.6981L, 17261822.6784L, 20555984.4061L));


	range.SetData(23634878.5219L, 0, 0);
	range.SetData(20292688.3557L, 1, 0);
	range.SetData(24032055.0372L, 2, 0);
	range.SetData(24383229.3740L, 3, 0);
	range.SetData(22170992.8178L, 4, 0);

	Calculate_Position cal(sat, range, 5);

	ECEF_Frame position = cal.GetPosition();
	ASSERT_DOUBLE_EQ(-3947762.4862546385, position.GetX());
	ASSERT_DOUBLE_EQ(3364401.3024154068, position.GetY());
	ASSERT_DOUBLE_EQ(3699431.9924437893, position.GetZ());

}

TEST(RINEX_NavigationMessage, Read)
{
	std::string filename = "05311710.13n";
	RINEX_NavigationMessage nav_message(filename);

	nav_message.Read();

	std::map <int, Ephemeris> ephem_map = nav_message.GetEphemeris(GPS_Time(1745, 388800, 0), -1); // 2013-06-20 12:00:00


	std::map<int, Ephemeris>::iterator it = ephem_map.begin();
	ASSERT_EQ(1, it->first);
	ASSERT_EQ(1745, it->second.GetToc().GetWeek());
	ASSERT_DOUBLE_EQ(388800.0, it->second.GetToc().GetSecond());
	ASSERT_DOUBLE_EQ(3.983825445175e-5, it->second.GetData(Ephemeris::Af0));
	ASSERT_DOUBLE_EQ(4.661160346586e-12, it->second.GetData(Ephemeris::Af1));
	ASSERT_DOUBLE_EQ(0.0, it->second.GetData(Ephemeris::Af2));
	ASSERT_DOUBLE_EQ(60.0, it->second.GetData(Ephemeris::IODE));
	ASSERT_DOUBLE_EQ(-1.58125e+1, it->second.GetData(Ephemeris::Crs));
	ASSERT_DOUBLE_EQ(4.907347267854e-09, it->second.GetData(Ephemeris::d_n));
	ASSERT_DOUBLE_EQ(1.521196807610e+0, it->second.GetData(Ephemeris::M0));
	ASSERT_DOUBLE_EQ(-9.406358003616e-7, it->second.GetData(Ephemeris::Cuc));
	ASSERT_DOUBLE_EQ(1.995946746320e-3, it->second.GetData(Ephemeris::eccentricity));
	ASSERT_DOUBLE_EQ(6.001442670822e-6, it->second.GetData(Ephemeris::Cus));
	ASSERT_DOUBLE_EQ(5.153686595917e+3, it->second.GetData(Ephemeris::sqrtA));
	ASSERT_DOUBLE_EQ(3.888000000000e+5, it->second.GetData(Ephemeris::TOE));
	ASSERT_DOUBLE_EQ(2.980232238770e-8, it->second.GetData(Ephemeris::Cic));
	ASSERT_DOUBLE_EQ(-1.841495219222e+0, it->second.GetData(Ephemeris::OMEGA0));
	ASSERT_DOUBLE_EQ(4.656612873077e-8, it->second.GetData(Ephemeris::Cis));
	ASSERT_DOUBLE_EQ(9.598454726167e-1, it->second.GetData(Ephemeris::i0));
	ASSERT_DOUBLE_EQ(2.618125000000e+2, it->second.GetData(Ephemeris::Crc));
	ASSERT_DOUBLE_EQ(2.631760951407e-1, it->second.GetData(Ephemeris::omega));
	ASSERT_DOUBLE_EQ(-8.198912946205e-9, it->second.GetData(Ephemeris::OMEGA_dot));
	ASSERT_DOUBLE_EQ(-1.989368579472e-10, it->second.GetData(Ephemeris::di));
	ASSERT_DOUBLE_EQ(1.000000000000e+0, it->second.GetData(Ephemeris::CAonL2));
	ASSERT_DOUBLE_EQ(1.745000000000e+3, it->second.GetData(Ephemeris::week));
	ASSERT_DOUBLE_EQ(0.000000000000e+0, it->second.GetData(Ephemeris::L2P));
	ASSERT_DOUBLE_EQ(2.000000000000e+0, it->second.GetData(Ephemeris::accuracy));
	ASSERT_DOUBLE_EQ(0.000000000000e+0, it->second.GetData(Ephemeris::health));
	ASSERT_DOUBLE_EQ(8.381903171539e-9, it->second.GetData(Ephemeris::TGD));
	ASSERT_DOUBLE_EQ(6.000000000000e+1, it->second.GetData(Ephemeris::IODC));
	ASSERT_DOUBLE_EQ(3.816180000000e+5, it->second.GetData(Ephemeris::TOT));
	ASSERT_DOUBLE_EQ(4.000000000000e+0, it->second.GetData(Ephemeris::FIT));

	it++;
	ASSERT_EQ(3, it->first);
	ASSERT_DOUBLE_EQ(51, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(6, it->first);
	ASSERT_DOUBLE_EQ(52, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(7, it->first);
	ASSERT_DOUBLE_EQ(17, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(8, it->first);
	ASSERT_DOUBLE_EQ(105, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(9, it->first);
	ASSERT_DOUBLE_EQ(31, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(11, it->first);
	ASSERT_DOUBLE_EQ(25, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(14, it->first);
	ASSERT_DOUBLE_EQ(28, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(16, it->first);
	ASSERT_DOUBLE_EQ(60, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(17, it->first);
	ASSERT_DOUBLE_EQ(52, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(18, it->first);
	ASSERT_DOUBLE_EQ(42, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(19, it->first);
	ASSERT_DOUBLE_EQ(10, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(20, it->first);
	ASSERT_DOUBLE_EQ(1, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(22, it->first);
	ASSERT_DOUBLE_EQ(46, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(23, it->first);
	ASSERT_DOUBLE_EQ(51, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(28, it->first);
	ASSERT_DOUBLE_EQ(16, it->second.GetData(Ephemeris::IODE));
	it++;
	ASSERT_EQ(32, it->first);
	ASSERT_DOUBLE_EQ(95, it->second.GetData(Ephemeris::IODE));
	it++;

	if (it == ephem_map.end())
	{
		SUCCEED();
	}
	else
	{
		FAIL();
	}


}


TEST(RINEX_NavigationMessage, CalculateSatellitePosition)
{
	std::string filename = "mtka3180.05n";
	RINEX_NavigationMessage nav_message(filename);

	nav_message.Read();

	std::map <int, Ephemeris> ephem_map = nav_message.GetEphemeris(GPS_Time(1349, 86400.0, 0), -1); // 2005-11-14 00:00:00


	Matrix range = Matrix(5, 1);

	std::map <int, Ephemeris> cal_ephem;

	for (std::map <int, Ephemeris>::iterator it = ephem_map.begin(); it != ephem_map.end(); it++)
	{
		if (it->first == 5)
		{
			cal_ephem.insert(std::pair<int, Ephemeris>(it->first, it->second));
		}
		else if (it->first == 14)
		{
			cal_ephem.insert(std::pair<int, Ephemeris>(it->first, it->second));
		}
		else if (it->first == 16)
		{
			cal_ephem.insert(std::pair<int, Ephemeris>(it->first, it->second));
		}
		else if (it->first == 22)
		{
			cal_ephem.insert(std::pair<int, Ephemeris>(it->first, it->second));
		}
		else if (it->first == 25)
		{
			cal_ephem.insert(std::pair<int, Ephemeris>(it->first, it->second));
		}

	}


	range.SetData(23545777.534L, 0, 0);		// PRN 5
	range.SetData(20299789.570L, 1, 0);		// PRN 14
	range.SetData(24027782.537L, 2, 0);		// PRN 16
	range.SetData(24367716.061L, 3, 0);		// PRN 22
	range.SetData(22169926.127L, 4, 0);		// PRN 25

	Calculate_Position cal(cal_ephem, range, GPS_Time(1349, 86400.0, 0));

	ECEF_Frame position = cal.GetPosition();
//	ASSERT_DOUBLE_EQ(-3947846.647, position.GetX());
//	ASSERT_DOUBLE_EQ(-3947847.5773508437, position.GetX());
//	ASSERT_DOUBLE_EQ(3364338.022, position.GetY());
//	ASSERT_DOUBLE_EQ(3364337.0398937939, position.GetY());
//	ASSERT_DOUBLE_EQ(3699406.626, position.GetZ());
//	ASSERT_DOUBLE_EQ(3699406.4078218928, position.GetZ());

// relative effect collection
	ASSERT_DOUBLE_EQ(-3947841.2121078535, position.GetX());
	ASSERT_DOUBLE_EQ(3364334.5810319413, position.GetY());
	ASSERT_DOUBLE_EQ(3699408.8296222701, position.GetZ());

}

