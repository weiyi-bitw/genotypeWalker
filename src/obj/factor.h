#include <stdio.h>
#include <string>
#include <map>

#ifndef FACTOR_H
#define FACTOR_H

class Factor{
  private:
	int nlevel;
	int *vec;
	int length;
	std::string *levels;
	std::map<std::string, int> levelMap;
	std::map<std::string, int>::iterator it;
  public:
	Factor();
	Factor(const std::string*, int);
	~Factor();
	std::string & operator[](const int);
	const std::string & operator[](const int) const;
	int getValue(int);
	int mapKey(std::string);
	std::string mapValue(int);
	int getLength(){ return length;}
	int getNlevel(){ return nlevel;}
};

#endif /* FACTOR_H */

