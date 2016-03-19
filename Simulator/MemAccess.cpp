#include "MemAccess.h"
#include <string>
#include <iostream>
using namespace std;

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
	//
	/*if(inInstruction){
		//switch(inInstrucion -> getInstruction()){
			//case LD:
				if(!MySim -> busyRegisters[inInstruction -> getReg1()]){
					MySim -> busyRegisters[inInstruction -> getReg1()] = 1;
				}else{
					cout << "MEM STALL" << endl;
				}		
			
		//}
	}*/

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
		//cout << "Loading value " << outData << " at location " << inA << endl;
		myState = PROCESSING;
		//cout << "MEM Forwarding : " << inInstruction->getReg1() << " val = " << outData << endl; 
		MySim -> forwardedValues.insert(make_pair(inInstruction -> getReg1(), outData));		
		break;
	case ST:
		//cout << "Storing value " << inData << " at location " << inA << endl;
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
	//MySim -> busyRegisters[inInstruction -> getReg1()] = 0;
}

void MemAccess::flush(){
	inInstruction = NULL;
	outInstruction = NULL;
	inA = inData = outData = 0;
}
