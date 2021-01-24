#include "TabForm.h"
#include "ui_TabForm.h"

TabForm::TabForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabForm)
{
    ui->setupUi(this);
}

TabForm::~TabForm()
{
    delete ui;
}
