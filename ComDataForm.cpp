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

void ComDataForm::asciiComboBoxClicked(bool check)
{
    if(check) {
        ui->asciiText->show();
        return;
    }
    ui->asciiText->hide();
}

void ComDataForm::hexComboBoxClicked(bool check)
{
    if(check) {
        ui->hexText->show();
        return;
    }
    ui->hexText->hide();
}
