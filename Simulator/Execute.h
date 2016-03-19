#pragma once

#include "Simulator.h"
#include "PipelineStage.h"

class Execute : public PipelineStage{
	public:
		Execute(Simulator *sim);
		void update();
		void execute();
		void flush();
		int inA, inB, outA, outB;
	private:
		
};
