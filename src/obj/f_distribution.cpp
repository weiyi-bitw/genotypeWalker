/*
 * =====================================================================================
 *
 *       Filename:  Fdistribution.cpp
 *
 *    Description:  Implementation of Fdistribution class, adapted from `incgammabeta.h` file
 *    	from the Numerical Recipe source files 
 *
 *        Version:  1.0
 *        Created:  06/25/2013 01:35:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include "f_distribution.h"

const double Fdistribution::y[18] = {0.0021695375159141994,
0.011413521097787704,0.027972308950302116,0.051727015600492421,
0.082502225484340941, 0.12007019910960293,0.16415283300752470,
0.21442376986779355, 0.27051082840644336, 0.33199876341447887,
0.39843234186401943, 0.46931971407375483, 0.54413605556657973,
0.62232745288031077, 0.70331500465597174, 0.78649910768313447,
0.87126389619061517, 0.95698180152629142};
const double Fdistribution::w[18] = {0.0055657196642445571,
0.012915947284065419,0.020181515297735382,0.027298621498568734,
0.034213810770299537,0.040875750923643261,0.047235083490265582,
0.053244713977759692,0.058860144245324798,0.064039797355015485,
0.068745323835736408,0.072941885005653087,0.076598410645870640,
0.079687828912071670,0.082187266704339706,0.084078218979661945,
0.085346685739338721,0.085983275670394821};
const double Fdistribution::cof[14]={57.1562356658629235,-59.5979603554754912,
14.1360979747417471,-0.491913816097620199,.339946499848118887e-4,
.465236289270485756e-4,-.983744753048795646e-4,.158088703224912494e-3,
-.210264441724104883e-3,.217439618115212643e-3,-.164318106536763890e-3,
.844182239838527433e-4,-.261908384015814087e-4,.368991826595316234e-5};
const int Fdistribution::SWITCH = 3000;
const double Fdistribution::EPS = std::numeric_limits<double>::epsilon();
const double Fdistribution::FPMIN = std::numeric_limits<double>::min()/EPS;

double Fdistribution::gammln(const double xx) {
        int j;
        double x,tmp,y,ser;
        if (xx <= 0) throw("Bad argument in gammln. Must > 0.\n");
        y=x=xx;
        tmp = x+5.24218750000000000;
        tmp = (x+0.5)*log(tmp)-tmp;
        ser = 0.999999999999997092;
        for (j=0;j<14;j++) ser += cof[j]/++y;
        return tmp+log(2.5066282746310005*ser/x);
}

double Fdistribution::betai(const double a, const double b, const double x){
	double bt;
	if( a <= 0.0 || b <= 0.0) throw("Bad a or b in betai(a, b, x). Both must > 0.");
	if( x < 0.0 || x > 1.0) throw("Bad x in betai(a, b, x). 0 <= x <= 1");
	if( x == 0.0 || x == 1.0 ) return x;
	if(a > SWITCH && b > SWITCH) return betaiapprox(a, b, x);
	bt = exp(gammln(a+b) - gammln(a) - gammln(b) + a*log(x)+b*log(1.0-x));
	if(x < (a+1.0)/(a+b+2.0)) return bt*betacf(a, b, x)/a;
	else return 1.0-bt*betacf(b, a, 1.0-x)/b;
}

double Fdistribution::betacf(const double a, const double b, const double x){
	int m,m2;
	double aa,c,d,del,h,qab,qam,qap;
	qab=a+b;
	qap=a+1.0;
	qam=a-1.0;
	c=1.0;
	d=1.0-qab*x/qap;
	if (fabs(d) < FPMIN) d=FPMIN;
	d=1.0/d;
	h=d;
	for (m=1;m<10000;m++) {
		m2=2*m;
		aa=m*(b-m)*x/((qam+m2)*(a+m2));
                d=1.0+aa*d;
                if (fabs(d) < FPMIN) d=FPMIN;
                c=1.0+aa/c;
                if (fabs(c) < FPMIN) c=FPMIN;
                d=1.0/d;
                h *= d*c;
                aa = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));
                d=1.0+aa*d;
                if (fabs(d) < FPMIN) d=FPMIN;
                c=1.0+aa/c;
                if (fabs(c) < FPMIN) c=FPMIN;
                d=1.0/d;
                del=d*c;
                h *= del;
                if (fabs(del-1.0) <= EPS) break;
	}
        return h;
}

double Fdistribution::betaiapprox(const double a, const double b, const double x){
	int j;
        double xu,t,sum,ans;
        double a1 = a-1.0, b1 = b-1.0, mu = a/(a+b);
        double lnmu=log(mu),lnmuc=log(1.-mu);
        t = sqrt(a*b/((a+b)*(a+b)*(a+b+1.0)));
        if (x > a/(a+b)) {
		if (x >= 1.0) return 1.0;
                xu = std::min(1.,std::max(mu + 10.*t, x + 5.0*t));
        } else {
                if (x <= 0.0) return 0.0;
                xu = std::max(0.,std::min(mu - 10.*t, x - 5.0*t));
        }
        sum = 0;
        for (j=0;j<18;j++) {
		t = x + (xu-x)*y[j];
                sum += w[j]*exp(a1*(log(t)-lnmu)+b1*(log(1-t)-lnmuc));
        }
        ans = sum*(xu-x)*exp(a1*lnmu-gammln(a)+b1*lnmuc-gammln(b)+gammln(a+b));
        return ans>0.0? 1.0-ans : -ans;
}

double Fdistribution::invbetai(const double p, const double a, const double b){
	const double EPS=1.e-8;
        double pp,t,u,err,x,al,h,w,afac,a1=a-1.,b1=b-1.;
        int j;
        if (p <= 0.) return 0.;
        else if (p >= 1.) return 1.;
        else if (a >= 1. && b >= 1.) {
		pp = (p < 0.5)? p : 1. - p;
                t = sqrt(-2.*log(pp));
                x = (2.30753+t*0.27061)/(1.+t*(0.99229+t*0.04481)) - t;
                if (p < 0.5) x = -x;
                al = (x*x-3.)/6.;
                h = 2./(1./(2.*a-1.)+1./(2.*b-1.));
                w = (x*sqrt(al+h)/h)-(1./(2.*b-1)-1./(2.*a-1.))*(al+5./6.-2./(3.*h));
                x = a/(a+b*exp(2.*w));
	} else {
		double lna = log(a/(a+b)), lnb = log(b/(a+b));
                t = exp(a*lna)/a;
                u = exp(b*lnb)/b;
                w = t + u;
                if (p < t/w) x = pow(a*w*p,1./a);
                else x = 1. - pow(b*w*(1.-p),1./b);
	}
	afac = -gammln(a)-gammln(b)+gammln(a+b);
        for (j=0;j<10;j++) {
		if (x == 0. || x == 1.) return x;
                err = betai(a,b,x) - p;
                t = exp(a1*log(x)+b1*log(1.-x) + afac);
                u = err/t;
                x -= (t = u/(1.-0.5*std::min(1.,u*(a1/x - b1/(1.-x)))));
		if (x <= 0.) x = 0.5*(x + t);
                if (x >= 1.) x = 0.5*(x + t + 1.);
                if (fabs(t) < EPS*x && j > 0) break;
	}
        return x;
}

Fdistribution::Fdistribution(double nu1in, double nu2in){
	nu1 = nu1in;
	nu2 = nu2in;
	if(nu1 <= 0. || nu2 <= 0.){ 
		printf("Bad nu1, nu2. Both must > 0.\n");
		throw 1;
	}
	fac = 0.5 * (nu1*log(nu1) + nu2*log(nu2)) + 
		gammln(0.5*(nu1+nu2)) - gammln(0.5*nu1) - gammln(0.5*nu2);
}

double Fdistribution::p(double f){
	if(f <= 0.) throw ("Bad f. Must > 0.");
	return exp((0.5*nu1 - 1) * log(f) - 0.5*(nu1+nu2)*log(nu2+nu1*f) + fac);
}

double Fdistribution::cdf(double f){
	if(f < 0.){
		if(fabs(f) > 1E-10){
			printf("Bad f. Must >= 0.");
			throw 1;
		}else{
			return 0.;
		}
	}
	return betai(0.5*nu1, 0.5*nu2, nu1*f/(nu2+nu1*f));
}

double Fdistribution::invcdf(double p){
	if(p <= 0. || p >= 1.) throw ("Bad p. Must > 0 and < 1");
	double x = invbetai(p, 0.5*nu1, 0.5*nu2);
	return nu2*x/(nu1*(1.-x));
}


