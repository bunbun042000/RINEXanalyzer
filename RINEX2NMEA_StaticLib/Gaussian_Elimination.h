/*
 * Gaussian_Elimination.h
 *
 *  Created on: 2013/06/16
 *      Author: bun
 */

#ifndef GAUSSIAN_ELIMINATION_H_
#define GAUSSIAN_ELIMINATION_H_

#include "Matrix.h"

class Gaussian_Elimination
{
public:
	Gaussian_Elimination();
	Gaussian_Elimination(const Gaussian_Elimination &gauss);
	Gaussian_Elimination(Matrix &mA, Matrix &vb);
	virtual ~Gaussian_Elimination();

	bool IsValid()
	{
		return valid;
	};

	Matrix GetAnswer();

private:
	Matrix matA;
	Matrix vecb;

	bool valid;

	void Forward_Elimination();
	void Backward_Substitution();

};


#endif /* GAUSSIAN_ELIMINATION_H_ */
