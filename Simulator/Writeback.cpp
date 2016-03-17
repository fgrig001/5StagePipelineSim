#include "Writeback.h"
#include <string>
#include <iostream>
using namespace std;

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
		myState = WAITING;
		return;
	}
	
	switch(inInstruction->getInstruction()){
	
	case LD:
	case ADD:
	case SUB:
	case MULT:
	case DIV:
		cout << "WB writing to reg: " << inInstruction -> getReg1() << " val = " << in << endl;	
		MySim -> registerVals.at(inInstruction ->getReg1()) = in;
		myState = PROCESSING;
		MySim -> busyRegisters[inInstruction -> getReg1()] = 0;
		break;
	case ST:
	case BRA:
		myState = PROCESSING;
		break;
	default:
		break;
	}
	outInstruction = inInstruction;
}
