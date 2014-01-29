/*
 * RBFKernel.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "kermorpp.h"

namespace kermorpp {

RBFKernel::RBFKernel(double gamma) :
		_gamma(gamma) {
}

RBFKernel::~RBFKernel() {
}

/*
 * Implements the sum(x.^2,1) Matlab command for a n x m matrix x
 */
void RBFKernel::sumsq(Matrix x, double* res) {
	int i, j;

#pragma omp parallel for shared(res, x) private(i,j)
	for (j = 0; j < x.m; j++) {
		res[j] = 0;
		for (i = 0; i < x.n; i++) {
			res[j] += x.values[i * x.m + j] * x.values[i * x.m + j];
		}
	}
}

/**
 * Parameters:
 * x: Input data matrix one of size `d \times n`
 * y: Input data matrix one of size `d \times m`
 * d: The input data DoFs
 * n: Number of first argument data points
 * m: Number of second argument data points
 *
 * Return values:
 * Kernel vector/matrix res of size `n \times m`
 */
Matrix RBFKernel::evaluate(Matrix x, Matrix y) {

#ifdef DEBUG
	char temp[1000];
#endif

	double hlp;
	int i, j, l;

	double* xsq = new double[x.m];
	double* ysq = new double[y.m];

	sumsq(x, xsq);
	sumsq(y, ysq);

	Matrix res = Matrix(x.m, y.m);

#pragma omp parallel for shared(res,xsq,ysq,x,y) private(hlp,i,j,l)
	// Running column indices i for x, j for y
	for (i = 0; i < res.n; i++) {
		for (j = 0; j < res.m; j++) {
			hlp = 0;
			for (l = 0; l < x.n; l++) {
				hlp += x.values[l * x.m + i] * y.values[l * y.m + j];
			}
			int pos = i * res.m + j;
			res.values[pos] = rbf_eval_rsq(
					(xsq[i] + ysq[j] - 2 * hlp) / (_gamma * _gamma));
#ifdef DEBUG
			sprintf(temp, "xsq=%.12f, ysq=%.12f, x*y=%.12f\n", xsq[i], ysq[j],
					hlp);
			std::cout << temp;
			sprintf(temp, "r=%.12f, res[%d,%d]=%.12f\n",
					(xsq[i] + ysq[j] - 2 * hlp), i, j, res.values[pos]);
			std::cout << temp;
#endif
		}
	}
	return res;
}

}

