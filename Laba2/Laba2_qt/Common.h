#pragma once

#include <stdexcept>
#include <vector>
#include <string>

struct TransitionElement;

typedef unsigned char uchar;
typedef std::vector<TransitionElement> TransitionTable;

struct TransitionElement {
	int		currentState	= -1;
	int		nextState		= -1;		
	uchar	letter			= 0;		
	bool	isTerminalState	= false;	

	friend bool operator>(const TransitionElement& el, const TransitionElement& er)
	{
		if (el.currentState > er.currentState) {
			return true;
		}

		if (el.currentState == er.currentState) {
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

	friend bool operator<(const TransitionElement& el, const TransitionElement& er)
	{
		return !operator>(el, er);
	}
};

TransitionTable readStates4File(const std::string& filename);