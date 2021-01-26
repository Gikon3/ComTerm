#include "ComTerm.h"
#include "ui_ComTerm.h"
#include "TabForm.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

ComTerm::ComTerm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ComTerm)
{
    ui->setupUi(this);
    ui->tabWidget->hide();
    updateFreePortList();
}

ComTerm::~ComTerm()
{
    delete ui;
}

// slots
void ComTerm::scanButtonClicked()
{
    updateFreePortList();
}

void ComTerm::connectButtonClicked()
{
    if(QSerialPort *port = openPort(ui->portsListComboBox->currentText())) {
        TabForm *tab = new TabForm(port);
        ui->tabWidget->addTab(tab, port->portName());
        openPortsList.insert(TabPortPair(tab, port));
        connect(port, &QSerialPort::readyRead, this, &ComTerm::handleReadyRead);
        if(ui->tabWidget->isHidden()) {
            ui->tabWidget->show();
        }
    }
}
// -- slots

void ComTerm::updateFreePortList()
{
    QString curPort = ui->portsListComboBox->currentText();
    ui->portsListComboBox->clear();
    for(const QSerialPortInfo& port: QSerialPortInfo().availablePorts()) {
        if(!port.isBusy()) {
            ui->portsListComboBox->addItem(port.portName());
        }
    }
    ui->portsListComboBox->setCurrentText(curPort);
}

QSerialPort* ComTerm::openPort(const QString& portName)
{
    QSerialPort *port = new QSerialPort();
    port->setPortName(portName);
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    if(port->open(QSerialPort::ReadWrite)) {
        return port;
    }
    delete port;
    QMessageBox::warning(this, "Warning", "Port " + portName + " is open");
    return nullptr;
}

void ComTerm::handleReadyRead()
{
    for(const TabPortPair& tabPort: openPortsList) {
        tabPort.first->append(tabPort.second->readAll());
    }
}
