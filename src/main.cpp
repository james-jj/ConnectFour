#include "application.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Application *application = new Application;
  return a.exec();
}
