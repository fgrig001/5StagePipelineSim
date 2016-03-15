#include <iostream>
#include "Instruction.h"
#include "Simulator.h"

using namespace std;

int main(){
	Simulator sim;
	sim.addInstruction(ADD,r1,r2,r3);
	sim.addInstruction(ADD,r1,r2,r3);
	sim.addInstruction(ADD,r1,r2,r3);
	sim.addInstruction(ADD,r1,r2,r3);
	sim.run();
}
