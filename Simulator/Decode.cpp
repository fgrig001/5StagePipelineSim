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
	if(inInstruction == NULL){ // No prev stall
		inInstruction = MySim->MyFetch->outInstruction;
	}
	//Else: prev stall, do nothing
}

void Decode::execute(){
	// No instruction
	if(inInstruction == NULL){
		outA = 0;
		outB = 0;
		outInstruction = NULL;
		myState = WAITING;
		return;
	}
	// Stalling
	if(MySim->MyExecute->myState == STALLING){
		myState = STALLING;
		return;	
	}
	// Valid instruction
	outA = MySim -> registerVals.at(inInstruction -> getReg2());
	outB = MySim -> registerVals.at(inInstruction -> getReg3());
	outInstruction = inInstruction;
	inInstruction = NULL;
	myState = PROCESSING;
}
