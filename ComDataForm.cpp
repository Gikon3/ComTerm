#include "ComDataForm.h"
#include "ui_ComDataForm.h"

ComDataForm::ComDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComDataForm)
{
    ui->setupUi(this);
}

ComDataForm::~ComDataForm()
{
    delete ui;
}
