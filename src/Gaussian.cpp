/*
 * Gaussian.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include "kermorpp.h"

using namespace Eigen;

namespace kermorpp {

Gaussian::Gaussian(double gamma) :
		RBFKernel(gamma) {
}

Gaussian::~Gaussian() {
}

MatrixXd Gaussian::rbf_eval_rsq(MatrixXd rsq) {
	// Default implementation: Gaussian (r^2 is passed)
	return (-rsq).unaryExpr(internal::scalar_exp_op<double>());
}

}

