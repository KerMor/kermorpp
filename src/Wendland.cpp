/*
 * Wendland.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include "kermorpp.h"
#include <iostream>

namespace kermorpp {

Wendland::Wendland(double gamma, int d, int k) :
		RBFKernel(gamma), _d(d), _k(k) {
}

Wendland::~Wendland() {
}

MatrixXd Wendland::rbf_eval_rsq(MatrixXd rsq) {
	// Default implementation: Gaussian (r^2 is passed)


	MatrixXd r = rsq.cwiseSqrt();
	MatrixXd one = MatrixXd::Ones(r.rows(),r.cols());
	int l = floor(_d / 2.0) + _k + 1;
	MatrixXd p;

	//cout << "rsq: " << rsq << ", r: " << r << ", l: " << l << endl;
	// +1 is done at end
	switch (_k) {
	case 1:
		p = (l + 1) * r + one;
		break;
	case 2:
		p = (l * l + 4 * l + 3) * rsq / 3 + (l + 2) * r + one;
		break;
	case 3:
		p = ((l * l * l + 9 * l * l + 23 * l + 15) * rsq.cwiseProduct(r)
				+ (6 * l * l + 36 * l + 45) * rsq) / 15 + (l + 3) * r + one;
		break;
	default:
		p = MatrixXd::Zero(rsq.rows(), rsq.cols());
		return p;
	}

	MatrixXd arg = (one-r).cwiseMax(0);

	//cout << "p: " << p << ", arg: " << arg << endl;

	return arg.unaryExpr(internal::scalar_pow_op<double>(l + _k)).cwiseProduct(p);
	//return std::max(0.0, pow((1 - r), l + _k)) * p;
}
}
