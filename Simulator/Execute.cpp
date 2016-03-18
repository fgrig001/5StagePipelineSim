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
	bool inASet = false;
	bool inBSet = false;
	if(MySim -> fullForwarding && inInstruction != NULL){
		switch(inInstruction -> getInstruction()){
		case ADD:
		case SUB:
		case MULT:
		case DIV:
		case LD:
			for(auto elem : MySim -> forwardedValues){
				if(inInstruction -> getReg2() == elem.first){
					inA = elem.second;
					inASet = true;
					//cout << "InASet" << endl;
				}
				if(inInstruction -> getReg3() == elem.first){
					inB = elem.second;
					inBSet = true;
					//cout << "InBSet" << endl;
				}
			}
			break;
		case ST:
		case BRA:
			for(auto elem : MySim -> forwardedValues){
				if(inInstruction -> getReg1() == elem.first){
					inA = elem.second;
					inASet = true;
					//cout << "InASet" << endl;
				}
				if(inInstruction -> getReg2() == elem.first){
					inB = elem.second;
					inBSet = true;
					//cout << "InBSet" << endl;
				}
			}
			break;
			
		}
			
	}
	if(!inASet)
		inA = MySim->MyDecode->outA;
	if(!inBSet)
		inB = MySim->MyDecode->outB;
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
		// If branches are resolved in EX
		if(!MySim -> branchesResolveInID){
			// If unconditional branch
			if(inInstruction -> getReg2() == NONE){
				//std::cout<<inInstruction->getLabel()<<endl;
				if(MySim->branchPredictedNotTaken){
					int executeResult = MySim -> labels.at(inInstruction -> getLabel());
					MySim -> PC = executeResult-1;
					//cout<<"FLUSHINGGGGG\n";
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
							//cout << "BRANCH PC = " << MySim -> PC;				
					}
					myState = PROCESSING;
				}
			}
		break;
	}
	if(inInstruction -> hasDestination()){
		//cout << "EX Forwarding : " << inInstruction->getReg1() << " val = " << outA << endl; 
		MySim -> forwardedValues.insert(make_pair(inInstruction->getReg1(), outA));
	}
	outInstruction = inInstruction;	
	if(myState == STALLING){
		outInstruction = NULL;
	}
	outB = inB;
}
