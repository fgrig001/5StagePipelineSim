
Sim: test.cpp dotOh 
	g++ -std=c++0x -ggdb test.cpp *.o -o Sim

dotOh:
	g++ -std=c++0x -ggdb -c  Simulator.cpp Instruction.cpp Fetch.cpp Decode.cpp Execute.cpp MemAccess.cpp Writeback.cpp PipelineStage.cpp 

clean:
	rm -fr Sim *.o 
