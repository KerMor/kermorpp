#include "kermorpp.h"

using namespace kermorpp;
using namespace std;
using namespace Eigen;

int main() {
	KernelExpansion* k = new KernelExpansion();

	int out = rand() % 200;
	int cdim = rand() % 200;
	int nc = rand() % 200;
	int np = rand() % 200;

	k->coeffs = MatrixXd::Random(out, nc);
	k->centers = MatrixXd::Random(cdim, nc);;
	MatrixXd p = MatrixXd::Random(cdim, np);

	int rcode = 0;
	k->kernel = new Gaussian(1);
	MatrixXd res = k->evaluate(p);

	if (res.rows() != out) rcode--;

	k->kernel = new Wendland(10,1,1);
	res = k->evaluate(p);

	if (res.rows() != out) rcode--;

	k->kernel = new Wendland(12,2,1);
	res = k->evaluate(p);

	if (res.rows() != out) rcode--;

	k->kernel = new Wendland(13,3,1);
	res = k->evaluate(p);

	if (res.rows() != out) rcode--;

	return rcode;
}

