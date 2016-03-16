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
	// Stalling
	if(MySim->MyExecute->myState == STALLING){
		cout<<"here2\n";
		myState = STALLING;
		return;	
	}
	// Valid instruction
	if(inInstruction -> getInstruction() == BRA){
		if(inInstruction -> getReg1() != NONE
		&& inInstruction -> getReg2() != NONE){
			//Conditional Branch
			outA = MySim -> registerVals.at(inInstruction -> getReg1());
			outB = MySim -> registerVals.at(inInstruction -> getReg2());
		}else if(inInstruction -> getReg1() == NONE
		      && inInstruction -> getReg2() == NONE){
			//Unconditional Branch			
			outA = 0;
			outB = 0;
		}else{
			//Unsupported Branch instruction
			outA = -1;
			outB = -1;
		}

	}else{
		if(inInstruction -> getReg2() != NONE){
			outA = MySim -> registerVals.at(inInstruction -> getReg2());
		}else{
			//Unsupported Instruction
			outA = -1;
		}if(inInstruction -> getReg3() != NONE){
			outB = MySim -> registerVals.at(inInstruction -> getReg3());
		}else{ //TODO: Potential conflict with BR instruction
			outB = inInstruction -> reg3Val;
		}
	}
	cout<<"OUTA: "<<outA<<endl;
	cout<<"OUTB: "<<outB<<endl;
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
