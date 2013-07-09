/*
 * Gaussian_Elimination.cpp
 *
 *  Created on: 2013/06/16
 *      Author: bun
 */

#include "Gaussian_Elimination.h"
#include <iostream>

Gaussian_Elimination::Gaussian_Elimination()
{
}


Gaussian_Elimination::~Gaussian_Elimination()
{
}

Matrix Gaussian_Elimination::GetAnswer(Matrix &mA, Matrix &vb)
{

	Matrix inverseA(mA.GetMaxRow(), mA.GetMaxColumn());

	for (int i = 0; i < inverseA.GetMaxRow(); i++)
	{
		for (int j = 0; j < inverseA.GetMaxColumn(); j++)
		{
			if (i == j)
			{
				inverseA.SetData(1.0L, i, j);
			}
			else
			{
				inverseA.SetData(0.0L, i, j);
			}
		}
	}


	Forward_Elimination(mA, inverseA, vb);
	Backward_Substitution(mA, inverseA, vb);

	return inverseA;

}

void Gaussian_Elimination::Forward_Elimination(Matrix &A, Matrix &inverseA, Matrix &b)
{

	int i, j, k;
	long double w;


	for (i = 0; i < A.GetMaxRow() - 1; i++)
	{
		j = A.Pivot(i);
		if ((j != -1) && (i != j))
		{
			A.SwapRow(i, j);
			b.SwapRow(i, j);
			inverseA.SwapRow(i, j);
		}
		else
		{
			// Do nothing
		}

		for (k = i + 1; k < A.GetMaxRow(); k++)
		{
			w = -(A.GetData(k, i) / A.GetData(i, i));
			A.RowAddition(k, w, i);
			b.RowAddition(k, w, i);
			inverseA.RowAddition(k, w, i);
		}
	}

}

void Gaussian_Elimination::Backward_Substitution(Matrix &A, Matrix &inverseA, Matrix &b)
{
	int i, j, n;
	long double w;

	n = b.GetMaxRow() - 1;

	for (i = n ; i >= 0; i--)
	{
		inverseA.RowMultiplation(1.0L / A.GetData(i, i), i);
		for (j = 0; j < i; j++)
		{
			inverseA.RowAddition(j, -(A.GetData(j, i)), i);
		}
	}

	b.SetData(b.GetData(n, 0) / A.GetData(n, n), n, 0);
	for (i = n - 1; i >= 0; i--)
	{
		w = b.GetData(i, 0);
		for (j = i + 1; j <= n; j++)
		{
			w -= b.GetData(j, 0) * A.GetData(i, j);
		}
		w = w / A.GetData(i, i);
		b.SetData(w, i, 0);
	}
}
