#include "StateMachine.h"

#include <algorithm>
#include <iostream>

using namespace std;

StateMachine::StateMachine() : deterministic(true), hangs(false)
{
	
}

bool StateMachine::checkDeterministic() {
	
	bool isDeterministic = true;
	size_t countStates = transitionTable.size();
	
	for (size_t i = 1; i < countStates; i++) {
		auto currentState = transitionTable[i - 1];
		auto prevState = transitionTable[i - 1];

		if (prevState.currentState == currentState.currentState
			&& prevState.letter == currentState.letter
			&& (prevState.isTerminalState != currentState.isTerminalState 
				|| prevState.nextState != currentState.nextState)) {
			
			isDeterministic = false;
			break;
		};
	}
	
	deterministic = isDeterministic;

	return isDeterministic;
}
bool StateMachine::checkHangs() {
	
	size_t countStates = transitionTable.size();

	bool isHangs = false;
	for (size_t i = 0; i < countStates; i++) {
		if (!transitionTable[i].isTerminalState) {
			
			bool found = false;			
			for (size_t j = 0; j < countStates; j++) {
				if (transitionTable[i].nextState == transitionTable[j].currentState) {
					found = true;
					break;
				}
			}

			if (!found) {
				isHangs = true;
				break;
			}
		}
	}

	hangs = isHangs;
	
	return isHangs;
}
TransitionTable StateMachine::getTransitionTable() const
{
	return transitionTable;
}

void StateMachine::setTransitionTable(const TransitionTable& transitionTable)
{
	this->transitionTable = transitionTable;

	update();
}

int StateMachine::findNextIndex(int curState, uchar sym) {
	
	size_t ln = transitionTable.size();

	int found = -1;
	for (size_t j = 0; j < ln; j++) { // very bad algorithm to search in _SORTED_ array
		
		if (transitionTable[j].currentState == curState 
			&& transitionTable[j].letter == sym) {
			
			found = j;
			break;
		}
	}
	return found;
}

void StateMachine::update()
{
	std::sort(transitionTable.begin(), transitionTable.end());

	if (transitionTable.size() == 0) { //some little check of machine
		throw runtime_error("Automat is empty");
	}

	if (transitionTable[0].currentState != 0) {
		throw runtime_error("There is no initial state");
	}

	size_t countStates = transitionTable.size();
	bool hasFinalState = false;
	for (size_t i = 0; i < countStates; i++) {
		if (hasFinalState = transitionTable[i].isTerminalState)
			break;
	}

	if (!hasFinalState) {
		throw runtime_error("There is no final state");
	}

	deterministic = checkDeterministic();
	hangs = checkHangs();
}

bool StateMachine::isDeterministic() const
{
	return deterministic;
}

bool StateMachine::isExpressionCorrect(const string& expression, int& errorPos) {
	
	if (!deterministic || hangs) {
		throw runtime_error("This automat cannot check expression");
	}
		
	size_t strLen = expression.size();

	int currentState = 0;
	for (int i = 0; i < strLen; i++) {
		int idx = findNextIndex(currentState, expression[i]);
		if (idx < 0) {
			errorPos = i;
			return false;
		}
		if (transitionTable[idx].isTerminalState) {
			if (i == strLen - 1) return true;
			errorPos = i + 1;
			return false;
		}
		currentState = transitionTable[idx].nextState;
	}
	errorPos = strLen;
	return false;
}

bool StateMachine::hasHangs() const
{
	return hangs;
}
