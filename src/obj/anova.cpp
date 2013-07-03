/*
 * 
 * Perform anova and get p-value
 *
 */

#include "anova.h"
AOVResult::AOVResult(){
	pData = NULL;
	ss_btwg = NULL;
	ss_wig = NULL;
	ss_tot = NULL;
	pfct = NULL;
	fDist = NULL;
	f = NULL;
	p_value = NULL;
}

AOVResult::~AOVResult(){
	if(fDist != NULL){
		delete fDist;
		fDist = NULL;
	}
	if(p_value != NULL){
		delete [] p_value;
		p_value = NULL;
	}	
	if(f != NULL){
		delete [] f;
		f = NULL;
	}
	if(ss_tot != NULL){
		delete [] ss_tot;
		ss_tot = NULL;
	}
	if(ss_wig != NULL){
		delete [] ss_wig;
		ss_wig = NULL;
	}
	if(ss_btwg != NULL){
		delete [] ss_btwg;
		ss_btwg = NULL;
	}
}
void AOVResult::saveResult(
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
){
	pData = pd;
	n = nIn;
	m = mIn;
	pfct = pfctIn;
	ss_btwg = ss_btwg_in;
	ss_wig = ss_wig_in;
	ss_tot = ss_tot_in;
	d1 = d1In;
	d2 = d2In;
	f = fIn;
	pfct = pfctIn;
	p_value = new double[m];
	fDist = new Fdistribution(d1, d2);
	for(int i = 0; i < m; i++){
		printf("%lf\n", f[i]);
		p_value[i] = 1. - fDist->cdf(f[i]);
	}printf("\n");
}

double* AOVResult::getPvalue() const{
	return p_value;
}

void AOVResult::print() const{
	for(int i = 0; i < m; i++){
		printf("Variable %d:", i);
		printf("%-20s %10s %10s %10s %10s\n", " ", "SS", "df", "F", "P value");
		printf("%-20s:%10lf %10lf %10lf %10lf\n", "Between Groups", ss_btwg[i], d1, f[i], p_value[i] );
		printf("%-20s:%10lf %10lf\n", "Within Groups", ss_wig[i], d2);
		printf("%-20s:%10lf %10lf\n", "Total", ss_tot[i], d1+d2);
	}
}

void AOVResult::clear(){
	if(fDist != NULL){
		delete fDist;
		fDist = NULL;
	}
	if(p_value != NULL){
		delete [] p_value;
		p_value = NULL;
	}	
	if(f != NULL){
		delete [] f;
		f = NULL;
	}
	if(ss_tot != NULL){
		delete [] ss_tot;
		ss_tot = NULL;
	}
	if(ss_wig != NULL){
		delete [] ss_wig;
		ss_wig = NULL;
	}
	if(ss_btwg != NULL){
		delete [] ss_btwg;
		ss_btwg = NULL;
	}
}


Anova::Anova(){}
Anova::~Anova(){
	result.clear();
}
void Anova::setAnova(Factor*  fctIn, int n){
	this->n = n;
	fct = fctIn;
}
  
void Anova::anova(const double* const* dataIn, int mIn, int nIn){
	if(nIn != n){
		printf("nIn != n\n");
		throw("Input data has different number of samples than the group data.");
	}

	int nl = fct->getNlevel();

	int *nG = new int[nl];
	double *muG = new double[nl];
	double *muG2 = new double[nl];
	double* ssWG = new double[mIn];
	double* ssBG = new double[mIn];
	double* ssTot = new double[mIn];
	double* f = new double[mIn];
	double d1 = nl-1;
	double d2 = n-nl;	

	for(int l = 0; l < mIn; ++l){
	//initialization
		ssWG[l] = ssTot[l] = 0.;
		for(int i = 0; i < nl; i++) muG[i] = muG2[i] = nG[i] = 0.;

		for(int i = 0; i < n; i++){
			int c = fct->getValue(i);
			muG[c] += dataIn[l][i];
			muG2[c] += dataIn[l][i] * dataIn[l][i];
			nG[c]++;
		}
	
		double muTot = 0.;
		for(int i = 0; i < nl; i++){
			ssWG[l] += (muG2[i] - muG[i]*muG[i]/nG[i] );
			muTot += muG[i];
			ssTot[l] += muG2[i];
		}
		ssTot[l] = ssTot[l] - muTot*muTot/n;
	
		ssBG[l] = ssTot[l] - ssWG[l];
		f[l] = ssBG[l] * d2 / d1 / ssWG[l];
		printf("ssWG: %lf \t ssTot: %lf \t f: %lf \n", ssWG[l], ssTot[l], f[l]);
	}

	delete [] nG;
	delete [] muG;
	delete [] muG2;

	result.saveResult(dataIn, mIn, n, fct, ssBG, ssWG, ssTot, d1, d2, f);
}

void Anova::clear(){
	result.clear();
}
