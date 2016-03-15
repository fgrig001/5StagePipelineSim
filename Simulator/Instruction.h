#pragma once

#include <string>

using namespace std;

enum Instructions{ADD, SUB, MULT, DIV, BRA, LD, ST, NOOP};
enum Registers{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, NONE};

class Instruction{
	public:
		Instruction();
		Instruction(Instructions new_instruction,
					Registers new_reg1,
					Registers new_reg2,
					Registers new_reg3,
					string new_label);
		Instruction(Instructions new_instruction,
					Registers new_reg1,
					Registers new_reg2,
					Registers new_reg3);
		void setInstruction(Instructions new_instruction);
		void setReg1(Registers new_reg);
		void setReg2(Registers new_reg);
		void setReg3(Registers new_reg);
		void setLabel(string new_label);
		void print();
		Registers getReg1(){return myReg1;}
		Registers getReg2(){return myReg2;}
		Registers getReg3(){return myReg3;}
		string getLabel(){return label;}
		Instructions getInstruction(){return myInstruction;}
		int instructionNumber;
	private:
		string label;
		Instructions myInstruction;
		Registers myReg1;
		Registers myReg2;
		Registers myReg3;
};
