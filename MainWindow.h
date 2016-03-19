#pragma once

#include <QPushButton>
#include <QMainWindow>
#include <QDockWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QFileDialog>
#include <QString>
#include <sstream>
#include <QTextEdit>
#include <fstream>
#include <QFont>
#include "Simulator/Simulator.h"


//! The main window for this application.
/*! This MainWindow class inherits from QMainWindow
	and is the primary application window in which
	all other widgets dock into. */
class MainWindow : public QMainWindow{
	Q_OBJECT
	public:
		explicit MainWindow(QMainWindow *parent=0);
		/*TextBoxSetup(QWidget *p = 0): QWidget(p)
		{
			numCyclesBox = new QLineEdit(tr("Insert text"));
			captureText = new QPushButton(tr("CaptureText"));
			connect(captureText,SIGNAL(clicked()),this, SLOT(storeText()));

			QVBoxLayout *layout = new QVBoxLayout();
			layout->addWidget(textUser);
			layout->addWidget(captureText);
			setLayout(layout);

		}*/
	private slots:
		void BranchPredictionChanged(int new_val);
		void BranchResolvedChanged(int new_val);
		void BranchTakenChanged(int new_val);
		void handleNumCyclesButton();
		void handleClearButton();
		void handleLoadButton();	
		void handleRunButton();
	private:
		// List widgets
		QListWidget *InputListWidget;
		QTextEdit *OutputTextWindow;

		// Push Buttons
		QPushButton *ClearButton;
		QPushButton *LoadButton;
		QPushButton *RunButton;
		QPushButton *captureText;
		QLineEdit *numCyclesBox;

		// Labels and combo box coices
		QLabel *NumCyclesLabel;
		QLabel *BranchPredictionLabel;
		QComboBox *BranchPredictionBox;

		QLabel *BranchTakenLabel;
		QComboBox *BranchTakenBox;

		QLabel *BranchResolvedLabel;
		QComboBox *BranchResolvedBox;
		
		// 5 Stage Pipeline simulator
		Simulator Sim;

		QString fileName;
};


