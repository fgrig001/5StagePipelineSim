#include <iostream>
#include "Instruction.h"
#include "Simulator.h"

using namespace std;

int main(){
	Simulator sim;
	sim.addInstruction(ADD,r1,r2,r3);
	sim.addInstruction(SUB,r4,r5,r6);
	sim.run();
}
