#pragma once

#include "Simulator.h"

class Fetch{
	public:
		Fetch(Simulator *sim);
		void update();
		void execute();
		void print();
		Instruction *inInstruction;
		Instruction *outInstruction;
	private:
		Simulator *MySim;
};
