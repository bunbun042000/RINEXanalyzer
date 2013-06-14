/*
 * Matrix.h
 *
 *  Created on: 2013/06/13
 *      Author: bun
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <cmath>

class CMatrix
{
	friend CMatrix operator*(CMatrix &s, long double x);
	friend CMatrix operator*(long double x, CMatrix &s);

public:
	CMatrix();
	CMatrix(int col, int lin);
	CMatrix(const CMatrix &mat);
	virtual ~CMatrix();

	CMatrix operator+(CMatrix &s);
	CMatrix operator-(CMatrix &s);
	CMatrix operator*(CMatrix &s);

	bool SetData(long double x, int column, int line);
	bool SetLine(const long double *line, int lin, int max_col);
	bool SetColumn(const long double *column, int col, int max_lin);

	bool IsValid()
	{
		return valid;
	}

	long double GetData(int column, int line)
	{
		return data[line * max_column + column];
	};

	int GetMaxColumn()
	{
		return max_column;
	};

	int GetMaxLine()
	{
		return max_line;
	};


private:
	int max_column;
	int max_line;
	long double *data;

	bool valid;

};


#endif /* MATRIX_H_ */
