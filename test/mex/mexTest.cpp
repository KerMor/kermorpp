/*
 * mexTest.c
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include "mex.h"
#include "matrix.h"
#include <math.h>
#include "../kermorpp.h"
#include "mstream.h"
#include <streambuf>
#include <iostream>  // std::cout
using namespace kermorpp;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

	mstream mout;
	std::streambuf *outbuf = std::cout.rdbuf(&mout);

	Matrix x = Matrix(mxGetM(prhs[0]),mxGetN(prhs[0]));
	x.values = mxGetPr(prhs[0]);

	Matrix y = Matrix(mxGetM(prhs[1]), mxGetN(prhs[1]));
	y.values = mxGetPr(prhs[1]);

	double gamma = mxGetScalar(prhs[2]);

//	Gaussian* kernel = new Gaussian(gamma);
//	Wendland* kernel = new Wendland(gamma,2,2);

	KernelExpansion* kexp = new KernelExpansion();
	kexp->loadFrom(".");

	Matrix res = kexp->evaluate(x);

	plhs[0] = mxCreateDoubleMatrix(res.n, res.m, mxREAL);
	double* mres = mxGetPr(plhs[0]);
	for (size_t i = 0; i < res.n * res.m; i++) {
		mres[i] = res.values[i];
	}

	std::cout.rdbuf(outbuf);
}

//#ifdef DEBUG
//	sprintf(temp, "y size: %d x %d\n", d, m);
//	mexPrintf(temp);
//#endif
