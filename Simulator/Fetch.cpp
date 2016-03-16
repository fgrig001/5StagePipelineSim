#include "Fetch.h"
#include "PipelineStage.h"
#include <iostream>
#include <string>

Fetch::Fetch(Simulator *sim):
	PipelineStage(sim)
{
	name = "Fetch";
}

void Fetch::update(){
	// Check for new instruction
	if(MySim->PC < MySim->instructionBuffer.size()){ 
		// Check for prev stall
		if(inInstruction == NULL){ 
			// Grab new instruction
			inInstruction = MySim->instructionBuffer.at(MySim->PC);
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
	inInstruction = NULL;
	outInstruction = NULL;
}

