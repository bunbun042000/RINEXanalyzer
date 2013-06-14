/*
 * Matrix.cpp
 *
 *  Created on: 2013/06/13
 *      Author: bun
 */


#include "Matrix.h"
#include <iostream>

CMatrix::CMatrix()
{
	max_column = 0;
	max_line = 0;

	data = 0;

	valid = false;
}
CMatrix::CMatrix(int col, int lin)
{
	max_column = col;
	max_line = lin;

	data = new long double[max_column * max_line];

	valid = true;
}

CMatrix::CMatrix(const CMatrix &mat)
{
	int i, size;

	max_column = mat.max_column;
	max_line = mat.max_line;

	size = max_column * max_line;

	data = new long double[size];
	for(i = 0; i < size; i++)
	{
		data[i] = mat.data[i];
	}

	valid = mat.valid;

}

CMatrix::~CMatrix()
{
	max_column = 0;
	max_line = 0;

	if (data != 0)
	{
		delete [] data;
	}
	data = 0;

	valid = false;
}

bool CMatrix::SetData(long double x, int column, int line)
{
	if (column > max_column)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	if (line > max_line)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	data[line * max_column + column] = x;
	return true;

}


bool CMatrix::SetLine(const long double *line, int lin, int max_col)
{

	int i;

	if (max_column != max_col)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	if(lin > max_line)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	for (i = 0; i < max_column; i++)
	{
		SetData(line[i], i, lin);
	}
	return true;
}

bool CMatrix::SetColumn(const long double *column, int col, int max_lin)
{

	int i;

	if (max_line != max_lin)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	if(col > max_column)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	for (i = 0; i < max_line; i++)
	{
		this->SetData(column[i], col, i);
		std::cout << "data = " << std::fixed <<  this->GetData(col, i) << ", col = " << col << ", i = " << i << "\n";
	}
	return true;

}

CMatrix CMatrix::operator+(CMatrix &s)
{

	CMatrix dest;

	if ((max_column != s.max_column) || (max_line != s.max_line))
	{
		return dest;
	}
	else
	{
		// Do nothing
	}

	dest = CMatrix(this->max_column, this->max_line);

	int i, size;

	size = dest.max_column * dest.max_line;

	for(i = 0; i < size; i++)
	{
			dest.data[i] = this->data[i] + s.data[i];
			std::cout << "data = " << std::fixed <<  dest.data[i] << ", i = " << i << "\n";
	}

	return dest;

}

CMatrix CMatrix::operator-(CMatrix &s)
{

	CMatrix dest;

	if ((max_column != s.max_column) || (max_line != s.max_line))
	{
		return dest;
	}
	else
	{
		// Do nothing
	}

	dest = CMatrix(s.max_column, s.max_line);

	int i, j;

	for(i = 0; i < dest.max_column; i++)
	{
		for(j = 0; j < dest.max_line; j++)
		{
			dest.SetData(GetData(i, j) - s.GetData(i, j), i, j);
		}
	}

	return dest;

}

CMatrix CMatrix::operator*(CMatrix &s)
{
	CMatrix dest;

	if ((max_column != s.max_line) || (max_line != s.max_column))
	{
		return dest;
	}
	else
	{
		// Do nothing
	}

	dest = CMatrix(max_line, s.max_column);

	int i, j, k;

	for(i = 0; i < dest.max_column; i++)
	{
		for(j = 0; j < s.max_line; j++)
		{
			for (k = 0; j < max_column; k++)
			{
				dest.SetData(GetData(k, j) * s.GetData(i, k), i, j);
			}
		}
	}

	return dest;

}

CMatrix operator*(CMatrix &s, long double x)
{

	CMatrix dest(s.max_column, s.max_line);

	int i, j;

	for(i = 0; i < dest.max_column; i++)
	{
		for(j = 0; j < dest.max_line; j++)
		{
			dest.SetData(s.GetData(i, j), i, j);
		}
	}

	return dest;

}

CMatrix operator*(long double x, CMatrix &s)
{

	return s * x;

}
