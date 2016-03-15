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
	memory(memorySize, 0)
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
	while(1){
		//MyFetch->print();
		//cout << "running update fetch" << endl;
		MyFetch->update();
		//cout << "running update decode" << endl;
		MyDecode->update();
		//cout << "running update ex" << endl;
		MyExecute->update();
		//cout << "running update mem" << endl;
		MyMemAccess->update();
		//cout << "running update wb" << endl;
		MyWriteback->update();
		//MyFetch->print();
		//cout << "running execute fetch" << endl;
		MyFetch->execute();
		//cout << "running execute decode" << endl;
		MyDecode->execute();
		//cout << "running execute ex" << endl;
		MyExecute->execute();
		//cout << "running execute mem" << endl;		
		MyMemAccess->execute();
		//cout << "running execute wb" << endl;
		MyWriteback->execute();
		CYCLE++;	
	}
}
