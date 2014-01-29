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

	Matrix x;
	x.n = 3;
	x.m = 2;
	double xv[6] = {1.0, 1.0, .5, 1.5, 2.5, .5};
	x.values = xv;

#if DEBUG
	cout << "done create arg: " << x << endl;
#endif

	Matrix res = k->evaluate(x);

#if DEBUG
	cout << "done eval: " << res << endl;
#endif

	k->kernel = new Gaussian(1);
	res = k->evaluate(x);

	return 0;
}

