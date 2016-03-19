#pragma once

#include <string>
#include <fstream>
#include "Instruction.h"

class Simulator;

class PipelineStage{
	public:
		PipelineStage(Simulator *sim);
		virtual void update()=0;
		virtual void execute()=0;
		void print();
		void print2(ostream &out);
		Instruction *inInstruction;
		Instruction *outInstruction;
		std::string name;
		enum State{STALLING,PROCESSING,WAITING,FLUSHING}myState;		
	protected:
		Simulator *MySim;
};
