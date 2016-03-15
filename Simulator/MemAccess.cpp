#include "MemAccess.h"
#include <string>

MemAccess::MemAccess(Simulator *sim):
	PipelineStage(sim),
	inA(0),
	inData(0),
	outData(0)
	
{
	name = "MemAccess";
}

void MemAccess::update(){
	inInstruction = MySim->MyExecute->outInstruction;
	inA = MySim->MyExecute->outA;
	inData = MySim->MyExecute->outB;
}

void MemAccess::execute(){
	if(inInstruction == NULL){
		outData = 0;
		outInstruction = NULL;		
		myState = WAITING;
		return;
	}
	switch(inInstruction->getInstruction()){
	case LD:	
		outData = MySim->memory.at(inA);
		myState = PROCESSING;
		break;
	case ST:
		MySim->memory.at(inA) = inData;
		outData = inA;
		myState = PROCESSING;
		break;
	default:
		outData = inA;
		myState = PROCESSING;
		break;
	}
	outInstruction = inInstruction;
}
