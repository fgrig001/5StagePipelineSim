#include "Fetch.h"
#include "PipelineStage.h"
#include <iostream>
#include <string>

Fetch::Fetch(Simulator *sim):
	PipelineStage(sim),
	branchTarget(-1),
	branchStall(0)
{
	name = "Fetch";
}

void Fetch::update(){
	// Check for new instruction
	if(MySim->PC < MySim->instructionBuffer.size()){ 
		// If not a stall 
		if(inInstruction == NULL){ // If stall, then inInstruction will alread have a value
			// If branch predicted taken, grab branch target
			if(!MySim->branchPredictedNotTaken && branchTarget != -1){
				MySim -> PC = branchTarget;
				branchStall = MySim->branchesTakenIn;
			}
			// Grab new instruction
			inInstruction = MySim->instructionBuffer.at(MySim->PC);
			// If branch instruction
			if(inInstruction->getInstruction() == BRA){
				branchTarget = MySim->labels.at(inInstruction -> getLabel());
			}else{
				branchTarget = -1;
			}
			if(inInstruction->instructionNumber == -1){
				inInstruction->instructionNumber = ++MySim->instructionCount;
			}
		}else{
			return;
		} // If stall do nothing 
	}else{ 
		inInstruction = NULL;
		// If branch predicted taken, grab branch target
		if(!MySim->branchPredictedNotTaken && branchTarget != -1 && branchStall <= 0){
			MySim -> PC = branchTarget;
			inInstruction = MySim->instructionBuffer.at(MySim->PC);
		}
	}	
}

void Fetch::execute(){
	// Check for stall
	if(MySim->MyDecode->myState == STALLING || branchStall != 0){
		myState = STALLING;
		if(branchStall != 0){
			branchStall--  ;
			outInstruction = NULL;
		}
		// Check for empty instruction
		if(inInstruction == NULL){
			myState = WAITING;
		}
		return;
	}
	// Add destination register to busy list
	if(inInstruction && inInstruction -> hasDestination()){
		MySim -> busyRegisters.at(
				inInstruction -> getReg1()
			).insert(inInstruction->instructionNumber);
	}
	// Execute process **
	outInstruction = inInstruction;
	inInstruction = NULL;
	// ******************

	// Update State
	if(outInstruction == NULL){
		if(myState != FLUSHING)
			myState=WAITING;
	}else{
		myState=PROCESSING;
	}
	MySim -> PC += 1;
	
}

void Fetch::flush(){
	// May cause issues when current value of busyReg overwrote another value (non zero)
	if(inInstruction && inInstruction->hasDestination()){
		if(MySim->busyRegisters.at(
				inInstruction->getReg1()
			).count(inInstruction->instructionNumber)){
			MySim->busyRegisters.at(
				inInstruction->getReg1()
			).erase(inInstruction->instructionNumber);
		}
	}
	if(outInstruction && outInstruction->hasDestination()){
		if(MySim->busyRegisters.at(
				outInstruction->getReg1()
			).count(outInstruction->instructionNumber)){
			MySim->busyRegisters.at(
				outInstruction->getReg1()
			).erase(outInstruction->instructionNumber);
		}
	}
	inInstruction = NULL;
	outInstruction = NULL;
	branchTarget = -1;
	myState = FLUSHING;
}

