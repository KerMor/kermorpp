/*
 * kermorpp.h
 *
 *  Created on: 23.07.2013
 *      Author: CreaByte
 */

#ifndef KERMORPP_H_
#define KERMORPP_H_

#define DEBUG true

#if defined(WIN32)
#define DIR_SEPARATOR "\\"
#else
#define DIR_SEPARATOR "/"
#endif

#include <sstream>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

namespace kermorpp {

const int INT_BYTES = 4; // sizeof(int);
const int DOUBLE_BYTES = 8; // sizeof(double);

class RBFKernel {

public:
	RBFKernel(double gamma);
	virtual ~RBFKernel();

	MatrixXd evaluate(MatrixXd x, MatrixXd y);

protected:
	virtual MatrixXd rbf_eval_rsq(MatrixXd rsq) = 0;

public:
	double _gamma;
};

class KernelExpansion {
public:
	KernelExpansion();
	virtual ~KernelExpansion();
	void loadFrom(string dir);
	MatrixXd evaluate(MatrixXd points);

private:
	VectorXd loadVector(const char* file);
	MatrixXd loadMatrix(const char* file);
	inline bool little_endian(void);
//	void combine(char *destination, const char *path1, const char *path2);

public:
	MatrixXd coeffs, centers;
	RBFKernel *kernel;
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
