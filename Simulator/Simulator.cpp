#include "Simulator.h"


Sumulator::Simulator():
	numRegisters(10),
	fullForwarding(false),
	registerBypassing(false),
	branchPredictedNotTaken(false)
{
	MyFetch = new Fetch();	
	MyDecode = new Decode ();
	MyEcecute = new Execute();
	MyMemAccess = new MemAccess();
	MyWriteback = new Writeback();
	registerStatus = new bool[numRegisters];
}
