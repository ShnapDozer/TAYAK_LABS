#pragma once

#include <stdexcept>
#include <vector>

struct ElementarySwitch;

typedef unsigned char uchar;
typedef std::vector<ElementarySwitch> StatesSwitchArray;

class format_error : public std::runtime_error {
public:
	format_error(const char* msg) : runtime_error(msg) {}
};

struct ElementarySwitch { // one switch for automat
	int initialState;		// number of current state
	uchar letter;			// reading symbol
	bool isTerminalState;	// is next state terminal?
	int nextState;			// number of next state

	ElementarySwitch() : initialState(-1), letter(0), isTerminalState(false), nextState(-1) {}

	// next 2 operators - for sorting states array
	friend bool operator > (const ElementarySwitch& el, const ElementarySwitch& er) {
		if (el.initialState > er.initialState) {
			return true;
		}

		if (el.initialState == er.initialState) {
			if (el.letter > er.letter) {
				return true;
			}
			if (el.letter == er.letter) {
				if (el.isTerminalState != er.isTerminalState) {
					return er.isTerminalState;
				}
				if (el.nextState > er.nextState) {
					return true;
				}
			}
		}

		return false;
	}

	friend bool operator < (const ElementarySwitch& el, const ElementarySwitch& er) {
		return !operator>(el, er);
	}
};