#pragma once

class Simulator;
class Fetch;
class Decode;
class Execute;
class MemAccess;
class Writeback;


#include "PipelineStage.h"
#include <vector>
#include <cstdlib>
#include "Instruction.h"
#include "Fetch.h"
#include "Decode.h"
#include "Execute.h"
#include "MemAccess.h"
#include "Writeback.h"

using namespace std;

class Simulator{
	public:
		Simulator();
		void addInstruction(Instructions I, 
							Registers reg1,
							Registers reg2, 
							Registers reg3);
		void addInstruction();
		void removeInstruction(int num);
		void run();
		// Pipline Stage Objects
		Fetch *MyFetch;
		Decode *MyDecode;
		Execute *MyExecute;
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
		int PC;
		int CYCLE;
	private:
};
