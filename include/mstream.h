/*
 * mstream.h
 *
 *  Created on: 22.07.2013
 *      Author: CreaByte
 */

#ifndef MSTREAM_H_
#define MSTREAM_H_

#include <streambuf>
#include <ios>
#include <stdio.h>

class mstream: public std::streambuf {
public:
protected:
	virtual std::streamsize xsputn(const char *s, std::streamsize n);
	virtual int overflow(int c = EOF);
};

#endif /* MSTREAM_H_ */

