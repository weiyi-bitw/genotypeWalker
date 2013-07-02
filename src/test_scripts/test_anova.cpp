/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  test script
 *
 *        Version:  1.0
 *        Created:  06/25/2013 01:24:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string>
#include "factor.h"
#include "anova.h"

int main(){
	std::string ss[20] = {"0", "0","0","0","0","1","1","1","1","1","2","2","2","2","2","3","3","3","3","3"};
	double x[20] = {12., 15., 18., 16. ,20., 20., 21., 22., 19., 20., 17., 16., 19., 15., 19., 14., 13., 12., 14., 11.};
	double** pd;
	pd = new double*[2];
	for(int i = 0; i < 2; i++){
		 pd[i] = new double[20];
		for(int j = 0; j < 20; j++){
			pd[i][j] = x[j] *(i+1);
		}
	}


	Factor fct(ss, 20);
	int nl = fct.getNlevel();
	printf("Factor initialized, nlevel = %d\n", nl);
	
	Anova aov;
	aov.setAnova(&fct, 20);
	printf("Anova obj initialized.\n");

	aov.anova(pd, 2, 20);

	double* p  = NULL;
	p = aov.result.getPvalue();

	for(int i = 0; i < 2; i++)
		printf("%lf\n", p[i]);
	

	for(int i = 0; i < 2; i++){
		delete [] pd[i];
	}
	delete [] pd;

	return 0;
}



