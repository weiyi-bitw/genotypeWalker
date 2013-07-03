/*
 * =====================================================================================
 *
 *       Filename:  testAnovaFW.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/01/2013 04:54:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include "anova_filewalker.h"
#include "configure.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <queue>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	if(argc < 2) std::cerr << "No configuration file is assigned." << std::endl;
	std::string confFile(argv[1]);


	Configuration conf(confFile);
	std::cout << conf;
	
	const int numProbes = conf.getInt("NUM_PROBES");
	const std::string ec10File = conf.get("EC10_FILE");
	std::string genotypeFiles = conf.get("GENOTYPE_FILE");
	const double pTh = conf.getDoub("P_VALUE");

	std::cout << pTh << std::endl;

	std::queue<std::string> gq;
	std::istringstream iss(genotypeFiles);
	std::string gf;	

	while(std::getline(iss, gf, ',')){
		gq.push(gf);
	}
	std::cout << gq.size() << " genotype files detected." << std::endl;	

	std::cout << "Initialize ANOVA file walker." << std::endl;	 
	ANOVAFileWalker afw(numProbes, pTh);

	std::cout << "Load EC10 file." << std::endl;	 
	afw.loadResponseFile(ec10File.c_str(), '\t');

	while(!gq.empty()){
		gf = gq.front();
		gq.pop();
		std::cout << "Walk through file " << gf << std::endl;
		afw.walk(gf.c_str(), '\t');
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

