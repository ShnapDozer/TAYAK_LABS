#include "StateMachine.h"

#include <algorithm>
#include <iostream>

using namespace std;

StateMachine::StateMachine(const char* filename) : StateReader(filename), deterministic(true), hangs(false)
{
	sortStates();
	
	if (statemachineStates.size() == 0) { //some little check of machine
		throw runtime_error("Automat is empty");
	}
		
	if (statemachineStates[0].initialState != 0) {
		throw runtime_error("There is no initial state");
	}
		
	size_t countStates = statemachineStates.size();
	bool hasFinalState = false;
	for (size_t i = 0; i < countStates; i++) {
		if (hasFinalState = statemachineStates[i].isTerminalState)
			break;
	}
		
	if (!hasFinalState) {
		throw runtime_error("There is no final state");
	}
		
	deterministic = checkDeterministic();
	hangs = checkHangs();
}

bool StateMachine::checkDeterministic() {
	
	bool isDeterministic = true;
	size_t countStates = statemachineStates.size(); // count of elements in array
	
	for (size_t i = 1; i < countStates; i++) {
		auto currentState = statemachineStates[i - 1];
		auto prevState = statemachineStates[i - 1];

		if (prevState.initialState == currentState.initialState
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
	
	size_t countStates = statemachineStates.size();

	bool isHangs = false;
	for (size_t i = 0; i < countStates; i++) {
		if (!statemachineStates[i].isTerminalState) {
			bool found = false;
			// very bad algorithm to search in _SORTED_ array. I was laziness to do better :->
			
			for (size_t j = 0; j < countStates; j++) {
				if (statemachineStates[i].nextState == statemachineStates[j].initialState) {
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
const StatesSwitchArray& StateMachine::GetSwitches() const
{
	return statemachineStates;
}
void StateMachine::sortStates() {
	
	std::sort(statemachineStates.begin(), statemachineStates.end());
}
int StateMachine::findNextIndex(int curState, uchar sym) {
	
	size_t ln = statemachineStates.size();

	int found = -1;
	for (size_t j = 0; j < ln; j++) { // very bad algorithm to search in _SORTED_ array
		
		if (statemachineStates[j].initialState == curState 
			&& statemachineStates[j].letter == sym) {
			
			found = j;
			break;
		}
	}
	return found;
}

bool StateMachine::isDeterministic()
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
		if (statemachineStates[idx].isTerminalState) {
			if (i == strLen - 1) return true;
			errorPos = i + 1;
			return false;
		}
		currentState = statemachineStates[idx].nextState;
	}
	errorPos = strLen;
	return false;
}

bool StateMachine::hasHangs()
{
	return hangs;
}
