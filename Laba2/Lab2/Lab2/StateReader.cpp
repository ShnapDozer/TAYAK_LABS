#include "StateReader.h"

#include <string>

using namespace std;

StateReader::StateReader(const char* filename) :stateFile(filename) {
	
	if (!stateFile.is_open()) {
		throw runtime_error("Invalid states file"); // can't open file
	}

	string tmpStr;
	int lineCounter = 0;
	while (getline(stateFile, tmpStr)) {
		
		lineCounter++;

		if (tmpStr.empty()) { // skip empty string
			continue;
		}  
		
		if (tmpStr[0] != 'q' && tmpStr[0] != 'Q') { // several check for input file format
			std::string errorMessage = ("Line " + std::to_string(lineCounter) + " must begin with 'q' letter");
			throw format_error(errorMessage.c_str());
		}
			
		string::size_type commaPos = tmpStr.find(',');
		
		if (commaPos == string::npos) {
			throw format_error("There is no comma");
		}
			
		string stateNumber = tmpStr.substr(1, commaPos - 1);
		ElementarySwitch tmpSw; // prepare next elementh in array
		tmpSw.initialState = atoi(stateNumber.c_str());
		
		if (tmpSw.initialState == 0 && stateNumber[0] != '0') {
			throw format_error("State number must contains digits only");
		}
			
		tmpSw.letter = tmpStr[commaPos + 1];
		
		if (tmpStr[commaPos + 2] != '=') {
			throw format_error("Expected '=' sign");
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
				throw format_error("Next state must begin with 'q' or 'f' letter");
		}
		
		stateNumber = tmpStr.substr(commaPos + 4);
		tmpSw.nextState = atoi(stateNumber.c_str());
		
		if (tmpSw.nextState == 0 && stateNumber[0] != '0') {
			throw format_error("State number must contains digits only");
		}
			
		statemachineStates.push_back(tmpSw); // add one switch to array of switches
	}
}