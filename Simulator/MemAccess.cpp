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
	//if(inInstruction){
		//int dest = inInstruction -> getReg1();
		//Instruction *execInst = MySim -> MyExecute -> inInstruction;
		//if(execInst && execInst -> hasTwoSourceOperands()){
		//	if(execInst -> getReg2() == inInstruction -> getReg1()
                //       || execInst -> getReg3() == inInstruction -> getReg1()){
		//		//Read after Write Hazard
		//	}
		//}
		//int exSrc1 = MySim -> in
	//}
	 
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
