#include <Rcpp.h>
#include <cstdint>
#include <cmath>
#include <algorithm>
using namespace Rcpp;

// [[Rcpp::export]]
double MOK_Cpp(const NumericVector & X, double k) {
  int n = X.size();
  NumericVector aXs = abs(clone(X).sort());

  double T2, T3;
  NumericVector T2_vec(n), T3_vec(n);
  NumericVector smaller(n);

  // We're using 1-indexing for j
  for (int j = k; j <= n - k + 1; j++) {
    // populate vector of indicators of smaller elements
    for (int i = 0; i < n; i++) {
      smaller[i] = aXs[i] < aXs[j - 1] ? 1 : 0;
    }

    T2 = Rf_choose(n - j, k) *
      Rf_choose(j - 1, k - 1);

    T2_vec = T2_vec + T2 * smaller;

    T3 = Rf_choose(n - j, k - 1) *
      Rf_choose(j - 1, k);
    T3_vec = T3_vec + T3 * smaller;
  }

  NumericVector D_vec = abs(T2_vec - T3_vec);

  double D_max = max(D_vec);
  return sqrt((double)n) * D_max / Rf_choose(n, 2 * k);
}

