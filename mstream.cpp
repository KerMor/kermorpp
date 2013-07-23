/*
 * mstream.cpp
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#include "mstream.h"
#include <mex.h>

std::streamsize mstream::xsputn(const char *s, std::streamsize n) {
	mexPrintf("%.*s", n, s);
	return n;
}

int mstream::overflow(int c) {
	if (c != EOF) {
		mexPrintf("%.1s", &c);
	}
	return 1;
}

