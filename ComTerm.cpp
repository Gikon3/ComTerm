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
    QSerialPortInfo info(ui->portsListComboBox->currentText());
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
        QMessageBox::warning(this, "Warning", "Port " + info.portName() + " is open");
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
