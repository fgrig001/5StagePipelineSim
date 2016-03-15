#include "Fetch.h"
#include <iostream>


Fetch::Fetch(Simulator *sim):
	MySim(sim),
	inInstruction(0),
	outInstruction(0)
{}

void Fetch::update(){
	if(MySim->PC+1 < MySim->instructionBuffer.size()){
		inInstruction = MySim->instructionBuffer.at(MySim->PC);
	}else{
		inInstruction = NULL;
	}
}

void Fetch::execute(){
	outInstruction = inInstruction;
	inInstruction = NULL;
}

void Fetch::print(){
	std::cout<<"Fetch-------------\n";
	if(inInstruction) inInstruction->print();
	else std::cout<<"inInstruction empty\n";
	if(outInstruction) outInstruction->print();
	else std::cout<<"outInstruction empty\n";
}
