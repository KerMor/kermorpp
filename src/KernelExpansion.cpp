/*
 * KernelExpansion.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include "kermorpp.h"
#include <iostream>
#include <fstream>

#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

namespace kermorpp {

KernelExpansion::KernelExpansion() :
		centers(MatrixXd(0, 0)), coeffs(MatrixXd(0, 0)), kernel(0) {
}

KernelExpansion::~KernelExpansion() {
	free(&centers);
	free(&coeffs);
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

void KernelExpansion::loadFrom(string dir) {

	string file = dir + DIR_SEPARATOR + "kernel.bin";
	VectorXd kdata = loadVector(file.c_str());
	switch ((int) kdata(0)) {
	case 1:
		kernel = new Gaussian(kdata(1));
		break;
	case 2:
		kernel = new Wendland(kdata(1), kdata(2), kdata(3));
		break;
	default:
		cerr << "Unknown kernel data: " << kdata << endl;
		break;
	}

	file = dir + DIR_SEPARATOR + "centers.bin";
	centers = loadMatrix(file.c_str());

#if DEBUG
	cout << "done loading centers: " << centers << endl;
#endif

	file = dir + DIR_SEPARATOR + "coeffs.bin";
	coeffs = loadMatrix(file.c_str());

#if DEBUG
	cout << "done loading coeffs: " << coeffs << endl;
#endif
}

VectorXd KernelExpansion::loadVector(const char* file) {

#if DEBUG
	cout << "Loading vector from file " << file << endl;
#endif

	ifstream fs;
	fs.open(file, ios::in | ios::binary);
	if (!fs) {
		cerr << "Not able to read file " << file << endl;
		fs.close();
		exit(-1);
	} else {
		char buf[DOUBLE_BYTES];
		bool le = little_endian();
		fs.seekg(0, ios::beg);

		// Faster would be: fs.read(reinterpret_cast<char*>(&res.n), INT_BYTES);
		// But have to take care of endianness
		fs.read(buf, INT_BYTES);
		if (le)
			reverse(buf, buf + INT_BYTES);
		int n;
		copy(buf, buf + INT_BYTES, reinterpret_cast<char*>(&n));

		VectorXd res(n);
		for (int l = 0; l < res.rows(); l++) {
			fs.read(buf, DOUBLE_BYTES);
			if (le)
				reverse(buf, buf + DOUBLE_BYTES);
			double tmp;
			copy(buf, buf + DOUBLE_BYTES, reinterpret_cast<char*>(&tmp));
			res(l) = tmp;
		}
		fs.close();
		return res;
	}
}

MatrixXd KernelExpansion::loadMatrix(const char* file) {

	ifstream fs;
	fs.open(file, ios::in | ios::binary);
	if (!fs) {
		cerr << "Not able to read file " << file << endl;
		fs.close();
		exit(-1);
	} else {
		char buf[DOUBLE_BYTES];
		bool le = little_endian();
		fs.seekg(0, ios::beg);

		int n, m;
		// Faster would be: fs.read(reinterpret_cast<char*>(&res.n), INT_BYTES);
		// But have to take care of endianness
		fs.read(buf, INT_BYTES);
		if (le)
			reverse(buf, buf + INT_BYTES);
		copy(buf, buf + INT_BYTES, reinterpret_cast<char*>(&n));

		fs.read(buf, INT_BYTES);
		if (le)
			reverse(buf, buf + INT_BYTES);
		copy(buf, buf + INT_BYTES, reinterpret_cast<char*>(&m));

		MatrixXd res(n, m);

#if DEBUG
		cout << "Reading " << res.rows() << " x " << res.cols() << " matrix" << endl;
#endif

		for (int i = 0; i < res.rows(); i++) {
			for (int j = 0; j < res.cols(); j++) {
				//fs.read(reinterpret_cast<char*>(&res.values[l]), DOUBLE_BYTES);
				fs.read(buf, DOUBLE_BYTES);
				if (le)
					reverse(buf, buf + DOUBLE_BYTES);
				double tmp;
				copy(buf, buf + DOUBLE_BYTES, reinterpret_cast<char*>(&tmp));
				res(i, j) = tmp;
			}
		}
		fs.close();
		return res;
	}

}

inline bool KernelExpansion::little_endian(void) {
	typedef unsigned char* pbyte;
	static unsigned long word = 0x1;
	static bool is_little_endian_machine = (*pbyte(&word) == 0x1);
	return is_little_endian_machine;
}

}

