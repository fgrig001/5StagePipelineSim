#pragma once

#include <QPushButton>
#include <QMainWindow>
#include <QDockWidget>


//! The main window for this application.
/*! This MainWindow class inherits from QMainWindow
	and is the primary application window in which
	all other widgets dock into. */
class MainWindow : public QMainWindow{
	public:
		explicit MainWindow(QMainWindow *parent=0);
	private:
};

