#include "MainWindow.h"

MainWindow::MainWindow(QMainWindow *parent):
	QMainWindow(parent)
{	
	// Sets the main window's size be greater than the specified size.
	setMinimumSize(600,600); 
	// Set window properties	
	setWindowTitle("5 Stage Pipeline Simulator");
}
