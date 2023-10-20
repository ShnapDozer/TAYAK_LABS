#include <iostream>
#include <string>

#include  <stdio.h>

#include "Common.h"
#include "StateMachine.h"

using namespace std;

int main() {

	try {
		StateMachine stateMachine;
		stateMachine.setTransitionTable(readStates4File("states.txt"));

		for (auto it : stateMachine.getTransitionTable()) {
            printf("q%d %c = %c%d\n", it.currentState, it.letter, (it.isTerminalState ? 'f' : 'q'), it.nextState);
		}

        printf("Has hangs %d\n", stateMachine.hasHangs());
        printf("Is deterministic %d\n", stateMachine.isDeterministic());

        while(true) {
//            testExpr = "for(inta=0;a<478;a++)";
            std::string testExpr;
            std::cout << "Enter expr: " << std::endl;
            std::cin >> testExpr;
            std::cout << testExpr << std::endl;

            int res = stateMachine.expressionIsCorrect(testExpr);
            if (res == -1) {
                printf("Expression is correct!\n");
            } else {
                printf("Incorrect expression. Error position: %d\n", res);
            }
        }


	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
	}


	return 0;
}
