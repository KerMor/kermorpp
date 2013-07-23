/*
 * mexTest.c
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include <mex.h>
#include <math.h>
#include "Gaussian.h"
#include "mstream.h"
#include <streambuf>
//#include <string>
#include <iostream>  // std::cout
//#include <sstream>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

	mstream mout;
	std::streambuf *outbuf = std::cout.rdbuf(&mout);

	double *x, *y, *res, *mres;
	size_t m, n, d, i;

#ifdef DEBUG
	char temp[100];
	sprintf(temp, "nlhs=%d, nrhs=%d\n", nlhs, nrhs);
	mexPrintf(temp);
#endif

	d = mxGetM(prhs[0]);
	n = mxGetN(prhs[0]);
	x = mxGetPr(prhs[0]);

#ifdef DEBUG
	sprintf(temp, "x size: %d x %d\n", d, n);
	mexPrintf(temp);
#endif

	m = mxGetN(prhs[1]);
	y = mxGetPr(prhs[1]);

#ifdef DEBUG
	sprintf(temp, "y size: %d x %d\n", d, m);
	mexPrintf(temp);
#endif

	Gaussian* kernel = new Gaussian(1);
	res = kernel->evaluate(x, y, d, n, m);

	plhs[0] = mxCreateDoubleMatrix(m, m, mxREAL);
	mres = mxGetPr(plhs[0]);
	for (i = 0; i < n * m; i++) {
		mres[i] = res[i];
	}

	std::cout.rdbuf(outbuf);
}
