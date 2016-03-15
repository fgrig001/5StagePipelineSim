#include "Fetch.h"
#include "PipelineStage.h"
#include <iostream>
#include <string>

Fetch::Fetch(Simulator *sim):
	PipelineStage(sim)
{
	name = "Fetch";
}

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
