/*
 * Matrix.cpp
 *
 *  Created on: 2013/06/13
 *      Author: bun
 */


#include "Matrix.h"
#include <iostream>

Matrix::Matrix()
{
	data = 0;
	column_index = 0;
	row_index = 0;
	DeleteHeap();
	InitHeap(0, 0, 0, 0, 0);
}

Matrix::Matrix(int row, int col)
{
	data = 0;
	column_index = 0;
	row_index = 0;
	DeleteHeap();
	InitHeap(row, col, 0, 0, 0);

}

Matrix::Matrix(const Matrix &mat)
{
	data = 0;
	column_index = 0;
	row_index = 0;
	DeleteHeap();
	InitHeap(mat.max_row, mat.max_column, mat.row_index, mat.column_index, mat.data);

}

Matrix::~Matrix()
{
	DeleteHeap();

}

bool Matrix::SetData(long double x, int row, int column)
{
	if (column > max_column)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	if (row > max_row)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	if (data == 0)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	if (column_index == 0)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	if (row_index == 0)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	data[row_index[row] * max_column + column_index[column]] = x;
	return true;

}


bool Matrix::SetLine(const long double *line, int lin, int max_col)
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

	if(lin > max_row)
	{
		return false;
	}
	else
	{
		// Do nothing
	}

	for (i = 0; i < max_column; i++)
	{
		SetData(line[i], lin, i);
	}
	return true;
}

bool Matrix::SetColumn(const long double *column, int col, int m_row)
{

	int i;

	if (max_row!= m_row)
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

	for (i = 0; i < max_row; i++)
	{
		this->SetData(column[i], i, col);
	}
	return true;

}

bool Matrix::SetSize(int row, int col)
{
	data = 0;
	column_index = 0;
	row_index = 0;
	DeleteHeap();
	return InitHeap(row, col, 0, 0, 0);
}

bool Matrix::SwapRow(int source, int dest)
{
	if ((source < max_row) && (dest < max_row))
	{
		std::swap(row_index[source], row_index[dest]);
		return true;
	}
	else
	{
		// Do nothing
	}
	return false;
}

Matrix Matrix::operator+(Matrix &s)
{

	Matrix dest;

	if ((max_column != s.max_column) || (max_row != s.max_row))
	{
		return dest;
	}
	else
	{
		// Do nothing
	}

	dest.InitHeap(this->max_column, this->max_row, 0, 0, 0);

	int i, j;


	for(i = 0; i < max_row; i++)
	{
		for(j = 0; j < max_column; j++)
		{
			dest.SetData(GetData(i, j) + s.GetData(i, j), i, j);

		}
	}

	return dest;

}


Matrix& Matrix::operator+=(Matrix &s)
{

	if ((max_column != s.max_column) || (max_row != s.max_row))
	{
		return *this;
	}
	else
	{
		// Do nothing
	}


	int i, j;
	long double temp;


	for(i = 0; i < max_row; i++)
	{
		for(j = 0; j < max_column; j++)
		{
			temp = GetData(i, j) + s.GetData(i, j);
			SetData(temp, i, j);

		}
	}

	return *this;
}


Matrix Matrix::operator-(Matrix &s)
{

	Matrix dest;

	if ((max_column != s.max_column) || (max_row != s.max_row))
	{
		return dest;
	}
	else
	{
		// Do nothing
	}

	dest = Matrix(s.max_column, s.max_row);

	int i, j;

	for (i = 0; i < max_row; i++)
	{
		for (j = 0; j < max_column; j++)
		{
			dest.SetData(GetData(i, j) - s.GetData(i, j), i, j);
		}
	}

	return dest;

}

Matrix Matrix::operator*(Matrix &s2)
{

	Matrix dest;

	if (max_column != s2.max_row)
	{
		return dest;
	}
	else
	{
		// Do nothing
	}


	dest = Matrix(max_row, s2.max_column);


	int i, j, k;
	long double temp;

	for(i = 0; i < dest.max_row; i++)
	{
		for(j = 0; j < dest.max_column; j++)
		{
			temp = 0.0L;
			for (k = 0; k < max_column; k++)
			{
				temp += GetData(i, k) * s2.GetData(k, j);
			}
			dest.SetData(temp, i, j);
		}
	}

	return dest;

}

Matrix& Matrix::operator=(const Matrix &s)
{
	InitHeap(s.max_row, s.max_column, s.row_index, s.column_index, s.data);
	return *this;
}

void Matrix::RowMultiplation(const long double x, const int row)
{
	int i;

	for (i = 0; i < max_column; i++)
	{
		SetData(x * GetData(row, i), row, i);
	}
}

void Matrix::RowAddition(const int row_a, const long double x, const int row_b)
{

	int i;

	for (i = 0; i < max_column; i++)
	{
		SetData(GetData(row_a, i) + x * GetData(row_b, i), row_a, i);
	}
}

Matrix Matrix::Tranposed()
{
	Matrix dest = Matrix(max_column, max_row);
	int i, j;

	for (i = 0; i < max_row; i++)
	{
		for (j = 0; j < max_column; j++)
		{
			dest.SetData(GetData(i, j), j, i);
		}
	}

	return dest;
}

int Matrix::Pivot(const int from_row)
{

	long double temp = 0.0L;

	if (!(from_row < max_column))
	{
		return -1;
	}
	else
	{
		// Do nothing
	}

	int m_row = from_row;
	for (int i = from_row; i < max_row; i++)
	{
		m_row = i;
		if (temp > fabs(GetData(i, from_row)))
		{
			temp = fabs(GetData(i, from_row));
			m_row = i;
		}
	}

	return m_row;

}


void Matrix::DeleteHeap()
{
	max_column = 0;
	max_row = 0;

	if (data != 0)
	{
		delete [] data;
	}
	else
	{
		// Do nothing
	}
	data = 0;

	if (column_index != 0)
	{
		delete [] column_index;
	}
	else
	{
		// Do nothing
	}
	column_index = 0;

	if (row_index != 0)
	{
		delete [] row_index;
	}
	else
	{
		// Do nothing
	}
	row_index = 0;

	valid = false;
}

bool Matrix::InitHeap(int m_row, int m_column, int *l_index, int *c_index, long double *s_data)
{
	int i, size;

	max_column = m_column;
	max_row = m_row;

	if (column_index != 0)
	{
		delete [] column_index;
	}
	else
	{
		// Do nothing
	}

	column_index = new int[m_column];

	for (i = 0; i < max_column; i++)
	{
		column_index[i] = i;
	}

	if (row_index != 0)
	{
		delete [] row_index;
	}
	else
	{
		// Do nothing
	}

	row_index = new int[max_row];
	for (i = 0; i < max_row; i++)
	{
		row_index[i] = i;
	}


	size = max_column * max_row;

	if (data != 0)
	{
		delete [] data;
	}
	else
	{
		// Do nothing
	}

	data = new long double[size];

	if ((s_data != 0) && (l_index != 0) && (c_index != 0)){
		int i, j;

		for (i = 0; i < max_row; i++)
		{
			for (j = 0; j < max_column; j++)
			{
				this->SetData(s_data[l_index[i] * max_column + c_index[j]], i ,j);
			}
		}
	}
	else
	{
		// Do nothing
	}

	valid = true;

	return valid;
}

Matrix operator*(Matrix &s, const long double x)
{

	Matrix dest(s.max_column, s.max_row);

	int i, j;

	for(i = 0; i < dest.max_row; i++)
	{
		for(j = 0; j < dest.max_column; j++)
		{
			dest.SetData(x * s.GetData(i, j), i, j);
		}
	}

	return dest;

}

Matrix operator*(long double x, Matrix &s)
{

	return s * x;

}

