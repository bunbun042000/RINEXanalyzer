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
	virtual ~Gaussian_Elimination();

	Matrix GetAnswer(Matrix &mA, Matrix &vb);

private:

	void Forward_Elimination(Matrix &A, Matrix &inverseA, Matrix &b);
	void Backward_Substitution(Matrix &A, Matrix &inverseA, Matrix &b);

};


#endif /* GAUSSIAN_ELIMINATION_H_ */
