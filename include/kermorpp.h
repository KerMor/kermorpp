/*
 * kermorpp.h
 *
 *  Created on: 23.07.2013
 *      Author: CreaByte
 */

#ifndef KERMORPP_H_
#define KERMORPP_H_

//#define DEBUG true

#if defined(WIN32)
#define DIR_SEPARATOR "\\"
#else
#define DIR_SEPARATOR "/"
#endif

#include <Eigen/Core>

using namespace std;
using namespace Eigen;

namespace kermorpp {

const int INT_BYTES = sizeof(int); // 4
const int DOUBLE_BYTES = sizeof(double); // 8

class RBFKernel {

public:
	RBFKernel(double gamma);
	virtual ~RBFKernel();

	MatrixXd evaluate(MatrixXd x, MatrixXd y);
	friend ostream & operator<<(ostream & os, const RBFKernel & k);

protected:
	virtual MatrixXd rbf_eval_rsq(MatrixXd rsq) = 0;

public:
	double _gamma;
};

class Util {
public:
	static VectorXd loadVector(string file);
	static MatrixXd loadMatrix(string file);
private:
	static inline bool little_endian(void);
};

class KernelExpansion {
public:
	KernelExpansion();
	virtual ~KernelExpansion();
	static KernelExpansion* loadFrom(string dir);
	MatrixXd evaluate(MatrixXd points);
	friend ostream & operator<<(ostream & os, const KernelExpansion & k);

public:
	MatrixXd coeffs;
	MatrixXd centers;
	RBFKernel* kernel;
};

class Wendland: public RBFKernel {
public:
	Wendland(double gamma, int d, int k);
	virtual ~Wendland();
protected:
	MatrixXd rbf_eval_rsq(MatrixXd rsq);

private:
	int _d, _k;
};

class Gaussian: public RBFKernel {
public:
	Gaussian(double gamma);
	virtual ~Gaussian();
protected:
	MatrixXd rbf_eval_rsq(MatrixXd rsq);
};

}

#endif /* KERMORPP_H_ */
