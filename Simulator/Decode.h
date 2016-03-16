#pragma once

#include "Simulator.h"
#include "PipelineStage.h"
#include <string>
class Decode : public PipelineStage {
	public:
		Decode(Simulator *sim);
		void update();
		void execute();
		void flush();
		int outA, outB; 
	private:
};
