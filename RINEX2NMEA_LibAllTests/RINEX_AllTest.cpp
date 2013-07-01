/*
 * RINEX_AllTest.cpp
 *
 *  Created on: 2013/06/07
 *      Author: bun
 */


#include <gtest/gtest.h>
#include <cmath>
#include <iostream>

#include "Matrix.h"
#include "GPS_Time.h"
#include "ECEF_Frame.h"
#include "WGS84_Frame.h"
#include "ENU_Frame.h"

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


TEST(GPS_Time_Test, ToDate)
{
  GPS_Time gpstime;
  struct tm tbuf;
  gpstime = GPS_Time(1350, 100.0, 0);

  tbuf = gpstime.ToDate();
  ASSERT_EQ(2005, tbuf.tm_year+1900);
  ASSERT_EQ(11, tbuf.tm_mon+1);
  ASSERT_EQ(20, tbuf.tm_mday);
  ASSERT_EQ(00, tbuf.tm_hour);
  ASSERT_EQ(01, tbuf.tm_min);
  ASSERT_EQ(40, tbuf.tm_sec);

}

TEST(GPS_Time_Test, ToGPSTime1)
{
	GPS_Time gpstime;

	struct tm tbuf;
	tbuf.tm_year = 119;
	tbuf.tm_mon = 3;
	tbuf.tm_mday = 7;
	tbuf.tm_hour = 1;
	tbuf.tm_min = 1;
	tbuf.tm_sec = 40;

	gpstime = GPS_Time(tbuf, 0, 0);

	int week = gpstime.GetWeek();
	ASSERT_EQ(2048, week);
	ASSERT_DOUBLE_EQ(3700.0, gpstime.GetSecond());

}

TEST(GPS_Time_Test, ToGPSTime2)
{
	GPS_Time gpstime;

	struct tm tbuf;
	tbuf.tm_year = 80;
	tbuf.tm_mon = 0;
	tbuf.tm_mday = 6;
	tbuf.tm_hour = 0;
	tbuf.tm_min = 0;
	tbuf.tm_sec = 0;

	gpstime = GPS_Time(tbuf, 0, 0);

	ASSERT_EQ(0, gpstime.GetWeek());
	ASSERT_DOUBLE_EQ(0.0, gpstime.GetSecond());
}

TEST(ECEF_Frame_Test, ECEF_Frame_Basic)
{

	ECEF_Frame f1 = ECEF_Frame(10, 20, 30);

	ASSERT_DOUBLE_EQ(sqrt(1400), f1.Distance(ECEF_Frame(0.0L, 0.0L, 0.0L)));

	ECEF_Frame f2 = ECEF_Frame(30, 20, 10);

	ASSERT_DOUBLE_EQ(sqrt(800), f2.Distance(f1));
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
	ASSERT_NEAR(63.23233511, w1.GetG_Height(), 1.0e-5);

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

	CENU_Frame enu1 = CENU_Frame(200.0L, 100.0L, 300.0L, wgs84_origin);

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

	CENU_Frame enu1 = CENU_Frame(f1, wgs84_origin);

	ASSERT_NEAR(200.0L, enu1.GetE(), 1.0e-3);
	ASSERT_NEAR(100.0L, enu1.GetN(), 1.0e-3);
	ASSERT_NEAR(300.0L, enu1.GetU(), 1.0e-3);

}
