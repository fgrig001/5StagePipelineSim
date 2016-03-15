#include "Writeback.h"
#include <string>
Writeback::Writeback(Simulator *sim):
	PipelineStage(sim)
{
	name = "Writeback";
}

void Writeback::update(){
	inInstruction = MySim->MyMemAccess->outInstruction;
}

void Writeback::execute(){
	outInstruction = inInstruction;
}
