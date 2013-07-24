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
 * NMEA0183.cpp
 *
 *  Created on: 2013/07/19
 *      Author: bun
 */

#include"NMEA0183.h"

NMEA0183::NMEA0183()
{

}
NMEA0183::~NMEA0183()
{

}

std::multimap<GPS_Time, std::string> NMEA0183::OutputNMEA0183(std::map<GPS_Time, ReceiverOutput>calculatedData)
{
	std::multimap<GPS_Time, std::string> out;
	out.clear();

	for (std::map<GPS_Time, ReceiverOutput>::iterator it = calculatedData.begin(); it != calculatedData.end(); it++)
	{
		out.insert(std::pair<GPS_Time, std::string>(it->first, CreateGPGGA(it->second)));
		out.insert(std::pair<GPS_Time, std::string>(it->first, CreateGPGSV(it->second)));
		out.insert(std::pair<GPS_Time, std::string>(it->first, CreateGPZDA(it->second)));
	}

	return out;
}

std::string NMEA0183::CreateCheckSum(std::string str)
{
	std::string out;
	out.clear();

	if (str.empty())
	{
		return out;
	}
	else
	{
		// Do nothing
	}
	std::string::size_type position = str.find('$');

	if ((position == std::string::npos) || (position != 0))
	{
		return out;
	}
	else
	{
		// Do nothing
	}

	int checksum = 0;
	for (int i = 1; i < (int)str.size(); i++)
	{
		checksum ^= str[i];
	}

	out = str;

	std::ostringstream stream;

	stream << std::hex;
	stream << std::setw(2) <<std::setiosflags(std::ios::uppercase);
	stream << checksum;
	out += '*';
	out += stream.str();

	return out;
}

std::string NMEA0183::CreateGPGGA(ReceiverOutput data)
{
	std::ostringstream stream;

	stream << "$GPGGA,";

	// UTC
	stream << CreateUTCtime(data);
	stream << ',';

	// Latitude
	stream << CreateLatitude(data);
	stream << ',';

	// Longitude
	stream << CreateLongitude(data);
	stream << ',';

	// GPS Quality
	stream << "1,";

	// Number of Satellites in use
	int number_of_sats = data.GetNumberOfSatellites();
	if (number_of_sats > 13)
	{
		number_of_sats = 12;
	}
	else
	{
		// Do nothing
	}
	stream << std::setw(2) << std::setfill('0');
	stream << number_of_sats;
	stream << ",";

	// HDOP
	stream << std::setprecision(1) << std::fixed << std::setw(2);
	stream << data.GetHDOP();
	stream << ",";

	// Altitude
	WGS84_Frame pos = data.GetPosition();

	stream << std::setprecision(3) << std::fixed << std::setfill('0');
	stream << pos.GetG_Height();
	stream << ",M,";

	// Geoidal Separation
	stream << std::setprecision(3) << std::fixed << std::setfill('0');
	stream << 0.0;
	stream << ",M,";

	// Age of Differential GPS data
	stream <<",";

	// Differential reference station ID
	// Do nothing

	std::string out = CreateCheckSum(stream.str());

	out += "\r\n";
	return out;
}

std::string NMEA0183::CreateGPGSV(ReceiverOutput data)
{
	std::string createGSV;
	createGSV.clear();

	std::map<int, SatellitesInView> skyplot = data.GetSkyPlot();
	int total_number_of_lines = (int)(data.GetNumberOfSatellites()
			/ GSV_Max_number_of_satellites_per_line);

	if (data.GetNumberOfSatellites() % GSV_Max_number_of_satellites_per_line != 0)
	{
		total_number_of_lines++;
	}
	else
	{
		// Do nothing
	}

	int sats = 0;
	std::ostringstream stream;

	for (std::map<int, SatellitesInView>::iterator it = skyplot.begin(); it != skyplot.end(); it++)
	{

		if (sats == 0 || (sats % GSV_Max_number_of_satellites_per_line) == 0)
		{
			stream << "$GPGSV,";
			stream << total_number_of_lines<< ',';
			stream << (int)(sats / GSV_Max_number_of_satellites_per_line) + 1 << ',';
			stream << std::setw(2) << std::setfill('0');
			stream << data.GetNumberOfSatellites();

		}
		else
		{
			// Do nothing
		}

		stream << ',';
		stream << std::setw(3) << std::setfill('0') << it->first << ',';
		stream << std::setw(2) << std::setfill('0') << (int) it->second.elevation << ',';
		stream << std::setw(3) << std::setfill('0') << (int) it->second.azimuth << ',';
		stream << std::setw(2) << std::setfill('0') << (int) it->second.SNR;

		sats++;
		if (((sats % GSV_Max_number_of_satellites_per_line)	== 0) ||
				(sats == data.GetNumberOfSatellites()))
		{
			if (((sats % GSV_Max_number_of_satellites_per_line)	!= 0) &&
					(sats == data.GetNumberOfSatellites()))
			{
				stream << ',';
			}
			else
			{
				// Do nothing
			}
			std::string out = CreateCheckSum(stream.str());
			out += "\r\n";
			createGSV += out;
			stream.str("");
			stream.clear(std::ostringstream::goodbit);
		}
		else
		{
			// Do nothing
		}

	}

	return createGSV;

}

std::string NMEA0183::CreateGPZDA(ReceiverOutput data)
{
	std::ostringstream stream;

	stream << "$GPZDA,";

	// UTC
	stream << CreateUTCtime(data);
	stream << ",";

	tm tmbuf = data.GetTime().ToDate();
	stream << std::setw(2) << std::setfill('0') << tmbuf.tm_mday << ',';
	stream << std::setw(2) << std::setfill('0') << tmbuf.tm_mon + 1 << ',';
	stream << std::setw(4) << std::setfill('0') << tmbuf.tm_year + 1900;

	// local time zone hours
	stream << ',';

	// local time zone minutes
	stream << ',';

	std::string out = CreateCheckSum(stream.str());

	out += "\r\n";
	return out;

}

std::string NMEA0183::CreateUTCtime(ReceiverOutput data)
{
	std::ostringstream stream;

	tm tmbuf = data.GetTime().ToDate();
	stream << std::setw(2) << std::setfill('0');
	stream << tmbuf.tm_hour;
	stream << std::setw(2) << std::setfill('0');
	stream << tmbuf.tm_min;
	stream << std::setw(6) << std::setfill('0') << std::fixed;
	stream << std::setprecision(3);
	double temp1 = (double)(data.GetTime().GetSecond() - data.GetTime().GetLeapSecond());
	double sec = fmod(temp1, 60);
	stream << sec;

	return stream.str();
}

std::string NMEA0183::CreateLatitude(ReceiverOutput data)
{
	std::ostringstream stream;

	WGS84_Frame pos = data.GetPosition();
	long double lat = pos.GetLat();
	lat = WGS84_Frame::Rad2Deg(lat);
	long double temp = fabs(lat);
	int lat_deg = (int)temp;
	long double lat_sec = (temp - lat_deg) * 60;
	stream << std::setw(2) << std::setfill('0');
	stream << lat_deg;
	stream << std::setw(7) << std::setfill('0');
	stream << std::setprecision(4) << std::fixed;
	stream << lat_sec;
	stream << ",";
	if (lat > 0)
	{
		stream << "N";
	}
	else
	{
		stream << "S";
	}

	return stream.str();

}

std::string NMEA0183::CreateLongitude(ReceiverOutput data)
{
	std::ostringstream stream;

	WGS84_Frame pos = data.GetPosition();
	long double longi = pos.GetLongi();
	longi = WGS84_Frame::Rad2Deg(longi);
	long double temp = fabs(longi);
	int longi_deg = (int)temp;
	long double longi_sec = (temp - longi_deg) * 60;
	stream << std::setw(3) << std::setfill('0');
	stream << longi_deg;
	stream << std::setw(7) << std::setfill('0');
	stream << std::setprecision(4) << std::fixed;
	stream << longi_sec;
	stream << ",";
	if (longi > 0)
	{
		stream << 'E';
	}
	else
	{
		stream << 'W';
	}

	return stream.str();

}
