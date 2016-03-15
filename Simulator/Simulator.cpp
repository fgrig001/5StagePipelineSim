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
	instructionCount(0)
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

void Simulator::addInstruction(Instructions I, Registers reg1,Registers reg2, Registers reg3){
	instructionBuffer.push_back(new Instruction(I,reg1,reg2,reg3));
}

void Simulator::run(){
	while(PC<10){
		// Update pipeline stages
		MyWriteback->update();
		MyMemAccess->update();
		MyExecute->update();
		MyDecode->update();
		MyFetch->update();
		// Execute pipeline stages
		MyWriteback->execute();
		MyMemAccess->execute();
		MyExecute->execute();
		MyDecode->execute();
		MyFetch->execute();
		// Print pipeline stages
		std::cout<<"Cycle: "<<CYCLE<<"--------------\n";
		MyFetch->print();
		MyDecode->print();
		MyExecute->print();
		MyMemAccess->print();
		MyWriteback->print();
		std::cout<<std::endl;
		// Incriment CYCLE counter
		CYCLE++;	
	}
}
