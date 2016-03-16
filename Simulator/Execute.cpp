#include "Execute.h"
#include <string>
#include <iostream>
using namespace std;

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
	
	//if(inInstruction && outInstruction && outInstruction -> getReg1() == inInstruction
	inA = MySim->MyDecode->outA;
	inB = MySim->MyDecode->outB;
}

void Execute::execute(){
	if(inInstruction == NULL){
		outA = 0;
		outB = 0;
		outInstruction = NULL;
		myState = WAITING;
		return;
	}
	cout<<"Instruction: "<<inInstruction->getInstruction()<<endl;
	switch(inInstruction -> getInstruction()){
	case ADD:
	case LD:
	case ST:
		outA = inA + inB;
		myState = PROCESSING;
		break;	
	case SUB:
		outA = inA - inB;
		myState = PROCESSING;
		break;
	case MULT:
		outA = inA * inB;
		myState = PROCESSING;
		break;
	case DIV:
		outA = inA / inB;
		myState = PROCESSING;
		break;
	case BRA:
		cout<<"BRA\n";
		cout<<"InA: "<<inA<<endl;
		cout<<"InB: "<<inB<<endl;
		if(inInstruction -> getReg2() == NONE){
			//TODO: we need to insert bubbles
			std::cout<<inInstruction->getLabel()<<endl;
			int executeResult = MySim -> labels.at(inInstruction -> getLabel());
			MySim -> PC = executeResult-1;
			cout<<"FLUSHINGGGGG\n";
			MySim -> MyFetch -> flush();
			MySim -> MyDecode -> flush();
			myState = PROCESSING;
		}else if(inA == inB){
			//TODO: we need to insert bubbles
			int executeResult = MySim -> labels.at(inInstruction -> getLabel())-1;
			MySim -> PC = executeResult;
			MySim -> MyFetch -> flush();
			MySim -> MyDecode -> flush();
			myState = PROCESSING;
		}
		break;
	}	
	if(myState != STALLING){
		outInstruction = inInstruction;
	}else{
		outInstruction = NULL;
	}
	outB = inB;
}
