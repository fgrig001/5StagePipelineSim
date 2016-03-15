#include "Execute.h"
#include <string>

Execute::Execute(Simulator *sim):
	PipelineStage(sim)
{
	name = "Execute";
}

void Execute::update(){
	inInstruction = MySim->MyDecode->outInstruction;
}

void Execute::execute(){
	outInstruction = inInstruction;
}
