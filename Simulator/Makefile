
Sim: test.cpp dotOh 
	g++ test.cpp *.o -o Sim

dotOh:
	g++ -c Simulator.cpp Instruction.cpp Fetch.cpp Decode.cpp Execute.cpp MemAccess.cpp Writeback.cpp 

clean:
	rm -fr Sim *.o 
