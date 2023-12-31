#pragma once

#include <string>

#include "Common.h"

class StateMachine {
public:
	StateMachine();
	
	bool hasHangs() const;
	bool isDeterministic() const;
	bool isExpressionCorrect(const std::string& expression, int& errorPos);
	
	void setTransitionTable(const TransitionTable& transitionTable);
	TransitionTable getTransitionTable() const; 

private: 
	bool hangs;
	bool deterministic;

	TransitionTable transitionTable;

	bool checkHangs();
	bool checkDeterministic();

	void update();
	int findNextIndex(int curState, uchar sym);
	

	
	
	
};