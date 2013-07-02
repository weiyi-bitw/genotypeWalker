/*
 * =====================================================================================
 *
 *       Filename:  testConfigure.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2013 01:27:15 PM
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
#include "configure.h"

int main(){
	std::string a = "run_manifest.conf";
	Configuration conf(a);
	std::cout << conf;

	return 0;
}


