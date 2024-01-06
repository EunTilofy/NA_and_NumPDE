#ifndef _DLS_HPP_
#define _DLS_HPP_

#include "linear.hpp"
#include "IO.hpp"
#include "DLS.hpp"
#include "function.hpp"
#include "calculator.hpp"
#include "eigen/Eigen/Core"
#include "eigen/Eigen/Dense"
#include "eigen/Eigen/LU"
#include "eigen/Eigen/QR"

using namespace linear;
using namespace Eigen;

class DLS {
public:

template<class T, int deg = 3>
vector<T> solveNormal(vector<T> x, vector<T> y, vector<T> rho) {
    assert(x.size() == y.size());
    int n = x.size();
    Mat<T> G(deg, deg);
    vector<T> c(deg);
    for(int i = 0; i < 2 * deg - 1; ++i) {
        T sum = 0;
        for(int j = 0; j < n; ++j) {
            sum += rho[j];
            if (i < deg) c[i] += rho[j] * y[j];
            rho[j] *= x[j];
        }
        for(int j = max(0, i-deg+1); j <= min(deg-1, i); ++j) {
            G[j][i-j] = sum;
        }
    }
    cerr << "G = " << G << "\n";
    return Gauss_elimination(G, Vec<T>(c)).toVector();
}


template<class T, int deg = 3> 
vector<T> solveQR(vector<T> x, vector<T> y) {
    assert(x.size() == y.size());
    int n = x.size();
    MatrixXd A(n, deg);
    VectorXd b(n);
    HouseholderQR<MatrixXd> qr;

    for(int i = 0; i < n; ++i) {
        A(i, 0) = 1;
        b(i) = y[i];
        for(int j = 1; j < deg; ++j) A(i, j) = A(i, j - 1) * x[i];
    }
	
    qr.compute(A);
    MatrixXd r = qr.matrixQR().triangularView<Upper>();
    MatrixXd q = qr.householderQ();

    Mat R(3, 3);
    for(int i = 0; i < deg; ++i) for(int j = 0; j < deg; ++j) R[i][j] = r(i, j);
    cerr << "R = " << R << "\n";
	
	VectorXd p = r.block<deg, deg>(0,0).lu().solve((q.transpose()*b).head(deg));
	vector<T> res(deg);
    for(int i = 0; i < deg; ++i) res[i] = p(i);
    return res;
}

};

#endif