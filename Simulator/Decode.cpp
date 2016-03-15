#include "Decode.h"


Decode::Decode(Simulator *sim):
	MySim(sim),
	inInstruction(NULL),
	outInstruction(NULL)
{}

void Decode::update(){
	inInstruction = MySim->MyFetch->outInstruction;
}

void Decode::execute(){
	outInstruction = inInstruction;
}
