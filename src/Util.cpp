/*
 * KernelExpansion.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include "kermorpp.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace Eigen;

namespace kermorpp {

VectorXd Util::loadVector(string file) {

#if DEBUG
	cout << "Loading vector from file " << file << endl;
#endif

	ifstream fs;
	fs.open(file.c_str(), ios::in | ios::binary);
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

MatrixXd Util::loadMatrix(string file) {

	ifstream fs;
	fs.open(file.c_str(), ios::in | ios::binary);
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

inline bool Util::little_endian(void) {
	typedef unsigned char* pbyte;
	static unsigned long word = 0x1;
	static bool is_little_endian_machine = (*pbyte(&word) == 0x1);
	return is_little_endian_machine;
}

}

