#pragma once

#include "Simulator.h"

class Decode{
	public:
		Decode(Simulator *sim);
		void update();
		void execute();
		Instruction *inInstruction;
		Instruction *outInstruction;
	private:
		Simulator *MySim;
};
