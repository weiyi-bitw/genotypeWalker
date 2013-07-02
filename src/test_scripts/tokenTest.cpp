/*
 * =====================================================================================
 *
 *       Filename:  tokenTest.cpp
 *
 *    Description:  test tokenize string
 *
 *        Version:  1.0
 *        Created:  06/26/2013 02:59:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include "matrix.h"
#include <iostream>

int main(int argc, char *argv[]){
	Matrix mat;
	mat.parseFile(argv[1], '\t');
	std::cout << mat;
	mat.transpose();
	std::cout << mat;

	return 0;
}



