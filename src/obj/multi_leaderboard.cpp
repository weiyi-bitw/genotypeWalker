/*
 * =====================================================================================
 *
 *       Filename:  multi_leaderboard.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/26/2013 04:03:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include "multi_leaderboard.h"


ScoredItem::ScoredItem(std::string n, double s){
	name = n;
	score = s;
}
ScoredItem::~ScoredItem(){}

LeaderBoard::LeaderBoard(){}
LeaderBoard::LeaderBoard(int l, int n, std::string* lns){
	nList = l;
	nLeader = n;
	filled = false;
	rankedLists = new std::vector<ScoredItem*>[nList];
	for(int i = 0; i < nList; i++){
		listMap.insert(std::pair<std::string, int>(lns[i], i));
	}
}

LeaderBoard::~LeaderBoard(){
	std::vector<ScoredItem*>::iterator it;
	for(int i = 0; i < nList; i++){ 
		for(it = rankedLists[i].begin(); it != rankedLists[i].end(); ++it){
			delete (*it);
		}
		rankedLists[i].clear();
	}
	delete [] rankedLists;
}

void LeaderBoard::insert(std::string name, double *ss){
	for(int i = 0; i < nList; i++){
		ScoredItem* si = new ScoredItem(name, ss[i]);
		rankedLists[i].push_back(si);
	}
	for(int i = 0; i < nList; i++){
		std::sort(rankedLists[i].begin(),rankedLists[i].end(), Comparator_ascend());
		if(rankedLists[i].size() > nLeader){
			delete rankedLists[i][nLeader];
			rankedLists[i].pop_back();
		}
	}
}

std::ostream & operator<<(std::ostream &os, LeaderBoard &lb ){
	std::map<std::string, int>::iterator it = lb.listMap.begin();
	os << it->first << "\t" << it->first;
	++it;
	for( ; it != lb.listMap.end(); ++it){
		os << "\t" << it->first << "\t" << it->first;
	}os << std::endl;
	for(int i = 0; i < lb.rankedLists[0].size(); i++){
		os << lb.rankedLists[0][i]->name << "\t" << lb.rankedLists[0][i]->score;
		for(int j = 1; j < lb.nList; j++){
			os << "\t" << lb.rankedLists[j][i]->name << "\t" << lb.rankedLists[j][i]->score;
		}os << std::endl;
	}
	return os;	
}

