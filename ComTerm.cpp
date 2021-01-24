#include "ComTerm.h"
#include "ui_ComTerm.h"

ComTerm::ComTerm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ComTerm)
{
    ui->setupUi(this);
}

ComTerm::~ComTerm()
{
    delete ui;
}

