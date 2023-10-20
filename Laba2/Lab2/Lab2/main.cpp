#include <iostream>
#include <string>

#include "Common.h"
#include "StateMachine.h"

int main() {

	try {
		StateMachine stateMachine;
		stateMachine.setTransitionTable(readStates4File("states.txt"));

		for (auto it : stateMachine.getTransitionTable()) {
			std::cout << "q" << it.currentState
				<< "," << it.letter 
				<< "=" << (it.isTerminalState ? "f" : "q")
				<< it.nextState << std::endl;
		}

		std::cout << "There are" << (stateMachine.hasHangs() ? "" : "n't") << " hangs" << std::endl;
		std::cout << "Automat is" << (stateMachine.isDeterministic() ? "" : "n't") << " deterministic" << std::endl;

		std::string testExpr;
		std::cout << "Please, enter expression to check ";
		std::cin >> testExpr;

		// for test with related "states.txt" file
		// testExpr = " for( int abAccc= 943 ; a<478; bbc++ )";
		// std::cout << testExpr << std::endl;

		int err;
		bool res = stateMachine.isExpressionCorrect(testExpr, err);
		if (res) {
			std::cout << "Expression is correct!" << std::endl;
		} else {
			std::cout << "Incorrect expression. Error position: " << err << std::endl;
		}

	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}