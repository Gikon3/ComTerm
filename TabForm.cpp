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

// slots
void TabForm::rxClearPushButtonClicked()
{
    ui->rxWidget->clear();
}

void TabForm::txClearPushButtonClicked()
{
    ui->txWidget->clear();
}
// -- slots

void TabForm::append(const QByteArray& array)
{
    if(!ui->pausePushButton->isChecked()) {
        ui->rxWidget->append(array);
    }
}
