/*
 * Copyright (c) 2013 Yamagata Fumihiro.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * 
 * Contributors:
 *     Yamagata Fumihiro - initial API and implementation
 */

#ifndef RINEXANALYZER_H_
#define RINEXANALYZER_H_

#include <ostream>

const static std::string output_dummy_filename = "dummy.csv";

void print_simplehelp(const std::string targetname);
void print_help(const std::string targetname);
void OutputNMEA0183(std::ostream &out, std::map<GPS_Time, ReceiverOutput> outdata);
void OutputDifference(std::ostream &out, std::map<GPS_Time, ReceiverOutput> outdata, ECEF_Frame origin, bool header);
void OutputSatellitePsudodiff(std::ostream &out, std::map<GPS_Time, ReceiverOutput> outdata, ECEF_Frame origin, bool header);

bool GetAveragePosition(std::map<GPS_Time, ReceiverOutput> &outdata, ECEF_Frame &origin);

#endif /* RINEXANALYZER_H_ */
