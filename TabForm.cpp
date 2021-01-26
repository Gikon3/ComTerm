#include "TabForm.h"
#include "ui_TabForm.h"

TabForm::TabForm(const QSerialPortInfo &info, bool *ok, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabForm)
{
    ui->setupUi(this);
    port = new QSerialPort(info, this);
    *ok = port->open(QSerialPort::ReadWrite);
    if(*ok) {
        connect(port, &QSerialPort::readyRead, this, &TabForm::handleReadyRead);
    }
}

TabForm::~TabForm()
{
    port->close();
    delete port;
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

void TabForm::txAppend(const QByteArray& array)
{
    ui->txWidget->append(array);
}

void TabForm::handleReadyRead()
{
    if(!ui->pausePushButton->isChecked()) {
        ui->rxWidget->append(port->readAll());
    }
    else {
        port->readAll();
    }
}

void TabForm::retranslate()
{
    ui->retranslateUi(this);
    ui->rxWidget->retranslate();
    ui->txWidget->retranslate();
}
