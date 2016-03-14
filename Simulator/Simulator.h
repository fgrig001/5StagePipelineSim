#pragma once

#include "Fetch.h"
#include "Decode.h"
#include "Execute.h"
#include "MemAccess.h"
#include "Writeback.h"

class Simulator{
	public:
		Simulator();
	private:
		Fetch *MyFetch;
		Decode *MyDecode;
		Execute *MyEcecute;
		MemAccess *MyMemAccess;
		Writeback *MyWriteback;
};
