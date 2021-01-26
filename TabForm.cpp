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

void TabForm::sendButtonClicked()
{
    QByteArray array = QString(ui->txLline->text()).toUtf8();
    port->write(array);
    txAppend(array);
}
// -- slots

void TabForm::rxAppend(const QByteArray& array)
{
    if(!ui->pausePushButton->isChecked()) {
        ui->rxWidget->append(array);
    }
}

void TabForm::txAppend(const QByteArray& array)
{
    ui->txWidget->append(array);
}
