#pragma once

#include <string>
#include "Instruction.h"

class Simulator;

class PipelineStage{
	public:
		PipelineStage(Simulator *sim);
		virtual void update()=0;
		virtual void execute()=0;
		void print();
		Instruction *inInstruction;
		Instruction *outInstruction;
		std::string name;
		enum State{STALLING,PROCESSING,WAITING}myState;		
	protected:
		Simulator *MySim;
};
