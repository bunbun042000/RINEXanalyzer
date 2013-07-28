// ----------------------------------------------------------------------
// Copyright (c) 2013 Yamagata Fumihiro.
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the GNU Public License v2.0
// which accompanies this distribution, and is available at
// http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
// 
// Contributors:
//     Yamagata Fumihiro - initial API and implementation
// ----------------------------------------------------------------------

#include "stdafx.h"

#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

// Need for GetPot
#include <cstring>
// From http://getpot.sourceforge.net/
#include <GetPot>
#include "RINEX.h"

#include "RINEXanalyzer.h"

const static std::string ver = "0.01";

int main(int argc, char **argv)
{


	GetPot cl(argc, argv);

	if(cl.size() == 1)
	{
		print_simplehelp(cl[0]);
    }
		else if (cl.search(2, "--help", "-h"))
	{
		print_help(cl[0]);
	}
	else
	{
		// Do nothing
	}

	// QZSS use
	bool use_qzs = false;

	if(cl.search("--with-qzs"))
	{
		use_qzs = true;
	}
	else
	{
		// Do nothing
	}

	// elevation mask and weight
	const std::string elevation_mask_str = cl.follow("0.0", 2, "-m", "--mask");
	long double elevation_mask;
	sscanf(elevation_mask_str.c_str(), "%Lf", &elevation_mask);
	const long double elevation_mask_rad = WGS84_Frame::Deg2Rad(elevation_mask);

	if (elevation_mask_rad < WGS84_Frame::Deg2Rad(0.0L) ||
			elevation_mask_rad > WGS84_Frame::Deg2Rad(90.0L))
	{
		std::cerr << "<mask> is valid from 0.0 to 90.0 degree." << std::endl;
		std::cerr << "Refer \"" << cl[0] << " --help\" or \"" << cl[0] << " -h\"" << std::endl;
		exit(0);
	}
	else
	{
		// Do nothing
	}

	// weight method
	const std::string weight_str = cl.follow("0", 2, "-w", "--weight");
	const int weight = atoi(weight_str.c_str());

	if (weight != 0 && weight != 1)
	{
		std::cerr << "<weight method> should be \"0\" or \"1\"." << std::endl;
		std::cerr << "Refer \"" << cl[0] << " --help\" or \"" << cl[0] << " -h\"" << std::endl;
		exit(0);
	}

	if (cl.search(2, "-w", "--weight") && cl.search(2, "-m", "--mask"))
	{
		std::cerr << "option \"--mask\" and \"-w\" is exclusive!" << std::endl;
		std::cerr << "Refer \"" << cl[0] << " --help\" or \"" << cl[0] << " -h\"" << std::endl;
		exit(0);
	}
	else
	{
		// Do nothing
	}

	// parse filename
	std::string output_filename = cl.follow(output_dummy_filename.c_str(), 2, "-o", "--output");

	std::vector<std::string> filenames = cl.nominus_vector();

	std::string input_filename;

	for (unsigned int i = 0; i < filenames.size(); ++i)
	{
		if (filenames[i] != elevation_mask_str && filenames[i] != weight_str
				&& filenames[i] != output_filename)
		{
			input_filename = filenames[i];
			break;
		}
		else
		{
			continue;
		}
	}


	if (filenames.empty() || filenames.size() > 2)
	{
		print_simplehelp(cl[0]);
	}
	else
	{
		input_filename = filenames[0];
	}

	std::ofstream out;

	if (output_filename != output_dummy_filename)
	{
		out.open(output_filename.c_str());
		if (out.good())
		{
			// Do nothing
		}
		else
		{
			std::cerr << "Can't open " << output_filename << " for writing." << std::endl;
			exit(0);
		}
	}
	else
	{
		// Do nothing
	}


	if (cl.search(2, "-e", "--error") && cl.search(2, "-s", "--skyplot"))
	{
		std::cerr << "option \"-e\" and \"-s\" is exclusive!" << std::endl;
		std::cerr << "Refer \"" << cl[0] << " --help\" or \"" << cl[0] << " -h\"" << std::endl;
		exit(0);
	}
	else
	{
		// Do nothing
	}

	RINEX_NavigationMessage nav_message(input_filename);
	nav_message.Read();

	RINEX_ObservationData obs_data(input_filename);

	std::multimap<GPS_Time, PsudoRange> psuRange = obs_data.GetPsudoRange();

	std::map<int, PsudoRange> range;
	GPS_Time cur;

	// count observation time
	int number_of_observation = 0;

	for (std::multimap<GPS_Time, PsudoRange>::iterator iter = psuRange.begin(); iter != psuRange.end(); iter = psuRange.upper_bound(iter->first))
	{
		++number_of_observation;
	}

	std::cout << "number_of_observation = " << number_of_observation << std::endl;

	std::map<GPS_Time, ReceiverOutput> outdata;
	outdata.clear();

	int count = 0;
	int error_count = 0;

	for (std::multimap<GPS_Time, PsudoRange>::iterator r_it = psuRange.begin(); r_it != psuRange.end(); r_it = psuRange.upper_bound(r_it->first))
	{
		range.clear();

		for (std::multimap<GPS_Time, PsudoRange>::iterator its = r_it; its != psuRange.upper_bound(r_it->first); its++)
		{
			range.insert(std::pair<int, PsudoRange>((its->second).GetPRN(), its->second));
			cur = its->first;

		}
		std::map <int, Ephemeris> ephem_map = nav_message.GetEphemeris(cur, -1, use_qzs);
		Calculate_Position cal(ephem_map, range, PsudoRange::CA, cur, nav_message.GetIon());

		ReceiverOutput position = cal.GetPosition(elevation_mask_rad, weight);

		++count;
		std::cout << std::setw(6) << count << " / " << std::setw(6) << number_of_observation << " is calculated.\r" << std::flush;

		if (!position.GetPosition().IsValid())
		{
			++error_count;
		}
		else
		{
			// Do nothing
		}

		outdata.insert(std::pair<GPS_Time, ReceiverOutput>(position.GetTime(), position));

		ECEF_Frame origin(position.GetPosition());

	}

	std::cout << std::endl;

	ECEF_Frame origin(0.0L, 0.0L, 0.0L);

	if (cl.vector_variable_size("--origin") == 3)
	{
		long double latitude = cl("--origin", 0., 0);
		long double longitude = cl("--origin", 0., 1);
		long double elipisoidal_height = cl("--origin", 0., 2);
		if (latitude >= 90.0 || latitude <= -90.0)
		{
			std::cerr << "latitude is not valid!" << std::endl;
		}
		else if (longitude >= 180.0 || longitude <= -180.0)
		{
			std::cerr << "longitude is not valid!" << std::endl;
		}
		else
		{
			origin = WGS84_Frame(WGS84_Frame::Deg2Rad(latitude), WGS84_Frame::Deg2Rad(longitude), elipisoidal_height);

		}
	}
	else if (cl.search("--origin"))
	{
		std::cerr << "OPTIONS:" << std::endl;
		std::cerr << "    --origin='<lat> <long> <hgt>'";

	}

	bool outputheader;
	if (cl.search("--header"))
	{
		outputheader = true;
	}
	else
	{
		outputheader = false;
	}

	if (cl.search(2, "-n", "--nmea") || (!(cl.search(2, "-e", "--error")) && !(cl.search(2, "-s", "--skyplot"))))
	{
		if (out.is_open())
		{
			OutputNMEA0183(out, outdata);
		}
		else
		{
			OutputNMEA0183(std::cout, outdata);
		}
	}
	else if (cl.search(2, "-e", "--error"))
	{
		if (out.is_open())
		{
			OutputDifference(out, outdata, origin, outputheader);
		}
		else
		{
			OutputDifference(std::cout, outdata, origin, outputheader);
		}
	}
	else if (cl.search(2, "-s", "--skyplot"))
	{
		if (out.is_open())
		{
			OutputSatellitePsudodiff(out, outdata, origin, outputheader);
		}
		else
		{
			OutputSatellitePsudodiff(std::cout, outdata, origin, outputheader);
		}
	}
	else
	{
		//Do nothing
	}


	return 0;
}

void OutputDifference(std::ostream &out, std::map<GPS_Time, ReceiverOutput> outdata, ECEF_Frame origin, bool header)
{
	ECEF_Frame pos = origin;

	if (pos.Distance(ECEF_Frame(0.0L, 0.0L, 0.0L)) < 1.0e-10)
	{
		pos = GetAveragePosition(outdata);
	}
	else
	{
		// Do nothing
	}

	if (header)
	{
		out << "UTC Date,UTC Time,E error,N error,U error" << std::endl;
	}
	else
	{
		// Do nothing
	}

	for(std::map<GPS_Time, ReceiverOutput>::iterator it = outdata.begin(); it != outdata.end(); it++)
    {
		ENU_Frame enu_pos(it->second.GetPosition(), pos);
		out << it->second.GetTime().ISO8601_day() << ',';
		out << it->second.GetTime().ISO8601_time() << ',';

		out << std::fixed << enu_pos.GetE() << ',';
		out << std::fixed << enu_pos.GetN() << ',';
		out << std::fixed << enu_pos.GetU() << std::endl;

    }

}

void OutputNMEA0183(std::ostream &out, std::map<GPS_Time, ReceiverOutput> outdata)
{
	NMEA0183 getnmea;
	std::multimap<GPS_Time, std::string> nmea0183 = getnmea.OutputNMEA0183(outdata);
	for(std::multimap<GPS_Time, std::string>::iterator it = nmea0183.begin(); it != nmea0183.end(); it++)
	{
		out << it->second;

	}

}

void OutputSatellitePsudodiff(std::ostream &out, std::map<GPS_Time, ReceiverOutput> outdata, ECEF_Frame origin, bool header)
{
	// plot satellite elevation versus distance error
	ECEF_Frame pos = origin;

	if (pos.Distance(ECEF_Frame(0.0L, 0.0L, 0.0L)) < 1.0e-10)
	{
		pos = GetAveragePosition(outdata);
	}
	else
	{
		// Do nothing
	}

	if (header)
	{
		out << "UTC Date,UTC Time,PRN,elevation,azimuth,psudo distance,true distance,diff(=psudo - true),SNR" << std::endl;
	}
	else
	{
		// Do nothing
	}

	for (std::map<GPS_Time, ReceiverOutput>::iterator it = outdata.begin(); it != outdata.end(); it++)
    {
		std::map<int, SatellitesInView> skyplot = it->second.GetSkyPlot(pos);

		for (std::map<int, SatellitesInView>::iterator sats = skyplot.begin(); sats != skyplot.end(); sats++)
		{
			out << it->second.GetTime().ISO8601_day() << ',';
			out << it->second.GetTime().ISO8601_time() << ',';


			out << sats->second.PRN << ',';
			out << std::fixed << sats->second.elevation << ',';
			out << std::fixed << sats->second.azimuth  << ',';
			out << std::fixed << sats->second.psudodistance << ',';
			out << std::fixed << sats->second.truedistance << ',';
			out << std::fixed << sats->second.distancediff << ',';
			out << std::fixed << sats->second.SNR << std::endl;

		}

    }


}

ECEF_Frame GetAveragePosition(std::map<GPS_Time, ReceiverOutput> &outdata)
{
	long int i = 0;
	ECEF_Frame pos(0.0L, 0.0L, 0.0L);
	for(std::map<GPS_Time, ReceiverOutput>::iterator it = outdata.begin(); it != outdata.end(); it++)
    {
		ECEF_Frame posA = it->second.GetPosition();

		if (posA.IsValid())
		{
			i++;
			pos = ((i - 1.0L) / i) * pos + (1.0L / i) * posA;
		}
		else
		{
			// Do nothing
		}

    }

	return pos;

}

void print_simplehelp(const std::string targetname)
{
	std::cout << "RINEXanalyzer version " << ver << std::endl;
	std::cout << std::endl;
	std::cout << "usage: " << targetname << "[options] <infile> [outfile]" << std::endl;
	std::cout << std::endl;
	std::cout << "    [outfile] can be blank which means stdout." << std::endl;
	std::cout << std::endl;
	std::cout << "Try:" << std::endl;
	std::cout << "    \"" << targetname << " --help\"" << std::endl;
	std::cout << " or:" << std::endl;
	std::cout << "    \"" << targetname << " -h\"\t\tfor general usage information" << std::endl;

	exit(0);

}

void print_help(const std::string targetname)
{

	std::cout << "RINEXanalyzer version " << ver << std::endl;
	std::cout << std::endl;
	std::cout << "usage: " << targetname << "[options] <infile>" << std::endl;
	std::cout << std::endl;
	std::cout << "OPTIONS:" << std::endl;
	std::cout << "   -o, --output <outfile>               outputfile. If outfile is blank," << std::endl;
	std::cout << "                                        which means stdout." << std::endl;
	std::cout << std::endl;
	std::cout << "   -n, --nmea                           output NMEA0183 GPGGA, GPGSV" << std::endl;
	std::cout << "                                        and GPZDA sentences." << std::endl;
	std::cout << "                                        (default)" << std::endl;
	std::cerr << "   -e, --error  [--origin='<lat> <long> <hgt>']  output difference from average" << std::endl;
	std::cerr << "                                        position or '<lat> <long> <hgt>'." << std::endl;
	std::cout << "                                        The output is UTC and difference" << std::endl;
	std::cout << "                                        in ENU Frame." << std::endl;
	std::cout << "                                        -n, -e and -s are exclusive." << std::endl;
	std::cout << "                                        <lat> and <long> should be degree. " << std::endl;
	std::cout << "                                        <hgt> should be meter." << std::endl;
	std::cout << "                                        <lat> from -90.0000 to 90.0000." << std::endl;
	std::cout << "                                        <long> from -180.0000 to 180.0000." << std::endl;
	std::cerr << "   -s, --skyplot  [--origin='<lat> <long> <hgt>']  output satellites distance from average" << std::endl;
	std::cerr << "                                        position or '<lat> <long> <hgt>'." << std::endl;
	std::cout << "                                        The output is UTC, PRN, psudo distance," << std::endl;
	std::cout << "                                        true distance and true - psudo diff." << std::endl;
	std::cout << "                                        -n, -r and -d are exclusive." << std::endl;
	std::cout << "                                        <lat> and <long> should be degree. " << std::endl;
	std::cout << "                                        <hgt> should be meter." << std::endl;
	std::cout << "                                        <lat> from -90.0000 to 90.0000." << std::endl;
	std::cout << "                                        <long> from -180.0000 to 180.0000." << std::endl;
	std::cout << "   -m, --mask <mask>                    elevation mask in calculation." << std::endl;
	std::cout << "                                        -m and -w are exclusive." << std::endl;
	std::cout << "                                        <mask> should be degree." << std::endl;
	std::cout << "                                        <mask> from 0.0000 to 90.0000." << std::endl;
	std::cout << "   -w, --weight [<weight method>]       using elevation weight in calculation." << std::endl;
	std::cout << "                                        -m and -w are exclusive." << std::endl;
	std::cout << "                                        <weight method> 0 : Not weight (default)" << std::endl;
	std::cout << "                                        <weight meghot> 1 : weight" << std::endl;
	std::cout << "       --header                         output header line." << std::endl;
	std::cout << "                                        This option has effect in \"-r\" \"-d\" only." << std::endl;
	std::cout << "       --with-qzs                       Use QZS in position calculation if it is enable." << std::endl;

	exit(0);

}
