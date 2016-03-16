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
#include <map>
#include <string>
#include "Instruction.h"
#include "Fetch.h"
#include "Decode.h"
#include "Execute.h"
#include "MemAccess.h"
#include "Writeback.h"

using namespace std;
const int memorySize = 1000;
class Simulator{
	public:
		
		Simulator();
		void addInstruction(Instructions I, 
							Registers reg1,
							Registers reg2, 
							Registers reg3,
							int reg_3_val=0);
		void addInstruction(Instructions I, 
							Registers reg1,
							Registers reg2, 
							string label);
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
		map<string, int> labels;
		map<int, int> registerVals;
		vector<int> busyRegisters;
		vector<int> memory;
		int instructionCount;
		int PC;
		int CYCLE;
	private:
};
