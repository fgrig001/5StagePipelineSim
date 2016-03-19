#include "Decode.h"
#include "PipelineStage.h"
#include <string>
#include <iostream>
using namespace std;

Decode::Decode(Simulator *sim):
	PipelineStage(sim),
	outA(0),
	outB(0),
	forward(false),
	flushFlag(false)
{
	name = "Decode";
}

void Decode::update(){
	// If no stall	
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
		if(flushFlag && myState == FLUSHING){
			flushFlag = false;	
		}else{
			myState = WAITING;
		}
		return;
	}

	forward = false;
	if(MySim -> fullForwarding){
		//cout << "ForwardedValues:" << endl;
		//for(auto elem : MySim -> forwardedValues){
		//	cout << elem.first << ", " << elem.second << endl;
		//} 
		switch(inInstruction -> getInstruction()){
		case ADD:
		case SUB:
		case MULT:
		case DIV:
		case LD:
			for(auto elem : MySim -> forwardedValues){
				if(inInstruction -> getReg2() == elem.first){
					forward = true;
				}
				if(inInstruction -> getReg3() == elem.first){
					forward = true;
				}
			}
			break;
		case ST:
		case BRA:
			for(auto elem : MySim -> forwardedValues){
				if(inInstruction -> getReg1() == elem.first){
					forward = true;
				}
				if(inInstruction -> getReg2() == elem.first){
					forward = true;
				}
			}
			break;
			
		}
	}


	if(!forward){
		switch(inInstruction -> getInstruction()){
		case BRA:
		case ST:
			if(!MySim -> busyRegisters.at(inInstruction -> getReg1()).empty()
			|| !MySim -> busyRegisters.at(inInstruction -> getReg2()).empty()){
				if(!forward){
					myState = STALLING;
					outInstruction = NULL;
					return;
				}else{
					myState = PROCESSING;
				}
			}else{
				myState = PROCESSING;
			}
			break;	
		default:
			set<int> busyReg2 = MySim -> busyRegisters.at(inInstruction -> getReg2());
			set<int> busyReg3 = MySim -> busyRegisters.at(inInstruction -> getReg3());
			if((!busyReg2.empty() && !(busyReg2.count(inInstruction -> instructionNumber) && busyReg2.size() == 1))
			|| (!busyReg3.empty() && !(busyReg3.count(inInstruction -> instructionNumber) && busyReg3.size() == 1))){
				if(!forward){
					myState = STALLING;
					outInstruction = NULL;
					return;	
				}
			
			}else{
				myState = PROCESSING;
			}
			break;
		}
	}
	// Stalling
	if(MySim->MyExecute->myState == STALLING){
		myState = STALLING;
		return;	
	}
	// If Branch instruction
	if(inInstruction -> getInstruction() == BRA){

		// If Conditional Branch
		if(inInstruction -> getReg1() != NONE
		&& inInstruction -> getReg2() != NONE){
			outA = MySim -> registerVals.at(inInstruction -> getReg1());
			outB = MySim -> registerVals.at(inInstruction -> getReg2());
		// If Unconditional Branch	
		}else if(inInstruction -> getReg1() == NONE
			  && inInstruction -> getReg2() == NONE){		
			outA = 0;
			outB = 0;
		// Unsupported Branch instruction
		}else{
			outA = -1;
			outB = -1;
		}

		// If branches are resolved in ID
		if(MySim -> branchesResolveInID){
			// If unconditional branch
			if(inInstruction -> getReg2() == NONE){
				if(MySim->branchPredictedNotTaken){
					int executeResult = MySim -> labels.at(inInstruction -> getLabel());
					MySim -> PC = executeResult-1;
					MySim -> MyFetch -> flush();
				}
				myState = PROCESSING;
			// If conditional branch (and taken)
			}else if(outA == outB){
				if(MySim->branchPredictedNotTaken){
					int executeResult = MySim -> labels.at(inInstruction -> getLabel());
					MySim -> PC = executeResult-1;
					MySim -> MyFetch -> flush();
				}
				myState = PROCESSING;
			// If conditional branch (and not taken)
			}else if(outA != outB){
				if(!MySim->branchPredictedNotTaken){
					MySim -> MyFetch -> flush();
					MySim -> PC = inInstruction -> instructionNumber-1;			
				}
				myState = PROCESSING;
			}
		}
	// If ST instruction	
	}else if(inInstruction -> getInstruction() == ST){
		if(inInstruction -> getReg1() != NONE
		&& inInstruction -> getReg2() != NONE){
			outB = MySim -> registerVals.at(inInstruction -> getReg1());
			outA = MySim -> registerVals.at(inInstruction -> getReg2());
		}
	// If instruction other than branch or Store
	}else{
		// If valid reg2 register
		if(inInstruction -> getReg2() != NONE){
			outA = MySim -> registerVals.at(inInstruction -> getReg2());
		}else{
			//Unsupported Instruction
			outA = -1;
		// If valid reg3 register (No an imediat)
		}if(inInstruction -> getReg3() != NONE){
			outB = MySim -> registerVals.at(inInstruction -> getReg3());
		// If reg3 is an imediat value
		}else{
			outB = inInstruction -> reg3Val;
		}
	}
	outInstruction = inInstruction;
	inInstruction = NULL;
	myState = PROCESSING;
}

void Decode::flush(){
	inInstruction = NULL;
	outInstruction = NULL;
	outA = 0;
	outB = 0;
	myState = FLUSHING;
	flushFlag = true;
}
