#pragma once

#include <QPushButton>
#include <QMainWindow>
#include <QDockWidget>
#include <QListWidget>
#include <QCheckBox>


//! The main window for this application.
/*! This MainWindow class inherits from QMainWindow
	and is the primary application window in which
	all other widgets dock into. */
class MainWindow : public QMainWindow{
	public:
		explicit MainWindow(QMainWindow *parent=0);
	private:
		QListWidget *ListWidget;
		QPushButton *AddButton;
		QPushButton *RemoveButton;
		QPushButton *RunButton;
		QCheckBox *Box1;
		QCheckBox *Box2 ;
		QCheckBox *Box3;
		QCheckBox *Box4 ;
		QCheckBox *Box5;
};

