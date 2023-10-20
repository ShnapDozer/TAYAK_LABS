#include "Common.h"

#include <fstream>
#include <string>

using namespace std;

TransitionTable readStates4File(const std::string& filename)
{	
	std::string tmpStr;
	std::ifstream stateFile;
	TransitionTable transitionTable;
	
	stateFile.open(filename.c_str());

	if(!stateFile.is_open()) {
		throw runtime_error("Cant open file!");
	}

	int lineCounter = 0;
	while (getline(stateFile, tmpStr)) {

		lineCounter++;

		if (tmpStr.empty()) { // skip empty std::string
			continue;
		}

		if (tmpStr[0] != 'q' && tmpStr[0] != 'Q') { // several check for input file format
			std::string errorMessage = ("Line " + std::to_string(lineCounter) + " must begin with 'q' letter");
			throw runtime_error(errorMessage.c_str());
		}

		string::size_type commaPos = tmpStr.find(',');

		if (commaPos == string::npos) {
			throw runtime_error("There is no comma");
		}

		string stateNumber = tmpStr.substr(1, commaPos - 1);
		TransitionElement tmpSw; // prepare next elementh in array
		tmpSw.currentState = atoi(stateNumber.c_str());

		if (tmpSw.currentState == 0 && stateNumber[0] != '0') {
			throw runtime_error("State number must contains digits only");
		}

		tmpSw.letter = tmpStr[commaPos + 1];

		if (tmpStr[commaPos + 2] != '=') {
			throw runtime_error("Expected '=' sign");
		}

		switch (tmpStr[commaPos + 3]) {
		case 'f':
		case 'F':
			tmpSw.isTerminalState = true;
			break;

		case 'q':
		case 'Q':
			tmpSw.isTerminalState = false;
			break;

		default:
			throw runtime_error("Next state must begin with 'q' or 'f' letter");
		}

		stateNumber = tmpStr.substr(commaPos + 4);
		tmpSw.nextState = atoi(stateNumber.c_str());

		if (tmpSw.nextState == 0 && stateNumber[0] != '0') {
			throw runtime_error("State number must contains digits only");
		}

		transitionTable.push_back(tmpSw);
	}

	return transitionTable;
}
