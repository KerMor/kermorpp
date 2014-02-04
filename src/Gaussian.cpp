/*
 * Gaussian.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include "kermorpp.h"
#include <iostream>

using namespace Eigen;

namespace kermorpp {

Gaussian::Gaussian(double gamma) :
		RBFKernel(gamma) {
}

Gaussian::~Gaussian() {
}

MatrixXd Gaussian::rbf_eval_rsq(MatrixXd rsq) {
	return (-rsq).unaryExpr(internal::scalar_exp_op<double>());
}

}

