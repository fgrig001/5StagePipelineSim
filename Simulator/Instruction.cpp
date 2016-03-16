#include "Instruction.h"
#include <iostream>
#include <string>
using namespace std;

Instruction::Instruction(){
	myInstruction = NOOP;
	myReg1 = NONE;
	myReg2 = NONE;
	myReg3 = NONE;
	label = "";
	instructionNumber = -1;
	cout<<"construct 1\n";
}

Instruction::Instruction(Instructions new_instruction,
						 Registers new_reg1,
						 Registers new_reg2,
						 string new_label):
	myInstruction(new_instruction),
	myReg1(new_reg1),
	myReg2(new_reg2),
	label(new_label),
	instructionNumber(-1)
{
		cout<<"construct 2\n";
}

Instruction::Instruction(Instructions new_instruction,
						 Registers new_reg1,
						 Registers new_reg2,
						 Registers new_reg3,
						 int reg_3_val):
	myInstruction(new_instruction),
	myReg1(new_reg1),
	myReg2(new_reg2),
	myReg3(new_reg3),
	reg3Val(reg_3_val),
	label(""),
	instructionNumber(-1)
{
		cout<<"construct 3\n";
}

void Instruction::print(){
	cout<<myInstruction<<" "
		<<myReg1<<" "
		<<myReg2<<" "
		<<myReg3<<endl;
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

void Instruction::setLabel(string new_label){
	label = new_label;
}
