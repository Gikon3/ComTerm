#include "TabForm.h"
#include "ui_TabForm.h"

TabForm::TabForm(QSerialPort *port, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabForm),
    port(port)
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
