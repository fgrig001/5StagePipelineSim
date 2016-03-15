#include "MemAccess.h"
#include <string>

MemAccess::MemAccess(Simulator *sim):
	PipelineStage(sim)
{
	name = "MemAccess";
}

void MemAccess::update(){
	inInstruction = MySim->MyExecute->outInstruction;
}

void MemAccess::execute(){
	outInstruction = inInstruction;
}
