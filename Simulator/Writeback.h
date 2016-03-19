#pragma once

#include "Simulator.h"
#include "PipelineStage.h"
#include <string>
class Writeback : public PipelineStage{
	public:
		Writeback(Simulator *sim);
		void update();
		void execute();
		void flush();
		int in;
	private:
};
