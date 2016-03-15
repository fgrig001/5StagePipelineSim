#include "Simulator.h"


Simulator::Simulator():
	PC(0),
	CYCLE(0),
	numRegisters(10),
	fullForwarding(false),
	registerBypassing(false),
	branchPredictedNotTaken(false)
{
	MyFetch = new Fetch(this);	
	MyDecode = new Decode (this);
	MyExecute = new Execute(this);
	MyMemAccess = new MemAccess(this);
	MyWriteback = new Writeback(this);
	registerStatus = new bool[numRegisters];
}

void Simulator::addInstruction(Instructions I, Registers reg1,Registers reg2, Registers reg3){
	instructionBuffer.push_back(new Instruction(I,reg1,reg2,reg3));
}

void Simulator::run(){
	while(1){
		MyFetch->print();
		MyFetch->update();
		MyDecode->update();
		MyExecute->update();
		MyMemAccess->update();
		MyWriteback->update();
		MyFetch->print();
		MyFetch->execute();
		MyDecode->execute();
		MyExecute->execute();
		MyMemAccess->execute();
		MyWriteback->execute();
		PC++;
		CYCLE++;	
	}
}
