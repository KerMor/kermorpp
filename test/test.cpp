/*
 * test.cpp
 *
 *  Created on: 23.07.2013
 *      Author: CreaByte
 */
#include <iostream>
#include <stdio.h>
#include <cstddef> // size_t is a typedef on an unsigned int
#include "../kermorpp.h"

using namespace kermorpp;
using namespace std;

int main() {
//     std::cout << "Number: " ;
//     std::size_t Number ;
//     std::cin >> Number ;
//     if ( Number > 10 )
//          std::cerr << "Hey!! Out of Range!" << std::endl ;
//     elses
//          std::cout << "It's: \"" << MyStringDigits[Number-1] << "\"" << std::endl ;

	KernelExpansion *k = new KernelExpansion;

//	cout << "done create" << endl;

	k->loadFrom(".");

//	cout << "done load" << endl;

	Matrix x;
	x.n = 3;
	x.m = 2;
	double xv[6] = {1.0, 1.0, .5, 1.5, 2.5, .5};
	x.values = xv;

	cout << "done create arg: " << x << endl;

	Matrix res = k->evaluate(x);

	cout << "done eval: " << res << endl;

//	double x[4] = { 1.0, 1.0, .5, 1.5 };
//	double y[6] = { 1.0, 1.0, .5, 1.5, 2.5, .5 };
//
//	Gaussian *g = new Gaussian(1);
//	double *res = g->evaluate(x, y, 2, 2, 3);

	return 0;
}

