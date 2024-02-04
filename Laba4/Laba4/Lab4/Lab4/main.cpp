#include <iostream>
#include <Windows.h>
#include <string>

#include "FileReader.h"
#include "PushdownAutomaton.h"

//void main(){ int a = 3; }
//void main(){ if (a < b) return 5; }
//void main(){ if ((a < b) or (c < d)) return 5; }
//void main(){ for (int a = 0;10 < a;) return 5; }
//void main(){ while (a < b) return 5; }
//void main(){ if (a < b) {return 5;} else {return 2;} } 
//void main(){ if (a < b) return 5; else }

// void main(){ int arw{1}{1} = { { 1) 1 }) { 1) 1 } }; }

int main()
{
    SetConsoleOutputCP(65001);

    FileReader fileReader;
    fileReader.readRules("fix.txt");

    fileReader.printRawRules();
    fileReader.printInputAlphabet();
    fileReader.printNonterminalsAlphabet();
    fileReader.printAlphabet();
    fileReader.printCommands();

    std::string input;
    while (true)
    {
        std::cout << "Enter the line:" << std::endl;
        std::getline(std::cin, input);
        
        char ch = '&&';
        int indexOfChar = input.find(ch);
        if (indexOfChar != -1) { input.replace(indexOfChar, 2, "or"); }
            

        ch = '||';
        indexOfChar = input.find(ch);
        if (indexOfChar != -1) { input.replace(indexOfChar, 2, "and"); }

        PushdownAutomaton automaton(input, fileReader.getCommands(), fileReader.getTerminals(), fileReader.getNonTerminals());

        automaton.checkStr(input);

        if (automaton.getErrorCount() > 0)
        {
            std::cout << "\nError with string\n";
            std::cout << "Count errors: " << automaton.getErrorCount() << std::endl;
        }
        else
        {
            std::cout << "\nChain configurations:\n";
            for (std::string str : automaton.getChainConfigurations())
            {
                std::cout << str << "\n";
            }

            std::cout << "\nString is good!" << std::endl;
        }

        std::cout << std::endl;
    }
    return 0;
}