/*
 * kermorpp.h
 *
 *  Created on: 23.07.2013
 *      Author: CreaByte
 */

#ifndef KERMORPP_H_
#define KERMORPP_H_

#include <math.h>
#include <omp.h>

namespace kermorpp {

const int INT_BYTES = 4; // sizeof(int);
const int DOUBLE_BYTES = 8; // sizeof(double);

struct Vector {
	int n;
	double* values;
};

struct Matrix {
	int n,m;
	double* values;
};

class RBFKernel {

public:
	RBFKernel(double gamma);
	virtual ~RBFKernel();

	double* evaluate(double* x, double* y, int d, int n, int m);

protected:
	virtual double rbf_eval_rsq(double rsq) = 0;

private:
	void sumsq(double* x, int n, int m, double* res);

public:
	double _gamma;
};

class KernelExpansion {
public:
	KernelExpansion();
	virtual ~KernelExpansion();
	void loadFrom(const char* dir);
	double* evaluate(double *x);

private:
	Vector loadVector(const char* file);
	Matrix loadMatrix(const char* file);
	inline bool little_endian(void);

public:
	double *coeffs, *centers;
	RBFKernel *kernel;
};

class Wendland: public RBFKernel {
public:
	Wendland(double gamma, int d, int k);
	virtual ~Wendland();
protected:
	double Wendland::rbf_eval_rsq(double rsq);

private:
	int _d, _k;
};

class Gaussian: public RBFKernel {
public:
	Gaussian(double gamma);
	virtual ~Gaussian();
protected:
	double Gaussian::rbf_eval_rsq(double rsq);
};

}

#endif /* KERMORPP_H_ */
