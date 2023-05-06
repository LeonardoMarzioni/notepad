/**
* Software entry point.
*
* @author Marzioni Leonardo
* @version 0.9.2 [beta]
*
*/

#include <QApplication.h>
#include <QProcess>

#include "MainWindow.h"
#include "Corrector.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainWindow* win = new MainWindow();
	win->show();

	app.exec();

	delete win;
	return EXIT_SUCCESS;
}