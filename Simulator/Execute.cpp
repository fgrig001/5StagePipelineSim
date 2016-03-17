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
	// Get new instruction
	inInstruction = MySim->MyDecode->outInstruction;
	// Get input values
	//if(MySim -> fullForwarding){
	//	if


	//}else{ 
		inA = MySim->MyDecode->outA;
		inB = MySim->MyDecode->outB;
	//}
	forwardedValues.clear();
}

void Execute::execute(){
	// Test for valid in instruction
	if(inInstruction == NULL){
		outA = 0;
		outB = 0;
		outInstruction = NULL;
		myState = WAITING;
		return;
	}
	//cout<<"Instruction: "<<inInstruction->getInstruction()<<endl;
	switch(inInstruction -> getInstruction()){
	case ADD:
		outA = inA + inB;
		myState = PROCESSING;
		break;	
	case LD:
	case ST:
		outA = inA + inInstruction -> reg3Val;
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
		// If branches are resolved in EX
		if(!MySim -> branchesResolveInID){
			// If unconditional branch
			if(inInstruction -> getReg2() == NONE){
				std::cout<<inInstruction->getLabel()<<endl;
				if(MySim->branchPredictedNotTaken){
					int executeResult = MySim -> labels.at(inInstruction -> getLabel());
					MySim -> PC = executeResult-1;
					cout<<"FLUSHINGGGGG\n";
					MySim -> MyFetch -> flush();
					MySim -> MyDecode -> flush();
				}
				myState = PROCESSING;
			// If conditional branch (and taken)
			}else if(inA == inB){
					if(MySim->branchPredictedNotTaken){
						int executeResult = MySim -> labels.at(inInstruction -> getLabel());
						MySim -> PC = executeResult-1;
						MySim -> MyFetch -> flush();
						MySim -> MyDecode -> flush();
					}
					myState = PROCESSING;
				// If conditional branch (and not taken)
				}else if(inA != inB){
					if(!MySim->branchPredictedNotTaken){
						MySim -> MyFetch -> flush();
						MySim -> MyDecode -> flush();
						MySim -> PC = inInstruction -> instructionNumber-1;			
							cout << "BRANCH PC = " << MySim -> PC;				
					}
					myState = PROCESSING;
				}
			}
	
		break;
	}
	outInstruction = inInstruction;	
	if(myState == STALLING){
		outInstruction = NULL;
	}
	outB = inB;
}
