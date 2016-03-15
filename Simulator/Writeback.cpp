#include "Writeback.h"

Writeback::Writeback(Simulator *sim):
	MySim(sim),
	inInstruction(NULL),
	outInstruction(NULL)
{}

void Writeback::update(){
	inInstruction = MySim->MyMemAccess->outInstruction;
}

void Writeback::execute(){
	outInstruction = inInstruction;
}
