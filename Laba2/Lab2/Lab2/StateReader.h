#pragma once

#include <vector>
#include <fstream>

#include "Common.h"

class StateReader { //class for reading states from file
public:

	StateReader(const char* filename);
	~StateReader() {
		stateFile.close();
	}

protected:
	StatesSwitchArray statemachineStates; // array of switches for automat

private:
	std::ifstream stateFile; // stream for reading file
};