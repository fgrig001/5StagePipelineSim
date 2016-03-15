#include <iostream>
#include <string>

#include "PipelineStage.h"

PipelineStage::PipelineStage(Simulator *sim):
	MySim(sim),
	inInstruction(NULL),
	outInstruction(NULL)
{}

void PipelineStage::print(){
	std::cout<< name + "-------------\n";
	if(inInstruction) inInstruction->print();
	else std::cout<<"inInstruction empty\n";
	if(outInstruction) outInstruction->print();
	else std::cout<<"outInstruction empty\n";
}
