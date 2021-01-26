#include "ComTerm.h"
#include "ui_ComTerm.h"
#include "TabForm.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTabWidget>

ComTerm::ComTerm(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::ComTerm)
{
    ui->setupUi(this);
    portSetting = new PortSetting(this);
    ui->tabWidget->hide();
    updateFreePortList();
}

ComTerm::~ComTerm()
{
    delete portSetting;
    delete ui;
}

// slots
void ComTerm::scanButtonClicked()
{
    updateFreePortList();
}

void ComTerm::connectButtonClicked()
{
    QString toolTipStr;
    QSerialPortInfo info = getPortParam(&toolTipStr);
    bool ok;
    TabForm *tab = new TabForm(info, &ok, this);
    if(ok) {
        ui->tabWidget->addTab(tab, info.portName());
        if(ui->tabWidget->isHidden()) {
            setMinimumHeight(minimumHeight() + heighTab);
            ui->tabWidget->show();
        }
        ui->tabWidget->setTabToolTip(ui->tabWidget->count() - 1, toolTipStr);
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
    updateFreePortList();
}

void ComTerm::aboutWindowShow()
{
    QMessageBox::about(this, "About", "Test");
}

void ComTerm::aboutQtWindowShow()
{
    QMessageBox::aboutQt(this, "About Qt");
}
// -- slots

ComTerm::PortSetting::PortSetting(ComTerm* parent)
{
    baudRate = {BaudRatePair(parent->ui->baudRate1200RB, QSerialPort::Baud1200),
                BaudRatePair(parent->ui->baudRate2400RB, QSerialPort::Baud2400),
                BaudRatePair(parent->ui->baudRate4800RB, QSerialPort::Baud4800),
                BaudRatePair(parent->ui->baudRate9600RB, QSerialPort::Baud9600),
                BaudRatePair(parent->ui->baudRate19200RB, QSerialPort::Baud19200),
                BaudRatePair(parent->ui->baudRate38400RB, QSerialPort::Baud38400),
                BaudRatePair(parent->ui->baudRate57600RB, QSerialPort::Baud57600),
                BaudRatePair(parent->ui->baudRate115200RB, QSerialPort::Baud115200)};
    dataBits = {DataBitsPair(parent->ui->dataBits5RB, QSerialPort::Data5),
                DataBitsPair(parent->ui->dataBits6RB, QSerialPort::Data6),
                DataBitsPair(parent->ui->dataBits7RB, QSerialPort::Data7),
                DataBitsPair(parent->ui->dataBits8RB, QSerialPort::Data8)};
    parity = {ParityPair(parent->ui->parityNoneRB, QSerialPort::NoParity),
              ParityPair(parent->ui->parityEvenRB, QSerialPort::EvenParity),
              ParityPair(parent->ui->parityOddRB, QSerialPort::OddParity),
              ParityPair(parent->ui->paritySpaceRB, QSerialPort::SpaceParity),
              ParityPair(parent->ui->parityMarkRB, QSerialPort::MarkParity)};
    stopBits = {StopBitsPair(parent->ui->stopBits1RB, QSerialPort::OneStop),
                StopBitsPair(parent->ui->stopBits15RB, QSerialPort::OneAndHalfStop),
                StopBitsPair(parent->ui->stopBits2RB, QSerialPort::TwoStop)};
    flowControl = {FlowControlPair(parent->ui->flowControlNoRB, QSerialPort::NoFlowControl),
                   FlowControlPair(parent->ui->flowControlHardRB, QSerialPort::HardwareControl),
                   FlowControlPair(parent->ui->flowControlSoftRB, QSerialPort::SoftwareControl)};
}

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

QSerialPortInfo ComTerm::getPortParam(QString *toolTip)
{
    QSerialPort port(ui->portsListComboBox->currentText());
    for(const BaudRatePair &baud: portSetting->baudRate) {
        if(baud.first->isChecked()) {
            port.setBaudRate(baud.second);
            toolTip->append("Baud Rate: " + QString().setNum(baud.second) + '\n');
            break;
        }
    }
    for(const DataBitsPair &data: portSetting->dataBits) {
        if(data.first->isChecked()) {
            port.setDataBits(data.second);
            toolTip->append("Data Bits: " + QString().setNum(data.second) + '\n');
            break;
        }
    }
    for(const ParityPair &parity: portSetting->parity) {
        if(parity.first->isChecked()) {
            port.setParity(parity.second);
            QString strParity;
            if(parity.second == QSerialPort::NoParity) {
                strParity = "No";
            }
            else if(parity.second == QSerialPort::EvenParity) {
                strParity = "Even";
            }
            else if(parity.second == QSerialPort::OddParity) {
                strParity = "Odd";
            }
            else if(parity.second == QSerialPort::SpaceParity) {
                strParity = "Space";
            }
            else if(parity.second == QSerialPort::MarkParity) {
                strParity = "Mark";
            }
            toolTip->append("Parity: " + strParity + '\n');
            break;
        }
    }
    for(const StopBitsPair &stop: portSetting->stopBits) {
        if(stop.first->isChecked()) {
            port.setStopBits(stop.second);
            QString strStop;
            if(stop.second == QSerialPort::OneStop) {
                strStop = "1";
            }
            else if(stop.second == QSerialPort::OneAndHalfStop) {
                strStop = "1.5";
            }
            else if(stop.second == QSerialPort::TwoStop) {
                strStop = "2";
            }
            toolTip->append("Stop Bits: " + strStop + '\n');
            break;
        }
    }
    for(const FlowControlPair &flow: portSetting->flowControl) {
        if(flow.first->isChecked()) {
            port.setFlowControl(flow.second);
            QString strFlow;
            if(flow.second == QSerialPort::NoFlowControl) {
                strFlow = "No";
            }
            else if(flow.second == QSerialPort::HardwareControl) {
                strFlow = "Hardware";
            }
            else if(flow.second == QSerialPort::SoftwareControl) {
                strFlow = "Software";
            }
            toolTip->append("Flow Control: " + strFlow);
            break;
        }
    }
    return QSerialPortInfo(port);
}
