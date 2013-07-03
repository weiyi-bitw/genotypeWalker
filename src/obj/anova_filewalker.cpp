/*
 * =====================================================================================
 *
 *       Filename:  anova_filewalker.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/01/2013 02:19:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include "anova_filewalker.h"

ANOVAFileWalker::ANOVAFileWalker(int n, double pth){
	nFeatures = n;
	pThreshold = pth;
}
ANOVAFileWalker::~ANOVAFileWalker(){
	if(plb != NULL){
		delete plb;
		plb = NULL;
	}
}

void ANOVAFileWalker::loadResponseFile(const char* fname, const char delim= '\t'){
	data.parseFile(fname, delim);
	data.transpose();
	std::string* listNames = new std::string[data.getNrow()];
	for(int i = 0; i < data.getNrow(); i++){
		listNames[i] = data.getRowName(i);
	}
	//std::cout << pThreshold << std::endl;
	plb = new LeaderBoard(data.getNrow(), nFeatures, pThreshold, listNames);
	delete [] listNames;
}

void ANOVAFileWalker::walk(const char* fname, const char delim = '\t'){
	std::ifstream ifs;
	std::string line;
	std::string token;

	ifs.open(fname);
	std::getline(ifs, line);

	// identify overlapping samples
	std::vector<int> assignment;
	std::istringstream iss(line);
	
	std::map<std::string, int> sampleMap = data.getColMap();
	std::map<std::string, int>::iterator it;

	std::getline(iss, token, delim); // useless
	while(std::getline(iss, token, delim)){
		it = sampleMap.find(token);
		if(it != sampleMap.end()){
			assignment.push_back(it->second);
		}else{
			assignment.push_back(-1);
		}
	}
	int nCol = assignment.size();
	int nSamples = data.getNcol();
	//std::cout << "nCol: " << nCol << "nSamples: " << nSamples << std::endl; 
	int lineCnt = 0;
	std::string* genotype = new std::string[nSamples];
	for(int i = 0; i < nSamples; i++) genotype[i] = "0";
	double *p;
	double **pData = data.getData();
	int dataNrow = data.getNrow();
	while(std::getline(ifs, line)){
		if(lineCnt % 1000 == 0) std::cout << lineCnt << std::endl;
		std::istringstream iss2(line);
		std::getline(iss2, token, delim);
		std::string feature = token;
		int idx = 0;
		while(std::getline(iss2, token, delim)){
			if(assignment[idx] >= 0){
				genotype[assignment[idx]] = token;
			}
			idx++;
		}
		Factor fc(genotype, nSamples);
		if(fc.getNlevel() > 1){
			aov.setAnova(&fc, nSamples);
			aov.anova(pData, dataNrow, nSamples);
			p = aov.result.getPvalue();
			plb->insert(feature, p);
			aov.clear();
		}
		++lineCnt;
	}
	if(lineCnt < 1) std::cout << "WARNING: No lines detected in genotype file!" << std::endl;
	delete [] genotype;
	ifs.close();
	std::cout << "anova finished." << std::endl;
	std::string outFileName(fname);
	unsigned endpos = outFileName.find(".txt");
	unsigned startpos = outFileName.rfind("/");
	outFileName = outFileName.substr(startpos+1, (endpos-startpos-1)) + "_topProbes.txt";
	std::cout << "Write to file " << outFileName << std::endl;
	std::ofstream ofs;
	ofs.open(outFileName.c_str());
	ofs << (*plb);
	ofs.close();

}

