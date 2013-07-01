/*
 * Matrix.h
 *
 *  Created on: 2013/06/13
 *      Author: bun
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <cmath>

class Matrix
{
	friend Matrix operator*(Matrix &s, const long double x);
	friend Matrix operator*(long double x, Matrix &s);

public:
	Matrix();
	Matrix(int lin, int col);
	Matrix(const Matrix &mat);
	virtual ~Matrix();

	Matrix operator+(Matrix &s);
	Matrix operator-(Matrix &s);
	Matrix operator*(Matrix &s2);
	Matrix& operator=(const Matrix &s);
	Matrix& operator+=(Matrix &s);

	bool SetData(long double x, int row, int column);
	bool SetLine(const long double *row_data, int row, int max_col);
	bool SetColumn(const long double *column_data, int column, int max_lin);

	bool SwapRow(int source, int dest);
	void RowMultiplation(const long double x, const int row);
	void RowAddition(const int row_a, const long double x, const int row_b);

	Matrix Tranposed();

	int Pivot(const int from_row);

	bool IsValid()
	{
		return valid;
	}

	long double GetData(int line, int column)
	{
		long double dat = data[row_index[line] * max_column + column_index[column]];
		return dat;
	};

	int GetMaxColumn()
	{
		return max_column;
	};

	int GetMaxRow()
	{
		return max_row;
	};


private:
	int max_column;
	int max_row;
	long double *data;

	int *column_index;
	int *row_index;

	bool valid;

	void DeleteHeap();
	bool InitHeap(int max_lin, int max_col, int *l_index, int *c_index, long double *s_data);

};


#endif /* MATRIX_H_ */
