//----------------------------------------------------------------------
//Copyright (c) 2013 Yamagata Fumihiro.
//All rights reserved. This program and the accompanying materials
//are made available under the terms of the GNU Public License v2.0
//which accompanies this distribution, and is available at
//http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
//
//Contributors:
//    Yamagata Fumihiro - initial API and implementation
//----------------------------------------------------------------------
// RINEX_AllTests.cpp
//

//#include "stdafx.h"


//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}

#include <gtest/gtest.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

#include "RINEX.h"

TEST(GPS_Time_Test, ToDate)
{
  GPS_Time gpstime;
  struct tm tbuf;
  gpstime = GPS_Time(1350, 100.0, GPS_Time_const::leap_sec_base);

  tbuf = gpstime.ToDate();
  ASSERT_EQ(2005, tbuf.tm_year+1900);
  ASSERT_EQ(11, tbuf.tm_mon+1);
  ASSERT_EQ(20, tbuf.tm_mday);
  ASSERT_EQ(00, tbuf.tm_hour);
  ASSERT_EQ(01, tbuf.tm_min);
  ASSERT_EQ(27, tbuf.tm_sec);
  ASSERT_EQ(13, gpstime.GetLeapSecond());

}

TEST(GPS_Time_Test, ToGPSTime1)
{
	GPS_Time gpstime;

	gpstime = GPS_Time(2019, 4, 7, 1, 1, 40);

	ASSERT_EQ(2048, gpstime.GetWeek());
	ASSERT_DOUBLE_EQ(3700.0, gpstime.GetSecond());

}

TEST(GPS_Time_Test, ToGPSTime2)
{
	GPS_Time gpstime;

	gpstime = GPS_Time(1980, 1, 6, 0, 0, 0);

	ASSERT_EQ(0, gpstime.GetWeek());
	ASSERT_DOUBLE_EQ(0.0, gpstime.GetSecond());
}

TEST(GPS_Time_Test, LeapSec)
{
	GPS_Time gpstime;
	gpstime = GPS_Time(1980, 1, 6, 0, 0, 0.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(0, gpstime.GetLeapSecond());
	// 1st
	gpstime = GPS_Time(1981, 6, 30, 23, 59, 59.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(0, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1981, 7, 1, 0, 0, 0.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(1, gpstime.GetLeapSecond());
	// 2nd
	gpstime = GPS_Time(1982, 7, 1, 0, 0, 0.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(1, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1982, 7, 1, 0, 0, 1.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(2, gpstime.GetLeapSecond());
	// 3rd
	gpstime = GPS_Time(1983, 7, 1, 0, 0, 1.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(2, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1983, 7, 1, 0, 0, 2.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(3, gpstime.GetLeapSecond());
	// 4th
	gpstime = GPS_Time(1985, 7, 1, 0, 0, 2.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(3, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1985, 7, 1, 0, 0, 3.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(4, gpstime.GetLeapSecond());
	// 5th
	gpstime = GPS_Time(1988, 1, 1, 0, 0, 3.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(4, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1988, 1, 1, 0, 0, 4.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(5, gpstime.GetLeapSecond());
	// 6th
	gpstime = GPS_Time(1990, 1, 1, 0, 0, 4.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(5, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1990, 1, 1, 0, 0, 5.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(6, gpstime.GetLeapSecond());
	// 7th
	gpstime = GPS_Time(1991, 1, 1, 0, 0, 5.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(6, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1991, 1, 1, 0, 0, 6.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(7, gpstime.GetLeapSecond());
	// 8th
	gpstime = GPS_Time(1992, 7, 1, 0, 0, 6.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(7, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1992, 7, 1, 0, 0, 7.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(8, gpstime.GetLeapSecond());
	// 9th
	gpstime = GPS_Time(1993, 7, 1, 0, 0, 7.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(8, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1993, 7, 1, 0, 0, 8.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(9, gpstime.GetLeapSecond());
	// 10th
	gpstime = GPS_Time(1994, 7, 1, 0, 0, 8.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(9, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1994, 7, 1, 0, 0, 9.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(10, gpstime.GetLeapSecond());
	// 11th
	gpstime = GPS_Time(1996, 1, 1, 0, 0, 9.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(10, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1996, 1, 1, 0, 0, 10.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(11, gpstime.GetLeapSecond());
	// 12th
	gpstime = GPS_Time(1997, 7, 1, 0, 0, 10.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(11, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1997, 7, 1, 0, 0, 11.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(12, gpstime.GetLeapSecond());
	// 13th
	gpstime = GPS_Time(1999, 1, 1, 0, 0, 11.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(12, gpstime.GetLeapSecond());
	gpstime = GPS_Time(1999, 1, 1, 0, 0, 12.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(13, gpstime.GetLeapSecond());
	// 14th
	gpstime = GPS_Time(2006, 1, 1, 0, 0, 12.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(13, gpstime.GetLeapSecond());
	gpstime = GPS_Time(2006, 1, 1, 0, 0, 13.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(14, gpstime.GetLeapSecond());
	// 15th
	gpstime = GPS_Time(2009, 1, 1, 0, 0, 13.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(14, gpstime.GetLeapSecond());
	gpstime = GPS_Time(2009, 1, 1, 0, 0, 14.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(15, gpstime.GetLeapSecond());
	// 16th
	gpstime = GPS_Time(2012, 7, 1, 0, 0, 14.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(15, gpstime.GetLeapSecond());
	gpstime = GPS_Time(2012, 7, 1, 0, 0, 15.0L, GPS_Time_const::leap_sec_base);
	ASSERT_EQ(16, gpstime.GetLeapSecond());


}

TEST(ECEF_Frame_Test, ECEF_Frame_Basic)
{

	ECEF_Frame f1 = ECEF_Frame(10, 20, 30);

	ASSERT_DOUBLE_EQ(sqrt(1400.0L), f1.Distance(ECEF_Frame(0.0L, 0.0L, 0.0L)));

	ECEF_Frame f2 = ECEF_Frame(30, 20, 10);

	ASSERT_DOUBLE_EQ(sqrt(800.0L), f2.Distance(f1));
}

TEST(WGS84_Frame_Test, ECEF2WGS84)
{

	// Japan Geodetic Datum
	// H23 MILT "Kokuji" No. 1613
	ECEF_Frame f1 = ECEF_Frame(-3959340.203, 3352854.274, 3697471.413);

	WGS84_Frame w1 = WGS84_Frame(f1);

	// Sokuryou-hou sekou-rei(H24/08/31 "Seirei" No.322)
	// Latitude N35'39"29.1572
	// Longitude E139'44"28.8869
	ASSERT_NEAR(35.6580992222 / 180.0 * 3.1415926535898, w1.GetLat(), 1.0e-10);
	ASSERT_NEAR(139.7413574722 / 180.0 * 3.1415926535898, w1.GetLongi(), 1.0e-10);
	ASSERT_NEAR(63.23233511, w1.GetE_Height(), 1.0e-5);

}

TEST(WGS84_Frame_Test, WGS842ECEF)
{
	//Japan Geodetic Datum
	//Geoidal Height is calculated by http://vldb.gsi.go.jp/sokuchi/surveycalc/transf.html
	//Using H23 MILT "Kokuji" No. 1613
	WGS84_Frame w1 = WGS84_Frame(35.6580992222 / 180 * 3.1415926535898, 139.7413574722 / 180.0 * 3.1415926535898, 63.2323511);

	ASSERT_NEAR(-3959340.203, w1.GetX(), 1.0e-3);
	ASSERT_NEAR(3352854.274, w1.GetY(), 1.0e-3);
	ASSERT_NEAR(3697471.413, w1.GetZ(), 1.0e-3);
}

TEST(ENU_Frame_Test, ENU2ECEF)
{
	WGS84_Frame wgs84_origin = WGS84_Frame(35.6580992222 / 180 * 3.1415926535898, 139.7413574722 / 180 * 3.1415926535898, 63.23233511);

	ENU_Frame enu1 = ENU_Frame(200.0L, 100.0L, 300.0L, wgs84_origin);

	ASSERT_NEAR(-3959610.981, (enu1.GetPosition()).GetX(), 1.0e-3);
	ASSERT_NEAR(3352821.497, (enu1.GetPosition()).GetY(), 1.0e-3);
	ASSERT_NEAR(3697727.548, (enu1.GetPosition()).GetZ(), 1.0e-3);

	ASSERT_DOUBLE_EQ(atan2(enu1.GetU(), sqrt(enu1.GetN() * enu1.GetN() + enu1.GetE() * enu1.GetE())), enu1.GetElevation());
	ASSERT_DOUBLE_EQ(atan2(enu1.GetE(), enu1.GetN()), enu1.GetAzimuth());

}

TEST(ENU_Frame_Test, ECEF2ENU)
{
	WGS84_Frame wgs84_origin = WGS84_Frame(35.6580992222 / 180 * 3.1415926535898, 139.7413574722 / 180 * 3.1415926535898, 63.23233511);

	WGS84_Frame f1 = WGS84_Frame(ECEF_Frame(-3959610.981, 3352821.497, 3697727.548));

	ENU_Frame enu1 = ENU_Frame(f1, wgs84_origin);

	ASSERT_NEAR(200.0L, enu1.GetE(), 1.0e-3);
	ASSERT_NEAR(100.0L, enu1.GetN(), 1.0e-3);
	ASSERT_NEAR(300.0L, enu1.GetU(), 1.0e-3);

}

TEST(Matrix_Test, Basic1)
{
	Matrix matA = Matrix(3, 3);
	matA.SetData(1.00L, 0, 0);
	matA.SetData(2.00L, 0, 1);
	matA.SetData(3.00L, 0, 2);
	matA.SetData(4.00L, 1, 0);
	matA.SetData(5.00L, 1, 1);
	matA.SetData(6.00L, 1, 2);
	matA.SetData(7.00L, 2, 0);
	matA.SetData(8.00L, 2, 1);
	matA.SetData(9.00L, 2, 2);

	ASSERT_DOUBLE_EQ(1.0L, matA.GetData(0, 0));
	ASSERT_DOUBLE_EQ(2.0L, matA.GetData(0, 1));
	ASSERT_DOUBLE_EQ(3.0L, matA.GetData(0, 2));
	ASSERT_DOUBLE_EQ(4.0L, matA.GetData(1, 0));
	ASSERT_DOUBLE_EQ(5.0L, matA.GetData(1, 1));
	ASSERT_DOUBLE_EQ(6.0L, matA.GetData(1, 2));
	ASSERT_DOUBLE_EQ(7.0L, matA.GetData(2, 0));
	ASSERT_DOUBLE_EQ(8.0L, matA.GetData(2, 1));
	ASSERT_DOUBLE_EQ(9.0L, matA.GetData(2, 2));

	Matrix matB = Matrix(3, 3);
	long double *vec1, *vec2, *vec3;
	vec1 = new long double[3];
	vec2 = new long double[3];
	vec3 = new long double[3];
	vec1[0] = 18.0L;
	vec1[1] = 12.0L;
	vec1[2] = 6.0L;
	vec2[0] = 16.0L;
	vec2[1] = 10.0L;
	vec2[2] = 4.0L;
	vec3[0] = 14.0L;
	vec3[1] = 8.0L;
	vec3[2] = 2.0L;
	matB.SetColumn(vec1, 0, 3);
	matB.SetColumn(vec2, 1, 3);
	matB.SetColumn(vec3, 2, 3);

	delete []vec1;
	delete []vec2;
	delete []vec3;

	ASSERT_DOUBLE_EQ(18.0L, matB.GetData(0, 0));
	ASSERT_DOUBLE_EQ(10.0L, matB.GetData(1, 1));
	ASSERT_DOUBLE_EQ(4.0L, matB.GetData(2, 1));

	Matrix matC;
	matC = matA + matB;

	ASSERT_DOUBLE_EQ(19.0L, matC.GetData(0, 0));
	ASSERT_DOUBLE_EQ(18.0L, matC.GetData(0, 1));
	ASSERT_DOUBLE_EQ(17.0L, matC.GetData(0, 2));
	ASSERT_DOUBLE_EQ(16.0L, matC.GetData(1, 0));
	ASSERT_DOUBLE_EQ(15.0L, matC.GetData(1, 1));
	ASSERT_DOUBLE_EQ(14.0L, matC.GetData(1, 2));
	ASSERT_DOUBLE_EQ(13.0L, matC.GetData(2, 0));
	ASSERT_DOUBLE_EQ(12.0L, matC.GetData(2, 1));
	ASSERT_DOUBLE_EQ(11.0L, matC.GetData(2, 2));

	matC = matB - matA;

	ASSERT_DOUBLE_EQ(17.0L, matC.GetData(0, 0));
	ASSERT_DOUBLE_EQ(14.0L, matC.GetData(0, 1));
	ASSERT_DOUBLE_EQ(11.0L, matC.GetData(0, 2));
	ASSERT_DOUBLE_EQ(8.0L, matC.GetData(1, 0));
	ASSERT_DOUBLE_EQ(5.0L, matC.GetData(1, 1));
	ASSERT_DOUBLE_EQ(2.0L, matC.GetData(1, 2));
	ASSERT_DOUBLE_EQ(-1.0L, matC.GetData(2, 0));
	ASSERT_DOUBLE_EQ(-4.0L, matC.GetData(2, 1));
	ASSERT_DOUBLE_EQ(-7.0L, matC.GetData(2, 2));

	matC = 2.5L * matA;
	ASSERT_DOUBLE_EQ(2.5L, matC.GetData(0, 0));
	ASSERT_DOUBLE_EQ(5.0L, matC.GetData(0, 1));
	ASSERT_DOUBLE_EQ(7.5L, matC.GetData(0, 2));
	ASSERT_DOUBLE_EQ(10.0L, matC.GetData(1, 0));
	ASSERT_DOUBLE_EQ(12.5L, matC.GetData(1, 1));
	ASSERT_DOUBLE_EQ(15.0L, matC.GetData(1, 2));
	ASSERT_DOUBLE_EQ(17.5L, matC.GetData(2, 0));
	ASSERT_DOUBLE_EQ(20.0L, matC.GetData(2, 1));
	ASSERT_DOUBLE_EQ(22.5L, matC.GetData(2, 2));

	matC = matA * 2.5L;
	ASSERT_DOUBLE_EQ(2.5L, matC.GetData(0, 0));
	ASSERT_DOUBLE_EQ(5.0L, matC.GetData(0, 1));
	ASSERT_DOUBLE_EQ(7.5L, matC.GetData(0, 2));
	ASSERT_DOUBLE_EQ(10.0L, matC.GetData(1, 0));
	ASSERT_DOUBLE_EQ(12.5L, matC.GetData(1, 1));
	ASSERT_DOUBLE_EQ(15.0L, matC.GetData(1, 2));
	ASSERT_DOUBLE_EQ(17.5L, matC.GetData(2, 0));
	ASSERT_DOUBLE_EQ(20.0L, matC.GetData(2, 1));
	ASSERT_DOUBLE_EQ(22.5L, matC.GetData(2, 2));

}

TEST(Matrix_Test, Basic2)
{
	Matrix matD = Matrix(2, 3);

	matD.SetData(1.0L, 0, 0);
	matD.SetData(2.0L, 0, 1);
	matD.SetData(3.0L, 0, 2);
	matD.SetData(5.0L, 1, 0);
	matD.SetData(8.0L, 1, 1);
	matD.SetData(7.0L, 1, 2);

	Matrix matF = matD.Tranposed();
	ASSERT_DOUBLE_EQ(1.0L, matF.GetData(0, 0));
	ASSERT_DOUBLE_EQ(2.0L, matF.GetData(1, 0));
	ASSERT_DOUBLE_EQ(3.0L, matF.GetData(2, 0));
	ASSERT_DOUBLE_EQ(5.0L, matF.GetData(0, 1));
	ASSERT_DOUBLE_EQ(8.0L, matF.GetData(1, 1));
	ASSERT_DOUBLE_EQ(7.0L, matF.GetData(2, 1));

	Matrix matE = Matrix(3, 2);
	matE.SetData(6.0L, 0, 0);
	matE.SetData(5.0L, 0, 1);
	matE.SetData(9.0L, 1, 0);
	matE.SetData(6.0L, 1, 1);
	matE.SetData(8.0L, 2, 0);
	matE.SetData(2.0L, 2, 1);


	matF = matD * matE;
	ASSERT_DOUBLE_EQ(48.0L, matF.GetData(0, 0));
	ASSERT_DOUBLE_EQ(23.0L, matF.GetData(0, 1));
	ASSERT_DOUBLE_EQ(158.0L, matF.GetData(1, 0));
	ASSERT_DOUBLE_EQ(87.0L, matF.GetData(1, 1));

	Matrix matG;
	matG = matE * matD;
	ASSERT_DOUBLE_EQ(31.0L, matG.GetData(0, 0));
	ASSERT_DOUBLE_EQ(52.0L, matG.GetData(0, 1));
	ASSERT_DOUBLE_EQ(53.0L, matG.GetData(0, 2));
	ASSERT_DOUBLE_EQ(39.0L, matG.GetData(1, 0));
	ASSERT_DOUBLE_EQ(66.0L, matG.GetData(1, 1));
	ASSERT_DOUBLE_EQ(69.0L, matG.GetData(1, 2));
	ASSERT_DOUBLE_EQ(18.0L, matG.GetData(2, 0));
	ASSERT_DOUBLE_EQ(32.0L, matG.GetData(2, 1));
	ASSERT_DOUBLE_EQ(38.0L, matG.GetData(2, 2));

	matG.SwapRow(1, 2);
	ASSERT_DOUBLE_EQ(31.0L, matG.GetData(0, 0));
	ASSERT_DOUBLE_EQ(52.0L, matG.GetData(0, 1));
	ASSERT_DOUBLE_EQ(53.0L, matG.GetData(0, 2));
	ASSERT_DOUBLE_EQ(18.0L, matG.GetData(1, 0));
	ASSERT_DOUBLE_EQ(32.0L, matG.GetData(1, 1));
	ASSERT_DOUBLE_EQ(38.0L, matG.GetData(1, 2));
	ASSERT_DOUBLE_EQ(39.0L, matG.GetData(2, 0));
	ASSERT_DOUBLE_EQ(66.0L, matG.GetData(2, 1));
	ASSERT_DOUBLE_EQ(69.0L, matG.GetData(2, 2));

	Matrix matH;
	matH = matG;
	ASSERT_DOUBLE_EQ(31.0L, matH.GetData(0, 0));
	ASSERT_DOUBLE_EQ(52.0L, matH.GetData(0, 1));
	ASSERT_DOUBLE_EQ(53.0L, matH.GetData(0, 2));
	ASSERT_DOUBLE_EQ(18.0L, matH.GetData(1, 0));
	ASSERT_DOUBLE_EQ(32.0L, matH.GetData(1, 1));
	ASSERT_DOUBLE_EQ(38.0L, matH.GetData(1, 2));
	ASSERT_DOUBLE_EQ(39.0L, matH.GetData(2, 0));
	ASSERT_DOUBLE_EQ(66.0L, matH.GetData(2, 1));
	ASSERT_DOUBLE_EQ(69.0L, matH.GetData(2, 2));

}

TEST(Matrix_Test, GaussianElimination)
{
	Matrix matA = Matrix(3, 4);

	matA.SetData(2.0L, 0, 0);
	matA.SetData(3.0L, 0, 1);
	matA.SetData(3.0L, 0, 2);
	matA.SetData(5.0L, 0, 3);
	matA.SetData(3.0L, 1, 0);
	matA.SetData(2.0L, 1, 1);
	matA.SetData(-1.0L, 1, 2);
	matA.SetData(-4.0L, 1, 3);
	matA.SetData(5.0L, 2, 0);
	matA.SetData(4.0L, 2, 1);
	matA.SetData(2.0L, 2, 2);
	matA.SetData(3.0L, 2, 3);

	matA.RowAddition(1, -matA.GetData(1, 0) / matA.GetData(0, 0), 0);
	matA.RowAddition(2, -matA.GetData(2, 0) / matA.GetData(0, 0), 0);

	ASSERT_DOUBLE_EQ(2.0L, matA.GetData(0, 0));
	ASSERT_DOUBLE_EQ(3.0L, matA.GetData(0, 1));
	ASSERT_DOUBLE_EQ(3.0L, matA.GetData(0, 2));
	ASSERT_DOUBLE_EQ(5.0L, matA.GetData(0, 3));
	ASSERT_DOUBLE_EQ(0.0L, matA.GetData(1, 0));
	ASSERT_DOUBLE_EQ(-2.5L, matA.GetData(1, 1));
	ASSERT_DOUBLE_EQ(-5.5L, matA.GetData(1, 2));
	ASSERT_DOUBLE_EQ(-11.5L, matA.GetData(1, 3));
	ASSERT_DOUBLE_EQ(0.0L, matA.GetData(2, 0));
	ASSERT_DOUBLE_EQ(-3.5L, matA.GetData(2, 1));
	ASSERT_DOUBLE_EQ(-5.5L, matA.GetData(2, 2));
	ASSERT_DOUBLE_EQ(-9.5L, matA.GetData(2, 3));

	matA.RowAddition(2, -matA.GetData(2, 1) / matA.GetData(1, 1), 1);
	ASSERT_DOUBLE_EQ(2.0L, matA.GetData(0, 0));
	ASSERT_DOUBLE_EQ(3.0L, matA.GetData(0, 1));
	ASSERT_DOUBLE_EQ(3.0L, matA.GetData(0, 2));
	ASSERT_DOUBLE_EQ(5.0L, matA.GetData(0, 3));
	ASSERT_DOUBLE_EQ(0.0L, matA.GetData(1, 0));
	ASSERT_DOUBLE_EQ(-2.5L, matA.GetData(1, 1));
	ASSERT_DOUBLE_EQ(-5.5L, matA.GetData(1, 2));
	ASSERT_DOUBLE_EQ(-11.5L, matA.GetData(1, 3));
	ASSERT_DOUBLE_EQ(0.0L, matA.GetData(2, 0));
	ASSERT_DOUBLE_EQ(0.0L, matA.GetData(2, 1));
	ASSERT_DOUBLE_EQ(2.2L, matA.GetData(2, 2));
	ASSERT_DOUBLE_EQ(6.6L, matA.GetData(2, 3));


}

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

	Gaussian_Elimination Gauss;


	Matrix vecX;
	vecX = Gauss.GetAnswer(matA, vecB);

	ASSERT_DOUBLE_EQ(1.0L, vecB.GetData(0, 0));
	ASSERT_DOUBLE_EQ(-2.0L, vecB.GetData(1, 0));
	ASSERT_DOUBLE_EQ(3.0L, vecB.GetData(2, 0));

	ASSERT_DOUBLE_EQ(-8.0L/11.0L, vecX.GetData(0, 0));
	ASSERT_DOUBLE_EQ(-6.0L/11.0L, vecX.GetData(0, 1));
	ASSERT_DOUBLE_EQ(9.0L/11.0L, vecX.GetData(0, 2));
	ASSERT_DOUBLE_EQ(1.0L, vecX.GetData(1, 0));
	ASSERT_DOUBLE_EQ(1.0L, vecX.GetData(1, 1));
	ASSERT_DOUBLE_EQ(-1.0L, vecX.GetData(1, 2));
	ASSERT_DOUBLE_EQ(-2.0L/11.0L, vecX.GetData(2, 0));
	ASSERT_DOUBLE_EQ(-7.0L/11.0L, vecX.GetData(2, 1));
	ASSERT_DOUBLE_EQ(5.0L/11.0L, vecX.GetData(2, 2));


}


TEST(RINEX_NavigationMessage, Read)
{
	std::string filename = "05311710.13";
	RINEX_NavigationMessage nav_message(filename);

	nav_message.Read(true);

	std::map <int, Ephemeris> ephem_map = nav_message.GetEphemeris(GPS_Time(1745, 388800.0L, 0), -1, true); // 2013-06-20 12:00:00

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
	ASSERT_EQ(193, it->first);
	ASSERT_DOUBLE_EQ(6, it->second.GetData(Ephemeris::IODE));
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


TEST(RINEX_NavigationMessage, CalculatePosition2)
{
	std::string filename = "mtka3180.05";
	RINEX_NavigationMessage nav_message(filename);

	nav_message.Read(false);

	RINEX_ObservationData obs_data(filename, nav_message.GetLeapSecond());


	std::multimap<GPS_Time, PsudoRange> psuRange = obs_data.GetPsudoRange();

	std::map<int, PsudoRange> range;
	GPS_Time cur;

	for (std::multimap<GPS_Time, PsudoRange>::iterator it = psuRange.begin(); it != psuRange.end(); it++)
	{
		// 2005-11-14 00:00:00
		if (fabs(it->first - GPS_Time(1349, 86400.0, 0)) < 1.0e-5)
		{
			range.insert(std::pair<int, PsudoRange>((it->second).GetPRN(), it->second));
			cur = it->first;
		}
		else
		{
			// Do nothing
		}

	}

	std::map <int, Ephemeris> ephem_map = nav_message.GetEphemeris(cur, -1, false);

	Calculate_Position cal(ephem_map, range, signalType::L1CA, cur, nav_message.GetIon());

	ReceiverOutput position = cal.GetPosition(0.0L);

// relative effect collection
	ASSERT_NEAR(-3947762.6273452728, position.GetPosition().GetX(), 1.0e-8);
	ASSERT_NEAR(3364400.5446071858, position.GetPosition().GetY(), 1.0e-8);
	ASSERT_NEAR(3699431.230931337, position.GetPosition().GetZ(), 1.0e-8);

	range.clear();
	ephem_map.clear();

	for (std::multimap<GPS_Time, PsudoRange>::iterator it = psuRange.begin(); it != psuRange.end(); it++)
	{
		// 2005-11-14 00:32:00
		if (fabs(it->first - GPS_Time(1349, 88320.0, 0)) < 1.0e-5)
		{
			range.insert(std::pair<int, PsudoRange>((it->second).GetPRN(), it->second));
			cur = it->first;
		}
		else
		{
			// Do nothing
		}

	}

	ephem_map = nav_message.GetEphemeris(cur, -1, false);

	cal = Calculate_Position(ephem_map, range, signalType::L1CA, cur, nav_message.GetIon());

	position = cal.GetPosition(0.0L);

	ASSERT_NEAR(-3947765.2127858549, position.GetPosition().GetX(), 1.0e-8);
	ASSERT_NEAR(3364401.930418036, position.GetPosition().GetY(), 1.0e-8);
	ASSERT_NEAR(3699431.3939317954, position.GetPosition().GetZ(), 1.0e-8);

}

TEST(RINEX_NavigationMessage, CalculatePosition21)
{
	std::string filename = "mtka3180.05";
	RINEX_NavigationMessage nav_message(filename);

	nav_message.Read(false);

	RINEX_ObservationData obs_data(filename, nav_message.GetLeapSecond());

	std::multimap<GPS_Time, PsudoRange> psuRange = obs_data.GetPsudoRange();

	std::map<int, PsudoRange> range;
	GPS_Time cur;
	std::map <int, Ephemeris> ephem_map;
	Calculate_Position cal;

	std::multimap<GPS_Time, PsudoRange>::iterator it = psuRange.begin();
	std::pair<std::multimap<GPS_Time, PsudoRange>::iterator,
	std::multimap<GPS_Time, PsudoRange>::iterator> r_it = psuRange.equal_range(it->first);

	do
	{
		range.clear();
		ephem_map.clear();

		cur = it->first;
		for (std::multimap<GPS_Time, PsudoRange>::iterator its = r_it.first; its != r_it.second; its++)
		{
			range.insert(std::pair<int, PsudoRange>((its->second).GetPRN(), its->second));
		}
		ephem_map = nav_message.GetEphemeris(cur, -1, false);
		cal = Calculate_Position(ephem_map, range, signalType::L1CA, cur, nav_message.GetIon());

		ReceiverOutput position = cal.GetPosition(0.0L);


		it = r_it.second;
		if (it != psuRange.end())
		{
			r_it = psuRange.equal_range(it->first);
		}
		else
		{
			break;
		}

	} while (it != psuRange.end());





}

TEST(RINEX_NavigationMessage, CalculatePosition212withoutQZSS)
{
	std::string filename = "05311710.13";
	RINEX_NavigationMessage nav_message(filename);

	nav_message.Read(false);

	RINEX_ObservationData obs_data(filename, nav_message.GetLeapSecond());


	std::multimap<GPS_Time, PsudoRange> psuRange = obs_data.GetPsudoRange();

	std::map<int, PsudoRange> range;
	GPS_Time cur;

	std::multimap<GPS_Time, PsudoRange>::iterator it = psuRange.begin();
	std::pair<std::multimap<GPS_Time, PsudoRange>::iterator,
	std::multimap<GPS_Time, PsudoRange>::iterator> r_it = psuRange.equal_range(it->first);

	do
	{
		range.clear();


		for (std::multimap<GPS_Time, PsudoRange>::iterator its = r_it.first; its != r_it.second; its++)
		{
			range.insert(std::pair<int, PsudoRange>((its->second).GetPRN(), its->second));
			cur = its->first;

		}
		std::map <int, Ephemeris> ephem_map = nav_message.GetEphemeris(cur, -1, false);
		Calculate_Position cal(ephem_map, range, signalType::L1CA, cur, nav_message.GetIon());

		ReceiverOutput position = cal.GetPosition(0.0L);

		if (fabs(cur - GPS_Time(1745, 388230.0, 16)) < 1.0e-5)
		{
			ASSERT_NEAR(-3814969.60410609, position.GetPosition().GetX(), 1.0e-8);
			ASSERT_NEAR(2699236.3398733628, position.GetPosition().GetY(), 1.0e-8);
			ASSERT_NEAR(4326126.7209189935, position.GetPosition().GetZ(), 1.0e-7);
		}

		it = r_it.second;
		if (it != psuRange.end())
		{
			r_it = psuRange.equal_range(it->first);
		}
		else
		{
			break;
		}

	} while (it != psuRange.end());

}

TEST(RINEX_NavigationMessage, CalculatePosition212withQZSS)
{
	std::string filename = "05311710.13";
	RINEX_NavigationMessage nav_message(filename);

	nav_message.Read(true);

	RINEX_ObservationData obs_data(filename, nav_message.GetLeapSecond());


	std::multimap<GPS_Time, PsudoRange> psuRange = obs_data.GetPsudoRange();

	std::map<int, PsudoRange> range;
	GPS_Time cur;

	std::multimap<GPS_Time, PsudoRange>::iterator it = psuRange.begin();
	std::pair<std::multimap<GPS_Time, PsudoRange>::iterator,
	std::multimap<GPS_Time, PsudoRange>::iterator> r_it = psuRange.equal_range(it->first);

	do
	{
		range.clear();


		for (std::multimap<GPS_Time, PsudoRange>::iterator its = r_it.first; its != r_it.second; its++)
		{
			range.insert(std::pair<int, PsudoRange>((its->second).GetPRN(), its->second));
			cur = its->first;

		}
		std::map <int, Ephemeris> ephem_map = nav_message.GetEphemeris(cur, -1, true);
		Calculate_Position cal(ephem_map, range, signalType::L1CA, cur, nav_message.GetIon());

		ReceiverOutput position = cal.GetPosition(WGS84_Frame::Deg2Rad(00.0L));

		if (fabs(cur - GPS_Time(1745, 388230.0, 16)) < 1.0e-5)
		{
			ASSERT_NEAR(-3814970.2604134339, position.GetPosition().GetX(), 1.0e-8);
			ASSERT_NEAR(2699236.998314104, position.GetPosition().GetY(), 1.0e-7);
			ASSERT_NEAR(4326126.8061326146, position.GetPosition().GetZ(), 1.0e-7);
		}

		it = r_it.second;
		if (it != psuRange.end())
		{
			r_it = psuRange.equal_range(it->first);
		}
		else
		{
			break;
		}

	} while (it != psuRange.end());

}
