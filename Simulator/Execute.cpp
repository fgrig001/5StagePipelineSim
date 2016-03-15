#include "Execute.h"
#include <string>

Execute::Execute(Simulator *sim):
	PipelineStage(sim),
	inA(0),
	inB(0),
	outA(0),
	outB(0)
{
	name = "Execute";
}

void Execute::update(){
	inInstruction = MySim->MyDecode->outInstruction;
	inA = MySim->MyDecode->outA;
	inB = MySim->MyDecode->outB;

}

void Execute::execute(){
	if(inInstruction == NULL){
		outA = 0;
		outB = 0;
		outInstruction = NULL;
		return;
	}
	switch(inInstruction -> getInstruction()){
	case ADD:
	case LD:
	case ST:
		outA = inA + inB;
		break;	
	case SUB:
		outA = inA - inB;
		break;
	case MULT:
		outA = inA * inB;
		break;
	case DIV:
		outA = inA / inB;
		break;
	case BRA:
		if(inInstruction -> getReg1() == NONE){
			//TODO: we need to insert bubbles
			int executeResult = MySim -> labels.at(inInstruction -> getLabel());
			MySim -> PC = executeResult;
		}else if(inA == inB){
			//TODO: we need to insert bubbles
			int executeResult = MySim -> labels.at(inInstruction -> getLabel());
			MySim -> PC = executeResult;
		}
		break;
	}	
	outInstruction = inInstruction;
	outB = inB;
}
