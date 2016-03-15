#include "MemAccess.h"


MemAccess::MemAccess(Simulator *sim):
	MySim(sim),
	inInstruction(NULL),
	outInstruction(NULL)
{}

void MemAccess::update(){
	inInstruction = MySim->MyExecute->outInstruction;
}

void MemAccess::execute(){
	outInstruction = inInstruction;
}
