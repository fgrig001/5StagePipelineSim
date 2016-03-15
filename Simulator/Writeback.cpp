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
		return;
	}
	switch(inInstruction->getInstruction()){
	
	case LD:
	case ADD:
	case SUB:
	case MULT:
	case DIV:	
		MySim -> registerVals.at(inInstruction ->getReg1()) = in;
		break;
	default:
		break;
	}
	outInstruction = inInstruction;
}
