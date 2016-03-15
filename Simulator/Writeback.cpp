#include "Writeback.h"
#include <string>
Writeback::Writeback(Simulator *sim):
	PipelineStage(sim),
	in(0)
{
	name = "Writeback";
}

void Writeback::update(){
	inInstruction = MySim->MyMemAccess->outInstruction;
	in = MySim->MyMemAccess->outData;
}

void Writeback::execute(){
	if(inInstruction == NULL){
		outInstruction = inInstruction;
		myState = WAITING;
		return;
	}
	switch(inInstruction->getInstruction()){
	
	case LD:
	case ADD:
	case SUB:
	case MULT:
	case DIV:	
		MySim -> registerVals.at(inInstruction ->getReg1()) = in;
		myState = PROCESSING;
		break;
	default:
		break;
	}
	outInstruction = inInstruction;
}
