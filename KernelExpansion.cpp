/*
 * KernelExpansion.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include "kermorpp.h"
#include <iostream>
//#include <stdio.h>
#include <fstream>
//#include <cstdlib>
//#include <ios>

using namespace std;

namespace kermorpp {

KernelExpansion::KernelExpansion() {
}

KernelExpansion::~KernelExpansion() {

}

Matrix KernelExpansion::evaluate(Matrix points) {
	if (centers.n != points.n) {
		cerr << "Argument dimension mismatch. Center dimension:" << centers.n
				<< " vs points dimension: " << points.n << endl;
		exit(-1);
	}
	Matrix other = kernel->evaluate(centers, points);
	cout << "done eval kexp " << endl;

	Matrix res;
	res.n = coeffs.n;
	res.m = other.m;
	std::cout << "matrix size " << res.n << " x " << res.m << endl;
	for (int i = 0; i < res.n; i++) {
		for (int j = 0; j < res.m; i++) {
			int pos = i * res.m + j;
			std::cout << "pos " << pos << endl;
			res.values[pos] = 0;
			for (int k = 0; k < coeffs.m; k++) {
				res.values[pos] += coeffs.values[i * coeffs.m + k]
						* other.values[k * i + j];
			}
		}
	}

	return res;
//	return coeffs.mtimes(kvec);
}

void KernelExpansion::loadFrom(const char* dir) {

	Vector kdata = loadVector("kernel.bin");
	switch ((int) kdata.values[0]) {
	case 1:
		kernel = new Gaussian(kdata.values[1]);
		break;
	case 2:
		kernel = new Wendland(kdata.values[1], kdata.values[2],
				kdata.values[3]);
		break;
	default:
		cerr << "Unknown kernel type: " << kdata.values[0] << endl;
		break;
	}
	cout << "done loading kernel" << endl;

	centers = loadMatrix("centers.bin");
	cout << "done loading centers" << endl;
	coeffs = loadMatrix("coeffs.bin");
	cout << "done loading coeffs" << endl;
}

Vector KernelExpansion::loadVector(const char* file) {
	Vector res;

	ifstream fs;
	fs.open(file, ios::in | ios::binary);
	if (!fs) {
		cerr << "Not able to read file " << file << endl;
	} else {
		char buf[DOUBLE_BYTES];
		bool le = little_endian();
		fs.seekg(0, ios::beg);

		// Faster would be: fs.read(reinterpret_cast<char*>(&res.n), INT_BYTES);
		// But have to take care of endianness
		fs.read(buf, INT_BYTES);
		if (le)
			reverse(buf, buf + INT_BYTES);
		copy(buf, buf + INT_BYTES, reinterpret_cast<char*>(&res.n));
		cout << "n nach read:" << res.n << endl;

		res.values = new double[res.n];
		for (int l = 0; l < res.n; l++) {
			//fs.read(reinterpret_cast<char*>(&res.values[l]), DOUBLE_BYTES);
			fs.read(buf, DOUBLE_BYTES);
			if (le)
				reverse(buf, buf + DOUBLE_BYTES);
			copy(buf, buf + DOUBLE_BYTES,
					reinterpret_cast<char*>(&res.values[l]));
			cout << "vec[" << l << "] nach read:" << res.values[l] << endl;
		}
	}
	fs.close();

	return res;
}

Matrix KernelExpansion::loadMatrix(const char* file) {
	Matrix res;

	ifstream fs;
	fs.open(file, ios::in | ios::binary);
	if (!fs) {
		cerr << "Not able to read file " << file << endl;
	} else {
		char buf[DOUBLE_BYTES];
		bool le = little_endian();
		fs.seekg(0, ios::beg);

		// Faster would be: fs.read(reinterpret_cast<char*>(&res.n), INT_BYTES);
		// But have to take care of endianness
		fs.read(buf, INT_BYTES);
		if (le)
			reverse(buf, buf + INT_BYTES);
		copy(buf, buf + INT_BYTES, reinterpret_cast<char*>(&res.n));

		fs.read(buf, INT_BYTES);
		if (le)
			reverse(buf, buf + INT_BYTES);
		copy(buf, buf + INT_BYTES, reinterpret_cast<char*>(&res.m));
		cout << "Reading " << res.n << " x " << res.m << " matrix" << endl;

		res.values = new double[res.n * res.m];
		for (int l = 0; l < res.n * res.m; l++) {
			//fs.read(reinterpret_cast<char*>(&res.values[l]), DOUBLE_BYTES);
			fs.read(buf, DOUBLE_BYTES);
			if (le)
				reverse(buf, buf + DOUBLE_BYTES);
			copy(buf, buf + DOUBLE_BYTES,
					reinterpret_cast<char*>(&res.values[l]));
			cout << "mat[" << l << "] nach read:" << res.values[l] << endl;
		}
	}
	fs.close();

	return res;
}

inline bool KernelExpansion::little_endian(void) {
	typedef unsigned char* pbyte;
	static unsigned long word = 0x1;
	static bool is_little_endian_machine = (*pbyte(&word) == 0x1);
	return is_little_endian_machine;
}

}

