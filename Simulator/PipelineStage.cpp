#include <iostream>
#include <string>

#include "PipelineStage.h"

PipelineStage::PipelineStage(Simulator *sim):
	MySim(sim),
	inInstruction(NULL),
	outInstruction(NULL),
	myState(WAITING)
{}

void PipelineStage::print(){
/*
	std::cout<< name + "-------------\n";
	if(inInstruction) inInstruction->print();
	else std::cout<<"inInstruction empty\n";
	if(outInstruction) outInstruction->print();
	else std::cout<<"outInstruction empty\n";
*/
	switch(myState){
		case STALLING:
			if(inInstruction == NULL){
				std::cout<<name<<"ERROR STALLING"<<std::endl;
			}
			std::cout<<name<<": Stalling instruction "<<inInstruction->instructionNumber<<endl;
			break;
		case PROCESSING:
			if(outInstruction == NULL){
				std::cout<<name<<" ERROR!\n";
				return;
			}
			std::cout<<name<<": Processing instruction "<<outInstruction->instructionNumber<<endl;
			break;
		case WAITING:
			std::cout<<name<<": Waiting for instruction\n";
			break;
	}
}
