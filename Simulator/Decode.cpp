#include "Decode.h"
#include "PipelineStage.h"
#include <string>

Decode::Decode(Simulator *sim):
	PipelineStage(sim),
	outA(0),
	outB(0)
{
	name = "Decode";
}

void Decode::update(){
	inInstruction = MySim->MyFetch->outInstruction;
}

void Decode::execute(){
	if(inInstruction == NULL){
		outA = 0;
		outB = 0;
		outInstruction = NULL;
		return;
	}
	outA = MySim -> registerVals.at(inInstruction -> getReg2());
	outB = MySim -> registerVals.at(inInstruction -> getReg3());
	outInstruction = inInstruction;
}
