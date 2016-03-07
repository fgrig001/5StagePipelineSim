#include "MainWindow.h"

MainWindow::MainWindow(QMainWindow *parent):
	QMainWindow(parent)
{	
	// Sets the main window's size be greater than the specified size.
	setMinimumSize(600,600); 
	// Set window properties	
	setWindowTitle("5 Stage Pipeline Simulator");

	// Initialize list widged and set properties
	ListWidget= new QListWidget(this);
	//setCentralWidget(ListWidget);
	//ListWidget->setMinimumSize(200,200);
	ListWidget->setGeometry(180,30,400,280);
	ListWidget->addItem("String1");
	ListWidget->addItem("String2");

	// Initialize add button and set properties
	AddButton = new QPushButton("Add Instruction", this);
	AddButton->setGeometry(10,30,140,30);

	// Initialize remove button and set properties
	RemoveButton = new QPushButton("Remove Instruction", this);
	RemoveButton->setGeometry(10,70,140,30);

	// Initialize run button and set properties
	RunButton = new QPushButton("Run Simulation", this);
	RunButton->setGeometry(10,270,140,30);

	// Initialize checkboxes
	Box1 = new QCheckBox("Box1",this);
	Box1->setGeometry(20,110,140,30);
	Box2 = new QCheckBox("Box2",this);
	Box2->setGeometry(20,140,140,30);
	Box3 = new QCheckBox("Box3",this);
	Box3->setGeometry(20,170,140,30);
	Box4 = new QCheckBox("Box4",this);
	Box4->setGeometry(20,200,140,30);
	Box5 = new QCheckBox("Box5",this);
	Box5->setGeometry(20,230,140,30);


}
