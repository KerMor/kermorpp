/*
 * Wendland.h
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#ifndef WENDLAND_H_
#define WENDLAND_H_

#include "RBFKernel.h"

namespace kermorpp {

class Wendland: public RBFKernel {
public:
	Wendland(double gamma, int d, int k);
	virtual ~Wendland();
protected:
	double Wendland::rbf_eval_rsq(double rsq);

private:
	int _d, _k;
};

}

#endif /* WENDLAND_H_ */
