/*
 * RBFKernel.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include "kermorpp.h"
#include <iostream>

namespace kermorpp {

ostream & operator<<(ostream & os, const RBFKernel & k) {
	os << "Gamma:" << k._gamma;
	return os;
}

RBFKernel::RBFKernel(double gamma) :
		_gamma(gamma) {
}

RBFKernel::~RBFKernel() {
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
MatrixXd RBFKernel::evaluate(MatrixXd x, MatrixXd y) {

	MatrixXd xsq = MatrixXd::Ones(y.cols(), 1)
			* x.cwiseProduct(x).colwise().sum();
	MatrixXd ysq = MatrixXd::Ones(x.cols(), 1)
			* y.cwiseProduct(y).colwise().sum();

	MatrixXd tmp = (xsq.transpose() + ysq - 2 * x.transpose() * y)
			/ (_gamma * _gamma);

//#if DEBUG
//	cout << "x: " << x << ", y:" << y << ", xsq: " << xsq << ", ysq: " << ysq
//	<< ", tmp: " << tmp << endl;
//#endif

	return rbf_eval_rsq(tmp);
}

}

