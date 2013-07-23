/*
 * Kernel.h
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include <math.h>
#include <omp.h>

namespace kermorpp {

class RBFKernel {

public:
	RBFKernel(double gamma);
	virtual ~RBFKernel();

	double* evaluate(double* x, double* y, int d, int n, int m);

protected:
	virtual double rbf_eval_rsq(double rsq) = 0;

private:
	void sumsq(double* x, int n, int m, double* res);

public:
	double _gamma;
};

}

#endif /* KERNEL_H_ */
