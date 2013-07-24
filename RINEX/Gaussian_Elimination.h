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
