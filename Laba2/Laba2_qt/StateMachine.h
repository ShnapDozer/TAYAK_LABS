#pragma once

#include <string>

#include "Common.h"

class StateMachine {
public:
	StateMachine();

    void setTransitionTable(const TransitionTable& transitionTable);
    TransitionTable getTransitionTable() const;
	
	bool hasHangs() const;
	bool isDeterministic() const;
    int expressionIsCorrect(const std::string& expression);
	
private: 
	bool hangs;
	bool deterministic;

	TransitionTable transitionTable;

	bool checkHangs();
	bool checkDeterministic();

	void update();
	int findNextIndex(int curState, uchar sym);
};
