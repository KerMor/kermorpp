#include "kermorpp.h"
#include <iostream>

using namespace kermorpp;
using namespace std;
using namespace Eigen;

int main(int argc, char **argv) {

	string path = string(".");
	if (argc == 2) {
		path = string(argv[1]);
	}

	KernelExpansion* k = KernelExpansion::loadFrom(path);

	cout << "loaded " << *k << endl;

	MatrixXd points = Util::loadMatrix(path + DIR_SEPARATOR + "points.bin");

	MatrixXd res = k->evaluate(points);
	MatrixXd res_comp = Util::loadMatrix(path + DIR_SEPARATOR + "eval.bin");

	int rcode = 0;
	if (res.rows() != res_comp.rows() || res.cols() != res_comp.cols())
		rcode--;
	if (!res.isApprox(res_comp))
		rcode--;

	return rcode;
}

