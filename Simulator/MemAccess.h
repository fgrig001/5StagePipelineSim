#pragma once

#include "Simulator.h"

class MemAccess{
	public:
		MemAccess(Simulator *sim);
		void update();
		void execute();
		Instruction *inInstruction;
		Instruction *outInstruction;
	private:
		Simulator *MySim;
};
