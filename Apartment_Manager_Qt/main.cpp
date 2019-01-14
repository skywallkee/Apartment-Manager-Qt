#include "Apartment_Manager_Qt.h"
#include "UI.h"
#include "test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	test();
	QApplication a(argc, argv);
	FileRepo repo{ "apartamente.txt" };
	Service sv{ repo };
	Apartment_Manager_Qt w{ sv };
	w.show();
	return a.exec();
	//UI ui{ sv };
	//ui.run();
	//return 0;
}


