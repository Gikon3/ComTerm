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

void TabForm::rxClearPushButtonClicked()
{
    ui->rxWidget->clear();
}

void TabForm::txClearPushButtonClicked()
{
    ui->txWidget->clear();
}

void TabForm::rxCheckBoxClicked(bool check)
{
    if(check) {
        ui->rxWidget->show();
        ui->rxClearPushButton->show();
        ui->pausePushButton->show();
        return;
    }
    ui->rxWidget->hide();
    ui->rxClearPushButton->hide();
    ui->pausePushButton->hide();
}

void TabForm::txCheckBoxClicked(bool check)
{
    if(check) {
        ui->txWidget->show();
        ui->txClearPushButton->show();
        ui->txLline->show();
        ui->sendPushButton->show();
        return;
    }
    ui->txWidget->hide();
    ui->txClearPushButton->hide();
    ui->txLline->hide();
    ui->sendPushButton->hide();
}
