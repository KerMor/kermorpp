/*
 * Gaussian.h
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#ifndef GAUSSIAN_H_
#define GAUSSIAN_H_

#include "RBFKernel.h"

class Gaussian : public RBFKernel {
public:
	Gaussian(double gamma);
	virtual ~Gaussian();
};

#endif /* GAUSSIAN_H_ */
