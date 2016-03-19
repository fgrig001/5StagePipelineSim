#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(QMainWindow *parent):
	QMainWindow(parent)
{	
	// Set MainWindow properties	
	setMinimumSize(450,650); 
	setWindowTitle("5 Stage Pipeline Simulator");

	// Initialize output text editor and set properties
	OutputTextWindow = new QTextEdit(this);
	OutputTextWindow->setGeometry(10,380,430,280);
	QFont font("Courier");
	font.setStyleHint(QFont::Monospace);
	OutputTextWindow->setFont(font);

	// Initialize input list widget and set properties
	InputListWidget= new QListWidget(this);
	InputListWidget->setGeometry(180,30,250,300);

	// Initialize load button and set properties
	LoadButton = new QPushButton("Load Instructions", this);
	LoadButton->setGeometry(10,30,140,30);
	connect(LoadButton,SIGNAL (released()),this,SLOT (handleLoadButton()));

	// Initialize clear instructions button and set properties
	ClearButton = new QPushButton("Clear Instructions", this);
	ClearButton->setGeometry(10,70,140,30);
	connect(ClearButton,SIGNAL (released()),this,SLOT (handleClearButton()));

	// Initialize run button and set properties
	RunButton = new QPushButton("Run Simulation", this);
	RunButton->setGeometry(10,130,140,30);
	connect(RunButton,SIGNAL (released()),this,SLOT (handleRunButton()));

	
	// Initialize branch prediction box and set properties
	BranchPredictionLabel = new QLabel("Branches Predicted",this);
	BranchPredictionLabel->setGeometry(15,170,140,30);
	BranchPredictionBox = new QComboBox(this);
	BranchPredictionBox->setGeometry(10,195,140,30);
	BranchPredictionBox->addItem("Taken");
	BranchPredictionBox->addItem("Not Taken");
	connect(BranchPredictionBox,SIGNAL(currentIndexChanged(int)),
		    this,SLOT(BranchPredictionChanged(int)));

	// Initialize branch taken box and set properties
	BranchTakenLabel = new QLabel("Branches Taken",this);
	BranchTakenLabel->setGeometry(15,230,140,30);
	BranchTakenBox = new QComboBox(this);
	BranchTakenBox->setGeometry(10,255,140,30);
	BranchTakenBox->addItem("Fetch");
	BranchTakenBox->addItem("Decode");
	BranchTakenBox->addItem("Execute");
	connect(BranchTakenBox,SIGNAL(currentIndexChanged(int)),
		    this,SLOT(BranchTakenChanged(int)));

	// Initialize branch resolved box and set properties
	BranchResolvedLabel = new QLabel("Branches Resolved",this);
	BranchResolvedLabel->setGeometry(15,290,140,30);
	BranchResolvedBox = new QComboBox(this);
	BranchResolvedBox->setGeometry(10,315,140,30);
	BranchResolvedBox->addItem("Decode");
	BranchResolvedBox->addItem("Execute");
	connect(BranchResolvedBox,SIGNAL(currentIndexChanged(int)),
		    this,SLOT(BranchResolvedChanged(int)));

	NumCyclesLabel = new QLabel("20 Cycles",this);
	NumCyclesLabel->setGeometry(15,105,140,30);
	captureText = new QPushButton("Set Cycles", this);
	captureText->setGeometry(10, 350, 100, 30);
	numCyclesBox = new QLineEdit("", this);
	numCyclesBox->setGeometry(120, 350, 100, 30);
	connect(captureText,SIGNAL(clicked()),this, SLOT(handleNumCyclesButton()));

}


void MainWindow::handleClearButton(){
	Sim.flushInstructionBuffer();	
	InputListWidget->clear();
}

void MainWindow::handleNumCyclesButton(){
	unsigned int x = numCyclesBox->text().toUInt();
	if(x > 0){
		Sim.numCycles = x;
	}	
	numCyclesBox->clear();
	
	NumCyclesLabel -> setText(tr((to_string(Sim.numCycles) + " Cycles").c_str()));
	
	
}

void MainWindow::handleLoadButton(){
	fileName = QFileDialog::getOpenFileName(this,tr("Open Code File"),"./InstructionFiles");
	Sim.parseInstructionFile(fileName.toStdString());
	ifstream in_file(fileName.toStdString());
	char str[255];
	while(in_file.getline(str,255)){
		QString qstr = QString::fromStdString(str);
		InputListWidget->addItem(qstr);
	}
}

void MainWindow::handleRunButton(){
	OutputTextWindow->clear();
	Sim.run();
	ifstream in_file("out_file");
	char str[255];
	while(in_file.getline(str,255)){
		QString qstr = QString::fromStdString(str);
		OutputTextWindow->append(qstr);
	}
}

void MainWindow::BranchPredictionChanged(int new_val){
	Sim.branchPredictedNotTaken = new_val;
}

void MainWindow::BranchResolvedChanged(int new_val){
	Sim.branchesResolveInID = !new_val;
}

void MainWindow::BranchTakenChanged(int new_val){
	Sim.branchesTakenIn = new_val;
}



