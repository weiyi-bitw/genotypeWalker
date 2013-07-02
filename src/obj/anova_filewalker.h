#include <iostream>
#include <fstream>
#include <string>
#include "anova.h"
#include "matrix.h"
#include "multi_leaderboard.h"

#ifndef ANOVA_FILEWALKER_H
#define ANOVA_FILEWALKER_H

class ANOVAFileWalker{
  private:
	int nFeatures;
	Matrix data;
	Anova aov;
  public:
	LeaderBoard* plb;

	ANOVAFileWalker(int n);
	~ANOVAFileWalker();
	
	void loadResponseFile(const char* fname, const char delim);
	void walk(const char* fname, const char delim);
};

#endif /* ANOVA_FILEWALKER_H */
