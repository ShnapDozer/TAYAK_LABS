#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <regex>
#include <sstream>

typedef std::vector<std::string> StringList;

StringList split(const std::string& s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

bool isInputAlphabetTerm(const std::string& term) {
    const regex rulesReg(R"(([A-Z])>(.+))");
}

class PDA_FMS {
public:
    struct Rule {
        std::string term;
        std::string token;
        std::string mToken;
        std::string outStack;

    };

    PDA_FMS(const std::string& ruleFilePath, const std::string& inputTapeStr) 
        : m_inputTape(inputTapeStr) {
        
        using namespace std;

        ifstream file(ruleFilePath);
        if (file.is_open()) {

            string line;
            while (std::getline(file, line)) {

                smatch match;
                const regex rulesReg(R"(([A-Z])>(.+))");
                if (!regex_search(line, match, rulesReg) 
                    || line[line.size() - 1] == '|' 
                    || line[2] == '|') {
                    
                    cout << "Не удалось распознать содержимое файла\n" << endl;
                } else {
                    string term = match[1];
                    StringList rulesStr = split(match[2], '|');
                    for (string& rule : rulesStr) {
                        cout << rule << endl;
                    }
                }
            }
        }
    }

private:
    std::stringstream m_inputTape;
    StringList m_inputAlphabet;
    StringList m_stackAlphabet;
    std::map<std::string, std::vector<Rule>> m_nonTermCommandsMap;
};


int main() {
    PDA_FMS fms("test1.txt", "aaabbbccc");

    return 0;
}