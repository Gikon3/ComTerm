#include "ComTerm.h"
#include "ui_ComTerm.h"
#include "TabForm.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTabWidget>

ComTerm::ComTerm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ComTerm)
{
    ui->setupUi(this);
    ui->tabWidget->hide();
    updateFreePortList();
    baudRateList = {BaudRatePair(ui->baudRate1200RB, QSerialPort::Baud1200),
                    BaudRatePair(ui->baudRate2400RB, QSerialPort::Baud2400),
                    BaudRatePair(ui->baudRate4800RB, QSerialPort::Baud4800),
                    BaudRatePair(ui->baudRate9600RB, QSerialPort::Baud9600),
                    BaudRatePair(ui->baudRate19200RB, QSerialPort::Baud19200),
                    BaudRatePair(ui->baudRate38400RB, QSerialPort::Baud38400),
                    BaudRatePair(ui->baudRate57600RB, QSerialPort::Baud57600),
                    BaudRatePair(ui->baudRate115200RB, QSerialPort::Baud115200)};
    dataBitsList = {DataBitsPair(ui->dataBits5RB, QSerialPort::Data5),
                    DataBitsPair(ui->dataBits6RB, QSerialPort::Data6),
                    DataBitsPair(ui->dataBits7RB, QSerialPort::Data7),
                    DataBitsPair(ui->dataBits8RB, QSerialPort::Data8)};
    parityList = {ParityPair(ui->parityNoneRB, QSerialPort::NoParity),
                  ParityPair(ui->parityEvenRB, QSerialPort::EvenParity),
                  ParityPair(ui->parityOddRB, QSerialPort::OddParity),
                  ParityPair(ui->paritySpaceRB, QSerialPort::SpaceParity),
                  ParityPair(ui->parityMarkRB, QSerialPort::MarkParity)};
    stopBitsList = {StopBitsPair(ui->stopBits1RB, QSerialPort::OneStop),
                    StopBitsPair(ui->stopBits15RB, QSerialPort::OneAndHalfStop),
                    StopBitsPair(ui->stopBits2RB, QSerialPort::TwoStop)};
    flowControlList = {FlowControlPair(ui->flowControlNoRB, QSerialPort::NoFlowControl),
                       FlowControlPair(ui->flowControlHardRB, QSerialPort::HardwareControl),
                       FlowControlPair(ui->flowControlSoftRB, QSerialPort::SoftwareControl)};
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
    QSerialPortInfo info = getPortParam();
    bool ok;
    TabForm *tab = new TabForm(info, &ok, this);
    if(ok) {
        ui->tabWidget->addTab(tab, info.portName());
        if(ui->tabWidget->isHidden()) {
            setMinimumHeight(minimumHeight() + heighTab);
            ui->tabWidget->show();
        }
    }
    else {
        QMessageBox::warning(this, "Warning", "Failed to open port " + info.portName());
        delete tab;
    }
    updateFreePortList();
}

void ComTerm::tabClose(int index)
{
    delete ui->tabWidget->widget(index);
    if(!ui->tabWidget->count()) {
        ui->tabWidget->hide();
        setMinimumHeight(minimumHeight() - heighTab);
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

QSerialPortInfo ComTerm::getPortParam()
{
    QSerialPort port(ui->portsListComboBox->currentText());
    for(const BaudRatePair &baud: baudRateList) {
        if(baud.first->isChecked()) {
            port.setBaudRate(baud.second);
            break;
        }
    }
    for(const DataBitsPair &data: dataBitsList) {
        if(data.first->isChecked()) {
            port.setDataBits(data.second);
            break;
        }
    }
    for(const ParityPair &parity: parityList) {
        if(parity.first->isChecked()) {
            port.setParity(parity.second);
            break;
        }
    }
    for(const StopBitsPair &stop: stopBitsList) {
        if(stop.first->isChecked()) {
            port.setStopBits(stop.second);
            break;
        }
    }
    for(const FlowControlPair &flow: flowControlList) {
        if(flow.first->isChecked()) {
            port.setFlowControl(flow.second);
            break;
        }
    }
    return QSerialPortInfo(port);
}
