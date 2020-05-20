#include "EternalModManager.h"
#include "GameSelection.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//EternalModManager w;
	//w.show();
	GameSelection g;
	g.show();
	return a.exec();
}
