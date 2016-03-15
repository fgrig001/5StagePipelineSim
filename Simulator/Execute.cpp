#include "Execute.h"


Execute::Execute(Simulator *sim):
	MySim(sim),
	inInstruction(NULL),
	outInstruction(NULL)
{}

void Execute::update(){
	inInstruction = MySim->MyDecode->outInstruction;
}

void Execute::execute(){
	outInstruction = inInstruction;
}
