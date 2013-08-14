
#include <iostream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
  private:
	std::map<std::string, int> rowMap;
	std::map<std::string, int> colMap;
	std::vector<std::string> rownames;
	std::vector<std::string> colnames;
	int ncol;
	int nrow;
	double* buffer;
	double** data;

  public:
	Matrix();
	~Matrix();
	
	void parseFile(const char*, char const);
	std::string getRowName(int) const;
	std::string getColName(int) const;
	std::map<std::string, int> getRowMap() const;
	std::map<std::string, int> getColMap() const;
	int getNcol() const;
	int getNrow() const;
	void transpose();
	double** getData() const;
	friend std::ostream& operator<<(std::ostream&, const Matrix&);
};

#endif /*  MATRIX_H */

