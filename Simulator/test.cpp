#include <iostream>
#include "Instruction.h"

using namespace std;

int main(){
	Instruction inst(ADD,r3,r6,r7);
	inst.setInstruction(ADD);
	cout<<inst.getInstruction()<<endl;
}
