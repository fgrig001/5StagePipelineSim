#include "Instruction.h"

Instruction::Instruction(){
	myInstruction = NOOP;
	myReg1 = NONE;
	myReg2 = NONE;
	myReg3 = NONE;
}

Instruction::Instruction(Instructions new_instruction,
						 Registers new_reg1,
						 Registers new_reg2,
						 Registers new_reg3):
	myInstruction(new_instruction),
	myReg1(new_reg1),
	myReg2(new_reg2),
	myReg3(new_reg3)
{
}

void Instruction::setInstruction(Instructions new_instruction){
	myInstruction = new_instruction;
}

void Instruction::setReg1(Registers new_reg){
	myReg1 = new_reg;
}

void Instruction::setReg2(Registers new_reg){
	myReg2 = new_reg;
}

void Instruction::setReg3(Registers new_reg){
	myReg3 = new_reg;
}


