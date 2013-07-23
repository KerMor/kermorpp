/*
 * RBFKernel.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include <cstdlib>
#include <stdio.h>
#include "RBFKernel.h"

RBFKernel::RBFKernel(double gamma) :
		_gamma(gamma) {
}

RBFKernel::~RBFKernel() {
}

inline double RBFKernel::rbf_eval_rsq(double rsq) {
	// Default implementation: Gaussian (r^2 is passed)
	return exp(-rsq);
}

/*
 * Implements the sum(x.^2,1) Matlab command for a n x m matrix x
 */
void RBFKernel::sumsq(double* x, int n, int m, double* res) {
	int i, j, *v, vfirst;

#pragma omp parallel for shared(xsq,x,n,m) private(i,j)
	for (j = 0; j < m; j++) {
		res[j] = 0;
		for (i = 0; i < n; i++) {
			res[j] += x[j * n + i] * x[j * n + i];
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
double* RBFKernel::evaluate(double* x, double* y, int d, int n, int m) {

	double hlp;
	int i, j, l;

	double* xsq = new double[n];
	double* ysq = new double[m];

	sumsq(x, d, n, xsq);
	sumsq(y, d, m, ysq);

	double* res = new double[n * m];

//#pragma omp parallel for shared(res,xsq,ysq,x,y,n,m,k) private(hlp,i,j,l)
	// Running column indices i for x, j for y
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			hlp = 0;
			for (l = 0; l < d; l++) {
				hlp += x[i * d + l] * y[j * d + l];
#ifdef DEBUG
				fprintf(stdout, "ScaP i=%d, j=%d, l=%d, x=%.12f, y=%.12f\n", i, j, l, x[i*n+l], y[j*n+l]);
#endif
			}
			res[i * m + j] = rbf_eval_rsq(
					(xsq[i] + ysq[j] - 2 * hlp) / (_gamma * _gamma));
#ifdef DEBUG
			fprintf(stdout, "xsq=%.12f, ysq=%.12f, x*y=%.12f\n", xsq[i], ysq[j], hlp);
#endif
		}
	}
	return res;
}

