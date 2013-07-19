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
	stream << ",";

	// Latitude
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
		stream << "N,";
	}
	else
	{
		stream << "S,";
	}

	// Longitude
	long double longi = pos.GetLongi();
	longi = WGS84_Frame::Rad2Deg(longi);
	temp = fabs(longi);
	int longi_deg = (int)temp;
	long double longi_sec = (temp - longi_deg) * 60;
	stream << std::setw(3) << std::setfill('0');
	stream << longi_deg;
	stream << std::setw(7) << std::setfill('0');
	stream << std::setprecision(4);
	stream << longi_sec;
	stream << ",";
	if (longi > 0)
	{
		stream << "E,";
	}
	else
	{
		stream << "W,";
	}

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
	stream << std::setprecision(3) << std::fixed << std::setfill('0');
	stream << pos.GetG_Height();
	stream << ",M,";

	// Geoidal Separation
	stream << std::setprecision(3) << std::fixed << std::setfill('0');
	stream << 0.0;
	stream << ",M,";

	// Age of Differential GPS data
	stream << "0.0";
	stream <<",";

	// Differential reference station ID
	// Do nothing

	std::string out = CreateCheckSum(stream.str());

	out += "\r\n";
	return out;
}

//	std::string CreateGPGSV();


