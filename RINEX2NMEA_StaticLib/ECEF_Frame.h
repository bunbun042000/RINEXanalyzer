/*
 * ECEF_Frame.h
 *
 *  Created on: 2013/06/10
 *      Author: bun
 */

#ifndef ECEF_FRAME_H_
#define ECEF_FRAME_H_

class CECEF_Frame
{
public:
	CECEF_Frame();
	CECEF_Frame(long double x0, long double y0, long double z0);
	CECEF_Frame(const CECEF_Frame &ecef_f);
	virtual ~CECEF_Frame();

	long double Distance(const CECEF_Frame &origin);
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

protected:
	long double x;
	long double y;
	long double z;

};


#endif /* ECEF_FRAME_H_ */
