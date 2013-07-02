/*
 * =====================================================================================
 *
 *       Filename:  matrix.cpp
 *
 *    Description:  Implementation of Matrix object
 *
 *        Version:  1.0
 *        Created:  06/26/2013 02:46:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include "matrix.h"

Matrix::Matrix(){
	data = NULL;
}

Matrix::~Matrix(){
	if(data != NULL){
		for(int i = 0; i < nrow; i++)
			delete [] data[i];
		
		delete [] data;
		data = NULL;
	}
}

void Matrix::parseFile(const char* inFile, char const delim){
	std::ifstream ifs;
	std::string line;
	std::string token;
	int m = -1, n = -1;
	bool firstRow = true;

	// first round: get dimensions
	ifs.open(inFile);
	while(std::getline(ifs, line)){
		if(firstRow){
			std::istringstream iss(line);
			while(std::getline(iss, token, delim)) n++;
			firstRow = false;
		}
		++m;
	}

	std::cout << "Dimension: " << m <<  "\t" << n << std::endl; 

	data = new double*[m];
	for(int i = 0; i < m; i++) data[i] = new double[n];
	
	ifs.close();

	// second round, populate matrix
	ifs.open(inFile);
	firstRow = true;
	int x = -1, y = 0;
	while(std::getline(ifs, line)){
		y = 0;
		std::istringstream iss(line);
		if(firstRow){
			std::getline(iss, token, delim); // useless entry
			while(std::getline(iss, token, delim)){
				colMap.insert(std::pair<std::string, int>(token, y) );
				colnames.push_back(token);
				y++;
			}
			firstRow = false;
		}else{
			std::getline(iss, token, delim); // rowname
			rowMap.insert(std::pair<std::string, int>(token, x) );
			rownames.push_back(token);
			while(std::getline(iss, token, delim)){
				data[x][y] = atof(token.c_str());
				y++;
			}
		}
		x++;
	}
	ncol = n;
	nrow = m;
	ifs.close();
}

std::string Matrix::getRowName(int i) const{
	return rownames[i];
}

std::string Matrix::getColName(int i) const{
	return colnames[i];
}

int Matrix::getNcol() const{
	return ncol;
}
int Matrix::getNrow() const{
	return nrow;
}

std::map<std::string, int> Matrix::getRowMap() const{
	return std::map<std::string, int>(rowMap);
}

std::map<std::string, int> Matrix::getColMap() const{
	return std::map<std::string, int>(colMap);
}

void Matrix::transpose(){
	double** newData = new double*[ncol];
	for(int i = 0; i < ncol; i++){
		newData[i] = new double[nrow];
	}
	for(int i = 0; i < ncol; i++){
		for(int j = 0; j < nrow; j++){
			newData[i][j] = data[j][i];
		}
	}
	for(int i = 0; i < nrow; i++)
		delete [] data[i];
		
	delete [] data;
	data = newData;
	newData = NULL;

	std::map<std::string, int> tempMap(rowMap);
	rowMap = colMap;
	colMap = tempMap;

	std::vector<std::string> tempVec(rownames);
	rownames = colnames;
	colnames = rownames;

	int tmp = nrow;
	nrow = ncol;
	ncol = tmp;
}

double** Matrix::getData() const{
	return data;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m){
	os << "REFID";
	for(int j = 0; j < m.ncol; j++){
		os << "\t" << m.colnames[j];
	}os << std::endl;
	for(int i = 0; i < m.nrow; i++){
		os << m.rownames[i];
		for(int j = 0; j < m.ncol; j++){
			os << "\t" << m.data[i][j];
		}os << std::endl;
	}
}

