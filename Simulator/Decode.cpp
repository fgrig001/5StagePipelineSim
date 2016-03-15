#include "Decode.h"
#include "PipelineStage.h"
#include <string>

Decode::Decode(Simulator *sim):
	PipelineStage(sim)
{
	name = "Decode";
}

void Decode::update(){
	inInstruction = MySim->MyFetch->outInstruction;
}

void Decode::execute(){
	outInstruction = inInstruction;
}
