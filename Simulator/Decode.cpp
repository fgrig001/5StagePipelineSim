#include "Decode.h"
#include "PipelineStage.h"
#include <string>
#include <iostream>
using namespace std;

Decode::Decode(Simulator *sim):
	PipelineStage(sim),
	outA(0),
	outB(0)
{
	name = "Decode";
}

void Decode::update(){
	if(inInstruction == NULL){ // No prev stall
		inInstruction = MySim->MyFetch->outInstruction;
	}
	//Else: prev stall, do nothing
}

void Decode::execute(){

	// No instruction
	if(inInstruction == NULL){
		cout<<"here\n";
		outA = 0;
		outB = 0;
		outInstruction = NULL;
		myState = WAITING;
		return;
	}
	switch(inInstruction -> getInstruction()){
	case BRA:
	case ST:
		if(MySim -> busyRegisters.at(inInstruction -> getReg1())
		|| MySim -> busyRegisters.at(inInstruction -> getReg2())){
			myState = STALLING;
			cout << "STALLING RAW\n\n" << endl;
			outInstruction = NULL;
			return;
		}else{
			myState = PROCESSING;
		}
		break;	
	default:
		if((MySim -> busyRegisters.at(inInstruction -> getReg2()) != 0 
		&& MySim -> busyRegisters.at(inInstruction -> getReg2()) != inInstruction -> instructionNumber)
		|| (MySim -> busyRegisters.at(inInstruction -> getReg3())
		&& MySim -> busyRegisters.at(inInstruction -> getReg3()) != inInstruction -> instructionNumber)){
			myState = STALLING;
			cout << "STALLING RAW\n\n" << endl;
			outInstruction = NULL;
			return;
		}else{
			myState = PROCESSING;
		}
		break;
	}
	// Stalling
	if(MySim->MyExecute->myState == STALLING){
		cout<<"here2\n";
		myState = STALLING;
		return;	
	}
	// If Branch Instruction
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
	// If instruction other than branch
	}else{
		// If valid reg2 register
		if(inInstruction -> getReg2() != NONE){
			outA = MySim -> registerVals.at(inInstruction -> getReg2());
			//cout << "DE reading from reg: " << inInstruction -> getReg2() << " val = " << outA << endl;	
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
	cout<<"FLUSH\n";
	inInstruction = NULL;
	outInstruction = NULL;
	outA = 0;
	outB = 0;
}
