/*
 * Wendland.h
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#ifndef WENDLAND_H_
#define WENDLAND_H_

#include "RBFKernel.h"

//namespace kernelpp {

class Wendland  { //public RBFKernel
public:
	Wendland();
//	Wendland(double gamma);
	virtual ~Wendland();
};

//}

#endif /* WENDLAND_H_ */
