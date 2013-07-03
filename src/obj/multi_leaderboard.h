#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>

#ifndef MULTI_LEADERBOARD_H
#define MULTI_LEADERBOARD_H

class ScoredItem{
  public:
	std::string name;
	double score;
	ScoredItem(std::string n, double s);
	~ScoredItem();
};
struct Comparator_ascend{
	bool operator()(ScoredItem* lhs, ScoredItem* rhs){
		return (lhs->score < rhs->score);
	}
};

class LeaderBoard{
  private:
	std::map<std::string, int> listMap;
	std::vector<ScoredItem*>* rankedLists;
	int nList;
	int nLeader;
	double threshold;
	bool filled;
	friend std::ostream& operator<< (std::ostream &, LeaderBoard &);
  public:
	LeaderBoard();
	LeaderBoard(int l, int n, double th, std::string* lns);
	~LeaderBoard();

	void insert(std::string name, double* ss);

};


#endif /* MULTI_LEADERBOARD_H */


