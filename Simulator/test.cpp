#include <iostream>
#include "Instruction.h"
#include "Simulator.h"

using namespace std;

int main(){
	Simulator sim;
	/*
	sim.labels.insert(make_pair("bla",1));
	sim.addInstruction(ADD,r3,r2,NONE,3); // 1
	sim.addInstruction(ADD,r1,r2,NONE,2); // 4
	sim.addInstruction(ADD,r7,r4,r4); // 2
	sim.addInstruction(ADD,r8,r4,r4); // 3
	sim.addInstruction(ADD,r1,r2,NONE,1); // 4
	sim.addInstruction(ADD,r5,r4,r4); // 5
	sim.addInstruction(ADD,r6,r4,r4); // 6
	sim.addInstruction(ADD,r7,r4,r4); // 7
	sim.addInstruction(BRA,r1,r3,"bla"); // 8
	sim.addInstruction(SUB,r4,r1,r2); // 9
	*/
	sim.labels.insert(make_pair("bla",0));
	sim.addInstruction(ADD,r3,r2,NONE,3); // 1
	sim.addInstruction(ADD,r1,r2,NONE,3); // 1
	sim.addInstruction(ADD,r5,r5,r5); // 1
	sim.addInstruction(ADD,r5,r5,r5); // 1
	sim.addInstruction(ADD,r5,r5,r5); // 1
	sim.addInstruction(ADD,r5,r5,r5); // 1
	sim.addInstruction(BRA,r1,r3,"bla"); // 8
	sim.run();
}
