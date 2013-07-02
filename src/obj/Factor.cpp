/*
 * =====================================================================================
 *
 *       Filename:  Factor.cpp
 *
 *    Description:  Implementation of class Factor
 *
 *        Version:  1.0
 *        Created:  06/25/2013 02:21:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include "factor.h"
Factor::Factor(){}
Factor::Factor(const std::string *input, int n){
	int en = 0;
	length = n;
	vec = new int[length];
	for(int i = 0; i < length; ++i){
		it = levelMap.find(input[i]);
		if(it == levelMap.end()){
			levelMap.insert(std::pair<std::string, int>(input[i], en));
			en++;
		}
		vec[i] = levelMap[input[i]];
	}
	nlevel = en;

	levels = new std::string[nlevel];
	it = levelMap.begin();
	for(int i = 0; i < nlevel; ++i){
		levels[it->second] = it->first;
		++it;
	}
		
}
 
Factor::~Factor(){
	if(vec != NULL) delete [] vec;
	if(levels != NULL) delete [] levels;
	//levelMap.clear();
}

std::string & Factor::operator[](const int k){
	if(k < 0 || k >= length){ 
		printf("Subscript out of bounds.\n");
		throw 1;
	}
	return levels[vec[k]];
}
const std::string & Factor::operator[](const int k) const{
	if(k < 0 || k >= length){
		printf("Subscript out of bounds.\n");
		throw 1;
	}
	return levels[vec[k]];
}


int Factor::getValue(int k){
	if(k < 0 || k >= length){ 
		printf("Subscript out of bounds.\n");
		throw 1;
	}
	return vec[k];
}

int Factor::mapKey(std::string s){
	it = levelMap.find(s);
	if(it == levelMap.end()){ 
		printf("Cannot find key.\n");
		throw 1;
	}
	return levelMap[s];
}

std::string Factor::mapValue(int l){
	if(l < 0 || l >= nlevel){ 
		printf("No such key.\n");
		throw 1;
	}
	return levels[l];
}
