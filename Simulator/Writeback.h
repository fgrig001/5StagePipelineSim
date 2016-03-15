#pragma once

#include "Simulator.h"

class Writeback{
	public:
		Writeback(Simulator *sim);
		void update();
		void execute();
	private:
		Instruction *inInstruction;
		Instruction *outInstruction;
		Simulator *MySim;
};
