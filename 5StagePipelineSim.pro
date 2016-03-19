CONFIG += c++11

TARGET = 5StagePipelineSim

INCLUDEPATH += .

QT += core gui
QT += widgets

HEADERS += MainWindow.h \
	Simulator/Decode.h \
	Simulator/Execute.h \
	Simulator/Fetch.cpp \
	Simulator/Fetch.h \
	Simulator/Instruction.h \
	Simulator/MemAccess.h \
	Simulator/PipelineStage.h \
	Simulator/Simulator.h \
	Simulator/Writeback.h 

SOURCES += MainWindow.cpp \
	main.cpp \
	Simulator/Decode.cpp \
	Simulator/Execute.cpp \
	Simulator/Fetch.cpp \
	Simulator/Instruction.cpp \
	Simulator/MemAccess.cpp \
	Simulator/PipelineStage.cpp \
	Simulator/Simulator.cpp \
	Simulator/Writeback.cpp 
