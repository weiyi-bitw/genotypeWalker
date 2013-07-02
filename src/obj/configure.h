#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>

#ifndef CONFIGURE_H
#define CONFIGURE_H

class Configuration{
  private:
	std::string filename;
	std::map<std::string, std::string> conf;
	std::map<std::string, std::string>::iterator it;
  public:
	Configuration(const std::string);
	~Configuration();
	
	std::string get(std::string);
	int getInt(std::string);
	double getDoub(std::string);
	char getChar(std::string);
	bool hasConf(std::string);
	friend std::ostream& operator<<(std::ostream&, Configuration &);
};

#endif /* CONFIGURE_H */
