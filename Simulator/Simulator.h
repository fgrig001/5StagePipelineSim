#pragma once

#include <vector>
#include "Instruction.h"
#include "Fetch.h"
#include "Decode.h"
#include "Execute.h"
#include "MemAccess.h"
#include "Writeback.h"

class Simulator{
	public:
		Simulator();
		void addInstruction();
		void removeInstruction(int num);
	private:
		// Pipline Stage Objects
		Fetch *MyFetch;
		Decode *MyDecode;
		Execute *MyEcecute;
		MemAccess *MyMemAccess;
		Writeback *MyWriteback;
		// Instruction Buffer 
		vector<Instruction*> instructionBuffer;
		// Register status array
		bool *registerStatus;	
		// The number of total registers
		int numRegisters;
		// Pipline Configuration Featur States
		bool fullForwarding;
		bool registerBypassing;
		bool branchPredictedNotTaken;
		// TODO: add these configurations (non binary options?)
		/* - Stage where branches are taken
		   - Stage where branches are resloved */
};
