#pragma once

#include "Simulator.h"

class PipelineStage{
	public:
		virtual PipelineStage(Simulator *sim);
		virtual void update()=0;
		virtual void execute()=0;
		void print();
		Instruction *inInstruction;
		Instruction *outInstruction;
	private:
		Simulator *MySim;
};
