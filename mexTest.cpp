/*
 * mexTest.c
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include <mex.h>
#include <math.h>
#include "kermorpp.h"
#include "mstream.h"
#include <streambuf>
#include <iostream>  // std::cout
using namespace kermorpp;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

	mstream mout;
	std::streambuf *outbuf = std::cout.rdbuf(&mout);

	double *x, *y, *res, *mres;
	size_t m, n, d, i;

	d = mxGetM(prhs[0]);
	n = mxGetN(prhs[0]);
	x = mxGetPr(prhs[0]);

	m = mxGetN(prhs[1]);
	y = mxGetPr(prhs[1]);

	double gamma = mxGetScalar(prhs[2]);

//	Gaussian* kernel = new Gaussian(gamma);
	Wendland* kernel = new Wendland(gamma,2,2);
	res = kernel->evaluate(x, y, d, n, m);

	plhs[0] = mxCreateDoubleMatrix(n, m, mxREAL);
	mres = mxGetPr(plhs[0]);
	for (i = 0; i < n * m; i++) {
		mres[i] = res[i];
	}

	std::cout.rdbuf(outbuf);
}

//#ifdef DEBUG
//	sprintf(temp, "y size: %d x %d\n", d, m);
//	mexPrintf(temp);
//#endif
