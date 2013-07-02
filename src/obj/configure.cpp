/*
 * =====================================================================================
 *
 *       Filename:  configure.cpp
 *
 *    Description: modified from René Nyffenegger's collection of things 
 *    		on the web
 *
 *    		http://www.adp-gmbh.ch/cpp/config_file.html
 *
 *        Version:  1.0
 *        Created:  07/02/2013 01:15:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include "configure.h"

std::string trim(std::string const& inS, const char* delims = " \t\r\n"){
	std::string outS(inS);
	std::size_t pos = outS.find_first_not_of(delims);
	if(pos != std::string::npos)
		outS.erase(0, pos);

	pos = outS.find_last_not_of(delims);
	if(pos != std::string::npos)
		outS.erase(++pos);
	
	return outS;
}

Configuration::Configuration(const std::string confFile){
	filename = confFile;
	std::ifstream ifs;
	std::string line;
	size_t posAssign;
	ifs.open(confFile.c_str());
	while(std::getline(ifs, line)){
		if(!line.length()) continue;
		if(line[0] == '#' || line[0] == ';') continue;

		posAssign = line.find('=');
		conf.insert(std::pair<std::string, std::string>(trim(line.substr(0, posAssign)), trim(line.substr(posAssign+1))));
	}
	ifs.close();
}

Configuration::~Configuration(){}

std::string Configuration::get(std::string key){
	it = conf.find(key);
	if(it == conf.end()) std::cerr << "Cannot find config key " << key << std::endl;
	return conf[key];
}

int Configuration::getInt(std::string key){
	it = conf.find(key);
	if(it == conf.end()) std::cerr << "Cannot find config key " << key << std::endl;
	return atoi(conf[key].c_str());
}

double Configuration::getDoub(std::string key){
	it = conf.find(key);
	if(it == conf.end()) std::cerr << "Cannot find config key " << key << std::endl;
	return atof(conf[key].c_str());
}
char Configuration::getChar(std::string key){
	it = conf.find(key);
	if(it == conf.end()) std::cerr << "Cannot find config key " << key << std::endl;
	return conf[key][0];
}

bool Configuration::hasConf(std::string key){
	it = conf.find(key);
	return (it!=conf.end());
}

std::ostream & operator<<(std::ostream &os, Configuration & cf){
	os <<  std::setfill('=') << std::setw(50) << std::left << "=== Configuration File " << std::endl;
	os << std::setfill(' ') << std::setw(20) << std::internal << "\n" <<  cf.filename << "\n" <<  std::endl;
	os << std::setfill('=') << std::setw(50) << "=" << std::endl;
	cf.it = cf.conf.begin();
	os << std::setfill(' ');
	while(cf.it != cf.conf.end()){
		os << std::setw(20) << std::left << cf.it->first;
		os << std::setw(10) << std::internal << " = ";
		os << cf.it->second << std::endl;;
		++cf.it;
	}
	return os;
}
