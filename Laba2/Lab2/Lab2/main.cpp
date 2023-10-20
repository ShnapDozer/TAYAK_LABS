#include <iostream>
#include <string>

#include "StateMachine.h"
#include "StateReader.h"

int main() {

	try { // try to create object of StateMachine
		StateMachine stateMachine("states.txt");

		for (auto it : stateMachine.GetSwitches()) {
			std::cout << "q" << it.initialState
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