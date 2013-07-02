
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "factor.h"
#include "f_distribution.h"

#ifndef ANOVA_H
#define ANOVA_H

class AOVResult{
  private:
	const double* const* pData;
	int m;
	int n;
	Factor* pfct;
	double* ss_btwg;
	double* ss_wig;
	double* ss_tot;
	double d1;
	double d2;
	Fdistribution* fDist;
	double* f;
	double* p_value;

  public:
	AOVResult();
	~AOVResult();
	void saveResult(
		const double* const* pd,
		int mIn,
		int nIn,
		Factor* pfctIn,
		double* ss_btwg_in,
		double* ss_wig_in,
		double* ss_tot_in,
		double d1In,
		double d2In,
		double* fIn
	);
	double* getPvalue() const;
	void print() const;
	void clear();
};

class Anova{
  public:
	AOVResult result;

	Anova();
	~Anova();
	void setAnova(Factor* fctIn, int n);
	void anova(const double* const* dataIn, int mIn, int nIn);
	void clear();
  private:
	int n;
	Factor* fct;
};

#endif /* ANOVE_H */

