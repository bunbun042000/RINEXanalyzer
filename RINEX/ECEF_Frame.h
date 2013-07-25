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
 * ECEF_Frame.h
 *
 *  Created on: 2013/06/10
 *      Author: bun
 */

#ifndef ECEF_FRAME_H_
#define ECEF_FRAME_H_

#include <cmath>
#include "Matrix.h"

#ifdef _WIN32
#include <float.h>
#endif

class ECEF_Frame
{
public:
	ECEF_Frame();
	ECEF_Frame(long double x0, long double y0, long double z0);
	ECEF_Frame(const ECEF_Frame &orig);
	ECEF_Frame(Matrix &m);
	virtual ~ECEF_Frame();

	friend ECEF_Frame operator*(long double r, ECEF_Frame &pos);
	ECEF_Frame &operator=(const ECEF_Frame &orig)
	{
		x = orig.x;
		y = orig.y;
		z = orig.z;
		return *this;
	};

	ECEF_Frame &operator*(const long double r);
	ECEF_Frame operator+(const ECEF_Frame &pos);
	ECEF_Frame &operator+=(const ECEF_Frame &pos);

	bool IsValid()
	{
#ifdef _WIN32
		return  _finite(x) && _finite(y) && _finite(z);
#else
		return (!(std::isnan(x)) && !(std::isnan(y)) && !(std::isnan(z)))
				&& (!(std::isinf(x)) && !(std::isinf(y)) && !(std::isinf(z)));
#endif
	}
	
	long double Distance(const ECEF_Frame &origin);
	long double GetX()
	{
		return x;
	};
	long double GetY()
	{
		return y;
	};
	long double GetZ()
	{
		return z;
	};

	Matrix GetMatrix()
	{
		Matrix m = Matrix(3,1);
		m.SetData(x, 0, 0);
		m.SetData(y, 1, 0);
		m.SetData(z, 2, 0);
		return m;
	};

protected:
	long double x;
	long double y;
	long double z;

};


#endif /* ECEF_FRAME_H_ */
