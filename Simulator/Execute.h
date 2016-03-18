#pragma once

#include "Simulator.h"
#include "PipelineStage.h"

class Execute : public PipelineStage{
	public:
		Execute(Simulator *sim);
		void update();
		void execute();
		int inA, inB, outA, outB;
	private:
		
};
