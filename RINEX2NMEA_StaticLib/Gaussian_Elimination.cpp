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
	valid = false;
}

Gaussian_Elimination::Gaussian_Elimination(const Gaussian_Elimination &gauss)
{
	matA = gauss.matA;
	vecb = gauss.vecb;

	valid = gauss.valid;

}

Gaussian_Elimination::Gaussian_Elimination(Matrix &mA, Matrix &vb)
{

	if (mA.GetMaxRow() != vb.GetMaxRow())
	{
		valid = false;
	}
	else
	{
		matA = mA;
		vecb = vb;
		valid = true;
	}

}

Gaussian_Elimination::~Gaussian_Elimination()
{
	valid = false;
}

Matrix Gaussian_Elimination::GetAnswer()
{

	Forward_Elimination();
	Backward_Substitution();

	return vecb;

}

void Gaussian_Elimination::Forward_Elimination()
{

	int i, j, k;
	long double w;


	for (i = 0; i < matA.GetMaxRow() - 1; i++)
	{
		j = matA.Pivot(i);
		if ((j != -1) && (i != j))
		{
			matA.SwapRow(i, j);
			vecb.SwapRow(i, j);
		}
		else
		{
			// Do nothing
		}

		for (k = i + 1; k < matA.GetMaxRow(); k++)
		{
			w = -(matA.GetData(k, i) / matA.GetData(i, i));
			matA.RowAddition(k, w, i);
			vecb.RowAddition(k, w, i);
		}
	}

}

void Gaussian_Elimination::Backward_Substitution()
{
	int i, j, n;
	long double w;

	n = vecb.GetMaxRow() - 1;
	vecb.SetData(vecb.GetData(n, 0) / matA.GetData(n, n), n, 0);
	for (i = n - 1; i >= 0; i--)
	{
		w = vecb.GetData(i, 0);
		for (j = i + 1; j <= n; j++)
		{
			w -= vecb.GetData(j, 0) * matA.GetData(i, j);
		}
		w = w / matA.GetData(i, i);
		vecb.SetData(w, i, 0);
	}
}
