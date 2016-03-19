#pragma once

#include "Simulator.h"
#include "PipelineStage.h"
#include <string>
class Fetch : public PipelineStage{
	public:
		Fetch(Simulator *sim);
		void update();
		void execute();
		void flush();
		int branchStall;
	private:
		int branchTarget;
};
