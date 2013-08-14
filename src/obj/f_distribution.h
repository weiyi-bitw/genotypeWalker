/*
 * Fdistribution.h
 *
 * adapted from incgammabeta.h of the Numerical Recipe source files
 *
 */

#include <stdio.h>
#include <cmath>
#include <limits>
#include <algorithm>

#ifndef FDISTRIBUTION_H
#define FDISTRIBUTION_H


class Fdistribution{
  private:
	static const double y[18];
	static const double w[18];
	static const double cof[14];
	static const int SWITCH;
	static const double EPS;
	static const double FPMIN;
	double nu1, nu2;
	double fac;
	double gammln(const double);
	double betai(const double, const double, const double);
	double betailn(const double, const double, const double);
	double betaiapprox(const double, const double, const double);
	double betacf(const double, const double, const double);
	double invbetai(const double, const double, const double);
  public:
	Fdistribution(double, double);
	double p(double);
	double cdf(double);
	double lncdf(double);
	double invcdf(double);
};




#endif /* FDISTRIBUTION_H */
