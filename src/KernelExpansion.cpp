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
//#include <ios>

using namespace std;

namespace kermorpp {

ostream & operator<<(ostream & os, Matrix &m) {
	os << m.n << " x " << m.m << " matrix [";
	for (int i = 0; i < m.n * m.m; i++) {
		os << m.values[i] << ", ";
	}
	os << "]";
	return os;
}

KernelExpansion::KernelExpansion() :
		centers(Matrix(0, 0)), coeffs(Matrix(0, 0)), kernel(0) {
}

KernelExpansion::~KernelExpansion() {

}

Matrix KernelExpansion::evaluate(Matrix points) {
	if (centers.n != points.n) {
		cerr << "Argument dimension mismatch. Center dimension:" << centers.n
				<< " vs points dimension: " << points.n << endl;
		exit(-1);
	}
	cout << "evaluating kexp.. " << endl << "centers:  " << centers << endl
			<< "points: " << points << endl;

	Matrix kvec = kernel->evaluate(centers, points);

	cout << "done eval kexp. kernel vector: " << kvec << endl;

	return coeffs.mtimes(kvec); //.transpose()
}

void KernelExpansion::loadFrom(char* dir) {

	char* file = strcat(dir,strcat(DIR_SEPARATOR,"kernel.bin"));
	Vector kdata = loadVector(file);
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

	file = strcat(dir,strcat(DIR_SEPARATOR,"centers.bin"));
	centers = loadMatrix(file);
	cout << "done loading centers: " << centers << endl;

	file = strcat(dir,strcat(DIR_SEPARATOR,"coeffs.bin"));
	coeffs = loadMatrix(file);
	cout << "done loading coeffs: " << coeffs << endl;
}

Vector KernelExpansion::loadVector(const char* file) {

	cout << "Loading vector from file " << file << endl;

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
//			cout << "vec[" << l << "] nach read:" << res.values[l] << endl;
		}
	}
	fs.close();

	return res;
}

Matrix KernelExpansion::loadMatrix(const char* file) {

	ifstream fs;
	fs.open(file, ios::in | ios::binary);
	if (!fs) {
		cerr << "Not able to read file " << file << endl;
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

		Matrix res = Matrix(n, m);
		cout << "Reading " << res.n << " x " << res.m << " matrix" << endl;
		for (int l = 0; l < res.n * res.m; l++) {
			//fs.read(reinterpret_cast<char*>(&res.values[l]), DOUBLE_BYTES);
			fs.read(buf, DOUBLE_BYTES);
			if (le)
				reverse(buf, buf + DOUBLE_BYTES);
			copy(buf, buf + DOUBLE_BYTES,
					reinterpret_cast<char*>(&res.values[l]));
//			cout << "mat[" << l << "] nach read:" << res.values[l] << endl;
		}
		return res;
	}
	fs.close();
	return Matrix();
}

inline bool KernelExpansion::little_endian(void) {
	typedef unsigned char* pbyte;
	static unsigned long word = 0x1;
	static bool is_little_endian_machine = (*pbyte(&word) == 0x1);
	return is_little_endian_machine;
}

//void combine(char *destination, const char *path1, const char *path2) {
//	if (path1 && *path1) {
//		auto len = strlen(path1);
//		strcpy(destination, path1);
//
//
//		if (destination[len - 1] == DIR_SEPARATOR) {
//			if (path2 && *path2) {
//				strcpy(destination + len,
//						(*path2 == DIR_SEPARATOR) ? (path2 + 1) : path2);
//			}
//		} else {
//			if (path2 && *path2) {
//				if (*path2 == DIR_SEPARATOR)
//					strcpy(destination + len, path2);
//				else {
//					destination[len] = DIR_SEPARATOR;
//					strcpy(destination + len + 1, path2);
//				}
//			}
//		}
//	} else if (path2 && *path2)
//		strcpy(destination, path2);
//	else
//		destination[0] = '\0';
//}

}

