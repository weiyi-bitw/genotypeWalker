/*
 * =====================================================================================
 *
 *       Filename:  leaderboardTest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/01/2013 12:11:08 PM
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
#include "multi_leaderboard.h"

int main(){
	std::string lns[4] = {"a", "b", "c", "d"};
	LeaderBoard lb(4, 3, lns);
	double ssx[4] = {3.2, 5.3, 6., 1.};
	double ssy[4] = {5., 2.5, 3.2, 1.};
	double ssz[4] = {0., 5.1, 2.6, 3.};
	double ssw[4] = {6., 3.2, 1.1, 2.2};

	lb.insert("x", ssx);
	lb.insert("y", ssy);
	lb.insert("z", ssz);
	lb.insert("w", ssw);

	std::cout << lb;

	return 0;
}


