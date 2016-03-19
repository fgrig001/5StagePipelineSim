#pragma once

#include <QPushButton>
#include <QMainWindow>
#include <QDockWidget>
#include <QListWidget>
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
	private slots:
		void BranchPredictionChanged(int new_val);
		void BranchResolvedChanged(int new_val);
		void BranchTakenChanged(int new_val);
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

		// Labels and combo box coices
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


