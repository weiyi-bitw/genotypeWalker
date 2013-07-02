/*
 * =====================================================================================
 *
 *       Filename:  testFileName.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2013 12:30:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>

int main(){
	std::string fname  = "/home/weiyi/ToxChallenge_dosage_chr10.txt";
	std::string outFileName(fname);
	unsigned endpos = outFileName.find(".txt");
	unsigned startpos = outFileName.rfind("/");
	outFileName = outFileName.substr(startpos+1, (endpos-startpos-1)) + "_topProbes.txt";
	
	std::cout << fname << std::endl;
	std::cout << outFileName << std::endl;

	return 0;
}

