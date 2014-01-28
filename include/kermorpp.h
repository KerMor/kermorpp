/*
 * kermorpp.h
 *
 *  Created on: 23.07.2013
 *      Author: CreaByte
 */

#ifndef KERMORPP_H_
#define KERMORPP_H_

#if defined(WIN32)
	#define DIR_SEPARATOR "\\"
#else
	#define DIR_SEPARATOR "/"
#endif

#include <math.h>
#include <omp.h>
#include <sstream>

using namespace std;

namespace kermorpp {

const int INT_BYTES = 4; // sizeof(int);
const int DOUBLE_BYTES = 8; // sizeof(double);

struct Vector {
	int n;
	double* values;
};

struct Matrix {
	int n, m;
	double* values;

public:
	Matrix() :
			n(0), m(0) {
	}
	;

	Matrix(int n, int m) :
			n(n), m(m) {
		values = new double[n * m];
	}
	;

	friend ostream & operator<<(ostream &os, Matrix &m);

	Matrix mtimes(Matrix other) {
		Matrix res = Matrix(n, other.m);
		for (int i = 0; i < res.n; i++) {
			for (int j = 0; j < res.m; j++) {
				int pos = i * res.m + j;
				//			std::cout << "pos " << pos << endl;
				res.values[pos] = 0;
				for (int k = 0; k < m; k++) {
					res.values[pos] += values[i * m + k]
							* other.values[k * other.m + j];
				}
			}
		}
		return res;
	}

	Matrix transpose() {
		Matrix res = Matrix(m, n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				res.values[j * n + i] = values[i * m + j];
			}
		}
		return res;
	}
};

class RBFKernel {

public:
	RBFKernel(double gamma);
	virtual ~RBFKernel();

	Matrix evaluate(Matrix x, Matrix y);

protected:
	virtual double rbf_eval_rsq(double rsq) = 0;

private:
	void sumsq(Matrix x, double* res);

public:
	double _gamma;
};

class KernelExpansion {
public:
	KernelExpansion();
	virtual ~KernelExpansion();
	void loadFrom(char* dir);
	Matrix evaluate(Matrix points);

private:
	Vector loadVector(const char* file);
	Matrix loadMatrix(const char* file);
	inline bool little_endian(void);
//	void combine(char *destination, const char *path1, const char *path2);

public:
	Matrix coeffs, centers;
	RBFKernel *kernel;
};

class Wendland: public RBFKernel {
public:
	Wendland(double gamma, int d, int k);
	virtual ~Wendland();
protected:
	double rbf_eval_rsq(double rsq);

private:
	int _d, _k;
};

class Gaussian: public RBFKernel {
public:
	Gaussian(double gamma);
	virtual ~Gaussian();
protected:
	double rbf_eval_rsq(double rsq);
};

}

#endif /* KERMORPP_H_ */
