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
	if (res.rows() != res_comp.rows() || res.cols() != res_comp.cols()) {
		rcode--;
		cerr << "Desired rows: " << res.rows() << ", computed: " << res_comp.rows() << endl;
		cerr << "Desired cols: " << res.cols() << ", computed: " << res_comp.cols() << endl;
	}

	if (!res.isApprox(res_comp, 1e-8)) {
		rcode--;
		cerr << "True evaluation: " << res_comp << endl;
		cerr << "Computed evaluation: " << res << endl;
		MatrixXd diff = res_comp - res;
		diff = diff.cwiseQuotient(res);
		cerr << "Relative difference norm: " << diff.norm() << endl;
	}

	return rcode;
}

