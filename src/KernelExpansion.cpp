/*
 * KernelExpansion.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include "kermorpp.h"
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace Eigen;

namespace kermorpp {

ostream & operator<<(ostream & s, const KernelExpansion &k) {

	s << "KernelExpansion centers: " << k.centers.rows() << " x " << k.centers.cols();
	s << ", " << "coeffs: " << k.coeffs.rows() << " x " << k.coeffs.cols();
	s << ", kernel: " << typeid(k.kernel).name() << ": " << *k.kernel;
	return s;

}

KernelExpansion::KernelExpansion() :
		coeffs(MatrixXd(0, 0)), centers(MatrixXd(0, 0)), kernel(0) {
}

KernelExpansion::~KernelExpansion() {
	kernel->~RBFKernel();
	free(kernel);
}

MatrixXd KernelExpansion::evaluate(MatrixXd points) {
	if (centers.rows() != points.rows()) {
		cerr << "Argument dimension mismatch. Center dimension:"
				<< centers.rows() << " vs argument dimension: " << points.rows()
				<< endl;
		exit(-1);
	}

#if DEBUG
	cout << "evaluating kexp.. " << endl << "centers:  " << centers << endl
	<< "points: " << points << endl;
#endif

	MatrixXd kvec = kernel->evaluate(centers, points);

#if DEBUG
	cout << "done eval kexp. kernel vector: " << kvec << ", coeffs: " << coeffs << endl;
#endif

	return coeffs * kvec;
}

KernelExpansion* KernelExpansion::loadFrom(string dir) {

	KernelExpansion* res = new KernelExpansion();
	string file = dir + DIR_SEPARATOR + "kernel.bin";
	VectorXd kdata = Util::loadVector(file);
	switch ((int) kdata(0)) {
	case 1:
		res->kernel = new Gaussian(kdata(1));
		break;
	case 2:
		res->kernel = new Wendland(kdata(1), kdata(2), kdata(3));
		break;
	default:
		cerr << "Unknown kernel data: " << kdata << endl;
		break;
	}

	res->centers = Util::loadMatrix(dir + DIR_SEPARATOR + "centers.bin");

#if DEBUG
	cout << "done loading centers: " << res.centers << endl;
#endif

	res->coeffs = Util::loadMatrix(file = dir + DIR_SEPARATOR + "coeffs.bin");

#if DEBUG
	cout << "done loading coeffs: " << res.coeffs << endl;
#endif

	return res;
}

}

