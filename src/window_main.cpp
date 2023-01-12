#include "window_main.h"
#include "./ui_window_main.h"

WindowMain::WindowMain(QWidget *parent): QMainWindow(parent), ui(new Ui::WindowMain) {
    ui->setupUi(this);
}

WindowMain::~WindowMain() {
    delete ui;
}

