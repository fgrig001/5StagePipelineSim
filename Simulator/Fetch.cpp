#include "Fetch.h"
#include "PipelineStage.h"
#include <iostream>
#include <string>

Fetch::Fetch(Simulator *sim):
	PipelineStage(sim),
	branchTarget(0)
{
	name = "Fetch";
	
}

void Fetch::update(){
	// Check for new instruction
	if(MySim->PC < MySim->instructionBuffer.size()){ 
		// Check for prev stall
		if(inInstruction == NULL){ // If stall, then inInstruction will alread have a value
			// Grab new instruction
			if(!MySim->branchPredictedNotTaken && branchTarget){
				MySim -> PC = branchTarget;
			}
			cout<<"Fetch PC: "<<MySim -> PC<<endl;
			inInstruction = MySim->instructionBuffer.at(MySim->PC);
			if(inInstruction->getInstruction() == BRA){
				branchTarget = MySim->labels.at(inInstruction -> getLabel());
			}else{
				branchTarget = 0;
			}
			if(inInstruction->instructionNumber == -1){
				inInstruction->instructionNumber = ++MySim->instructionCount;
			}
			
		}else return; 
	}else{ 
		inInstruction = NULL;
	}	
}

void Fetch::execute(){
	// Check for stall
	if(MySim->MyDecode->myState == STALLING){
		myState = STALLING;
		// Check for empty instruction
		if(inInstruction == NULL){
			myState = WAITING;
		}
		return;
	}
	// Update outInstruction
	if(inInstruction && inInstruction -> hasDestination()){
		MySim -> busyRegisters[inInstruction -> getReg1()] = inInstruction->instructionNumber;
	}
	outInstruction = inInstruction;
	inInstruction = NULL;
	if(outInstruction == NULL){
		myState=WAITING;
	}else{
		myState=PROCESSING;
	}
	MySim -> PC += 1;
	cout<<"THE PC: "<<MySim->PC<<endl;
	
}

void Fetch::flush(){
	// May cause issues when current value of busyReg overwrote another value (non zero)
	if(inInstruction && inInstruction->hasDestination()){
		MySim->busyRegisters.at(inInstruction->getReg1()) = 0;
	}
	if(outInstruction && outInstruction->hasDestination()){
		MySim->busyRegisters.at(outInstruction->getReg1()) = 0;
	}
	inInstruction = NULL;
	outInstruction = NULL;
	branchTarget = 0;
}

