#include <iostream>
#include "Instruction.h"
#include "Simulator.h"

using namespace std;

int main(){
	Simulator sim;
	/*
	sim.addInstruction(ADD,r3,r2,NONE,3); // 0
	sim.labels.insert(make_pair("bla",1));
	sim.addInstruction(ADD,r1,r1,NONE,1); // 1
	sim.addInstruction(BRA,r1,r3,"bla2"); // 2
	sim.addInstruction(BRA,NONE,NONE,"bla"); // 3
	sim.labels.insert(make_pair("bla2",4));
	sim.addInstruction(SUB,r4,r1,r2); // 4
	*/

	// testing branch predicted taken / not taken
	/*
	sim.labels.insert(make_pair("bla",1));
	sim.addInstruction(ADD,r3,r2,NONE,3);
	sim.addInstruction(ADD,r4,r4,NONE,3);
	//sim.addInstruction(ADD,r1,r1,NONE,1);
	sim.addInstruction(BRA,r3,r4,"bla");
	sim.addInstruction(MULT,r5,r4,r3);
	*/

	// testing branches resolve in id or ex
	sim.labels.insert(make_pair("bla",1));
	sim.addInstruction(ADD,r3,r2,NONE,3);
	sim.addInstruction(ADD,r4,r4,NONE,3);
	sim.addInstruction(BRA,r3,r4,"bla");
	sim.addInstruction(MULT,r5,r4,r3);
	

	/*	
	sim.labels.insert(make_pair("bla",0));
	sim.addInstruction(ADD,r3,r2,NONE,3); // 1
	sim.addInstruction(ADD,r1,r2,NONE,3); // 1
	sim.addInstruction(ADD,r5,r5,r5); // 1
	sim.addInstruction(ADD,r5,r5,r5); // 1
	sim.addInstruction(ADD,r5,r5,r5); // 1
	sim.addInstruction(ADD,r5,r5,r5); // 1
	sim.addInstruction(BRA,r1,r3,"bla"); // 8
	sim.run();
	*/
	/*
	sim.addInstruction(ADD,r3,r2,NONE,3); // 1
	sim.addInstruction(ADD,r5,r3,r3); // 1
	sim.addInstruction(ADD,r6,r5,r5);
	sim.run();
	*///sim.addInstruction(ADD,r5,r5,r5); // 1
	//sim.addInstruction(ADD,r5,r5,r5); // 1
	//sim.addInstruction(ADD,r5,r5,r5); // 1
	sim.run();
}
