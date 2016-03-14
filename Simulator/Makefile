
Sim: test.cpp Simulator.o Instruction.o Fetch.o Decode.o Execute.o MemAccess.o Writeback.o 
	g++ test.cpp Instruction.o Fetch.o -o Sim

Simulator.o: Simulator.h Simulator.cpp
	g++ -c Simulator.cpp

Instruction.o: Instruction.h Instruction.cpp
	g++ -c Instruction.cpp

Fetch.o: Fetch.h Fetch.cpp
	g++ -c Fetch.cpp

Decode.o: Decode.h Decode.cpp
	g++ -c Decode.cpp

Execute.o: Execute.h Execute.cpp
	g++ -c Execute.cpp

MemAccess.o: MemAccess.h MemAccess.cpp
	g++ -c MemAccess.cpp

Writeback.o: Writeback.h Writeback.cpp
	g++ -c Writeback.cpp

clean:
	rm -fr Sim *.o 
