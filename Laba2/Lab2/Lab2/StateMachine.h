#pragma once

#include <string>

#include "StateReader.h"
#include "Common.h"

class StateMachine : public StateReader {
public:
	StateMachine(const char* filename);
	
	bool isDeterministic();
	bool isExpressionCorrect(const std::string& expression, int& errorPos);
	bool hasHangs();
	
	const StatesSwitchArray& GetSwitches() const; // just for printing
	
protected:
	int findNextIndex(int curState, uchar sym);
	void sortStates();

	bool checkDeterministic();
	bool checkHangs();
	
private: 
	bool deterministic;
	bool hangs;
	
};