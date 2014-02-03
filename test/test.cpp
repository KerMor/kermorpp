/*
 * test.cpp
 *
 *  Created on: 23.07.2013
 *      Author: CreaByte
 */
#include <iostream>
#include <stdio.h>
#include <cstddef> // size_t is a typedef on an unsigned int
#include "kermorpp.h"

using namespace kermorpp;
using namespace std;
using namespace Eigen;

int main(int argc, char **argv) {
	KernelExpansion *k = new KernelExpansion;

	string path = string(".");
	if (argc == 2) {
		path = string(argv[1]);
	}

#if DEBUG
	cout << "loading expansion from " << path << endl;
#endif

	k->loadFrom(path);

	cout << "loaded coeffs " << k->coeffs.rows() << " x " << k->coeffs.cols()
			<< " with centers " << k->centers.rows() << " x "
			<< k->centers.cols() << endl;

	MatrixXd x(3, 2);
	x << 1.0, 1.0, .5, 1.5, 2.5, .5;

#if DEBUG
	cout << "done create arg: " << x << endl;
#endif

	MatrixXd res = k->evaluate(x);

#if DEBUG
	cout << "done eval: " << res << endl;
#endif

	k->kernel = new Gaussian(1);
	res = k->evaluate(x);

	MatrixXd ma(2, 2);
	ma << 1, 2, 3, 4;
	k->coeffs = ma;

	MatrixXd c(2, 2);
	c << 1, 2, 3, 4;
	k->centers = ma;

	MatrixXd p(2, 1);
	p << 1, 2;

#if DEBUG
	cout << "res:" << k->evaluate(p);
#endif

	return 0;
}

