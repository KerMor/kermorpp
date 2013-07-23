/*
 * Gaussian.h
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#ifndef GAUSSIAN_H_
#define GAUSSIAN_H_

#include "RBFKernel.h"

namespace kermorpp {

class Gaussian: public RBFKernel {
public:
	Gaussian(double gamma);
	virtual ~Gaussian();
protected:
	double Gaussian::rbf_eval_rsq(double rsq);
};

}

#endif /* GAUSSIAN_H_ */
