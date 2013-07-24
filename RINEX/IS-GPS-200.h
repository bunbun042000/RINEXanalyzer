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
 * IS-GPS-200.h
 *
 *  Created on: 2013/07/07
 *      Author: bun
 */

#ifndef IS_GPS_200_H_
#define IS_GPS_200_H_

namespace IS_GPS_200
{
	static const long double GPS_Pi = 3.1415926535898; // From IS-GPS-200G(05 Sep. 2012) p.154
	static const long double C_velocity = 2.99792458e+8; // From IS-GPS-200G(05 Sep. 2012) p.126
	static const long double GMe = 3.986005e+14; // From IS-GPS-200G(05 Sep. 2012) p.93
	static const long double Omega_E = 7.2921151467e-5; // From IS-GPS-200G(05 Sep. 2012) p.100

}


#endif /* IS_GPS_200_H_ */
