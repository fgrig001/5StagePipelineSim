#include "Simulator.h"

#include<iostream>
using namespace std;

Simulator::Simulator():
	PC(0),
	CYCLE(0),
	numRegisters(10),
	fullForwarding(false),
	registerBypassing(false),
	branchPredictedNotTaken(false),
	memory(memorySize, 0),
	instructionCount(0),
	busyRegisters(10)
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
	//while(PC<10){
	for(int i=0;i<30;++i){
		// Update pipeline stages
		MyWriteback->update();
		cout << "A" << endl;
		MyMemAccess->update();
		cout << "B" << endl;
		MyExecute->update();
		cout << "C" << endl;
		MyDecode->update();
		cout << "D" << endl;
		MyFetch->update();
		cout << "E" << endl;
		// Execute pipeline stages
		MyWriteback->execute();
		cout << "F" << endl;
		MyMemAccess->execute();
		cout << "G" << endl;
		MyExecute->execute();
		cout << "H" << endl;		
		MyDecode->execute();
		cout << "I" << endl;
		MyFetch->execute();
		cout << "J" << endl;
		// Print pipeline stages
		std::cout<<"Cycle: "<<CYCLE<<"--------------\n";
		std::cout<<"PC: "<<PC<<"--------------\n";
		MyFetch->print();
		MyDecode->print();
		MyExecute->print();
		MyMemAccess->print();
		MyWriteback->print();
		std::cout<<std::endl;
		cout << "Register Values" << endl;
		for(int j = 0; j < registerVals.size(); ++j){
			cout << registerVals[j] << ", ";
		}
		cout << endl;
		// Incriment CYCLE counter
		CYCLE++;	
	}
}
