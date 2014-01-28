/*
 * Wendland.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include "kermorpp.h"
#include <math.h>
//#include <xutility>

namespace kermorpp {

Wendland::Wendland(double gamma, int d, int k) :
		RBFKernel(gamma), _d(d), _k(k) {
}

Wendland::~Wendland() {
}

double Wendland::rbf_eval_rsq(double r) {
	// Default implementation: Gaussian (r^2 is passed)

	r = sqrt(r);
	int l = floor(_d / 2.0) + _k + 1;
	double p;

	switch (_k) {
	case 1:
		p = (l + 1) * r + 1;
		break;
	case 2:
		p = (l * l + 4 * l + 3) * r * r / 3 + (l + 2) * r + 1;
		break;
	case 3:
		p = ((l * l * l + 9 * l * l + 23 * l + 15) * r * r * r
				+ (6 * l * l + 36 * l + 45) * r * r) / 15 + (l + 3) * r + 1;
		break;
	default:
		p = 0;
		break;
	}
	return std::max(0.0, pow((1 - r), l + _k)) * p;
}
}
