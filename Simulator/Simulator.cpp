#include "Simulator.h"

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

Simulator::Simulator():
	PC(0),
	CYCLE(0),
	numRegisters(11),
	fullForwarding(false),
	registerBypassing(false),
	branchPredictedNotTaken(false),
	branchesResolveInID(true),
	branchesTakenIn(0),
	memory(memorySize, 0),
	instructionCount(0),
	busyRegisters(11)
{
	MyFetch = new Fetch(this);	
	MyDecode = new Decode (this);
	MyExecute = new Execute(this);
	MyMemAccess = new MemAccess(this);
	MyWriteback = new Writeback(this);
	registerStatus = new bool[numRegisters];
	for(int i = 0; i < numRegisters; ++i){
		registerVals.insert(make_pair(i, 0));
	}
}

void Simulator::addInstruction(Instructions I, 
							   Registers reg1,
							   Registers reg2, 
							   Registers reg3,
							   int reg_3_val)
{
	instructionBuffer.push_back(new Instruction(I,reg1,reg2,reg3,reg_3_val));				
}

void Simulator::addInstruction(Instructions I, 
							   Registers reg1,
							   Registers reg2, 
							   string label)
{
	instructionBuffer.push_back(new Instruction(I,reg1,reg2,label));				
}

void Simulator::run(){
	ofstream out_file("out_file");
	PC=0;
	CYCLE=0;
	registerVals.clear();
	for(int i = 0; i < numRegisters; ++i){
		registerVals.insert(make_pair(i, 0));
	}
	for(int i = 0; i < numRegisters-1; ++i){
		busyRegisters.at(i).clear();
	}

	// Flush Stages 
	MyFetch->flush();
	MyDecode->flush();
	MyExecute->flush();
	MyMemAccess->flush();
	MyWriteback->flush();

	MyWriteback->myState = PipelineStage::WAITING;
	MyMemAccess->myState = PipelineStage::WAITING;
	MyExecute->myState = PipelineStage::WAITING;
	MyDecode->myState = PipelineStage::WAITING;
	MyFetch->myState = PipelineStage::WAITING;
	
	for(int i=0;i<20;++i){

		// Update pipeline stages
		MyWriteback->update();
		MyMemAccess->update();
		MyExecute->update();
		MyDecode->update();
		MyFetch->update();

		// Execute pipeline stages
		forwardedValues.clear();
		MyWriteback->execute();
		MyMemAccess->execute();
		MyExecute->execute();
		MyDecode->execute();
		MyFetch->execute();
		
		// Print Colunm headders
		if(i == 0){
			out_file << setw(4) << "Cyc" 
				 << setw(4) << "F" 
				 << setw(4) << "D" 
				 << setw(4) << "E" 
				 << setw(4) << "M" 
				 << setw(4) << "W" << endl; 
		}
		out_file << setw(4) << CYCLE;

		// Print pipeline stages
		MyFetch->print2(out_file);
		MyDecode->print2(out_file);
		MyExecute->print2(out_file);
		MyMemAccess->print2(out_file);
		MyWriteback->print2(out_file);
		out_file<<std::endl;

		// Incriment CYCLE counter
		CYCLE++;	
	}
	// Print register vals
	out_file << std::endl;
	out_file << "r0 r1 r2 r3 r4 r5 r6 r7 r8 r9\n";
	for(int j = 0; j < registerVals.size()-1; ++j){
		out_file << registerVals[j] << ", ";
	}
	out_file << endl;

}


void Simulator::flushInstructionBuffer(){
	instructionCount = 0;	
	PC = 0;
	CYCLE = 0;
	while(!instructionBuffer.empty()){
		delete instructionBuffer.back();
		instructionBuffer.pop_back();
	}
}

void Simulator::parseInstructionFile(string file_name){
	labels.clear();
	flushInstructionBuffer();
	registerVals.clear();
	for(int i = 0; i < numRegisters; ++i){
		registerVals.insert(make_pair(i, 0));
	}
	
	// Open file
	ifstream in_file(file_name.c_str());	
	// Test for file open
	if(in_file.fail()){
		cout<<"Error opening file!\n";
		return;
	}
	string hold, opp, arg1, arg2, arg3;
	int instCount=0;
	// Read in file contents
	while(in_file>>hold){
		// If Option
		if(hold[0]=='$'){ 
		// If Label	
		}else if(hold[hold.size()-1]==':'){ 
			hold.pop_back();
			this -> labels.insert(make_pair(hold,instCount));
		// If Instruction
		}else{
			instCount++;
			if(hold == "ADD"){
				opp = hold;
				in_file>>arg1;
				in_file>>arg2;
				in_file>>arg3;
				if(arg3[0] == '#'){ // Imediate
					this -> addInstruction(ADD,
								(Registers)(arg1[1]-48),
								(Registers)(arg2[1]-48),
								NONE,
								(arg3[1]-48));
				}else{ // No imediate
					this -> addInstruction(ADD,
								(Registers)(arg1[1]-48),
								(Registers)(arg2[1]-48),
								(Registers)(arg3[1]-48));
				}
			}else if(hold == "SUB"){
				opp = hold;
				in_file>>arg1;
				in_file>>arg2;
				in_file>>arg3;
				if(arg3[0] == '#'){ // Imediate
					this -> addInstruction(SUB,
								(Registers)(arg1[1]-48),
								(Registers)(arg2[1]-48),
								NONE,
								(arg3[1]-48));
				}else{ // No imediate
					this -> addInstruction(SUB,
								(Registers)(arg1[1]-48),
								(Registers)(arg2[1]-48),
								(Registers)(arg3[1]-48));
				}
			}else if(hold == "MULT"){
				opp = hold;
				in_file>>arg1;
				in_file>>arg2;
				in_file>>arg3;
				if(arg3[0] == '#'){ // Imediate
					this -> addInstruction(MULT,
								(Registers)(arg1[1]-48),
								(Registers)(arg2[1]-48),
								NONE,
								(arg3[1]-48));
				}else{ // No imediate
					this -> addInstruction(MULT,
								(Registers)(arg1[1]-48),
								(Registers)(arg2[1]-48),
								(Registers)(arg3[1]-48));
				}
			}else if(hold == "DIV"){
				opp = hold;
				in_file>>arg1;
				in_file>>arg2;
				in_file>>arg3;
				if(arg3[0] == '#'){ // Imediate
					this -> addInstruction(DIV,
								(Registers)(arg1[1]-48),
								(Registers)(arg2[1]-48),
								NONE,
								(arg3[1]-48));
				}else{ // No imediate
					this -> addInstruction(DIV,
								(Registers)(arg1[1]-48),
								(Registers)(arg2[1]-48),
								(Registers)(arg3[1]-48));
				}
			}else if(hold == "LD"){
				opp = hold;
				in_file>>arg1;
				in_file>>arg2;
				in_file>>arg3;
				this -> addInstruction(LD,
							(Registers)(arg1[1]-48),
							(Registers)(arg2[1]-48),
							NONE,
							(arg3[1]-48));
			}else if(hold == "BRA"){
				opp = hold;
				in_file>>arg1;
				if(arg1.size() != 2){ // Unconditional
					this -> addInstruction(BRA,
										   NONE,
										   NONE,
										   arg1);
				}else{ // Conditional
					in_file>>arg2;
					in_file>>arg3;
					this -> addInstruction(BRA,
								(Registers)(arg1[1]-48),
								(Registers)(arg2[1]-48),
										   arg3);
				}
			}else if(hold == "ST"){
				opp = hold;
				in_file>>arg1;
				in_file>>arg2;
				in_file>>arg3;
				this -> addInstruction(ST,
							(Registers)(arg1[1]-48),
							(Registers)(arg2[1]-48),
							NONE,
							(arg3[1]-48));
			}
		}
	}
	return;
}
