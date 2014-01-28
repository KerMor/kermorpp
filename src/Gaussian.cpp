/*
 * Gaussian.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include "kermorpp.h"

namespace kermorpp {

Gaussian::Gaussian(double gamma) :
		RBFKernel(gamma) {
}

Gaussian::~Gaussian() {
}

double Gaussian::rbf_eval_rsq(double rsq) {
	// Default implementation: Gaussian (r^2 is passed)
	return exp(-rsq);
}

}

