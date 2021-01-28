#include "TabForm.h"
#include "ui_TabForm.h"
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>

TabForm::TabForm(const QSerialPortInfo &info, bool *ok, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabForm),
    recordFile(new QFile)
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
    delete recordFile;
    port->close();
    delete port;
    delete ui;
}

// slots
void TabForm::rxClearButtonClicked()
{
    ui->rxWidget->clear();
}

void TabForm::txClearButtonClicked()
{
    ui->txWidget->clear();
}

void TabForm::sendButtonClicked()
{
    QByteArray array = QString(ui->txLline->text()).toUtf8();
    port->write(array);
    txAppend(array);
}

void TabForm::recordToolButtonClicked()
{
    QString filename = openExplorer(recordLastFilePath);
    if(filename.size()) {
        ui->recordLine->setText(filename);
    }
}

void TabForm::recordButtonClicked()
{
    if(recordFile->isOpen()) {
        recordFile->close();
        ui->recordButton->setText(tr("Start recording"));
        ui->rxWidget->appendEndFile();
        ui->recordButton->setChecked(false);
        return;
    }

    recordFile->setFileName(ui->recordLine->text());
    if(!recordFile->open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Warning"), tr("Could not open file"));
        ui->recordButton->setChecked(false);
        return;
    }
    if(QFileInfo(*recordFile).size()
            && QMessageBox::question(this, tr("Warning"), tr("The file is not empty!\nOverwrite?")) == QMessageBox::No) {
        ui->recordButton->setChecked(false);
        return;
    }

    ui->recordButton->setText(tr("End recording"));
    ui->rxWidget->appendStartFile();
    ui->recordButton->setChecked(true);
}

void TabForm::sendFileToolButtonClicked()
{
    QString filename = openExplorer(sendLastFilePath);
    if(filename.size()) {
        ui->sendFileLine->setText(filename);
    }
}

void TabForm::sendFileButtonClicked()
{
    QFile sendFile(ui->sendFileLine->text());
    if(!sendFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Warning"), tr("Could not open file"));
        return;
    }

    while(!sendFile.atEnd()) {
        QByteArray buf = sendFile.read(4096);
        port->write(buf);
        txAppend(buf);
    }
    sendFile.close();
}
// -- slots

void TabForm::txAppend(const QByteArray& array)
{
    ui->txWidget->append(array);
}

void TabForm::handleReadyRead()
{
    QByteArray buf = port->readAll();
    if(!ui->pauseButton->isChecked()) {
        ui->rxWidget->append(buf);
        if(recordFile->isOpen()) {
            recordFile->write(buf);
        }
    }
}

void TabForm::retranslate()
{
    ui->retranslateUi(this);
    ui->rxWidget->retranslate();
    ui->txWidget->retranslate();
}

QString TabForm::openExplorer(QString &lastFilePath)
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), lastFilePath.size() ? lastFilePath: "C:\\",
                                                    tr("All files (*.*);; Text document (*.txt *.log)"));
    if(filename.size()) {
        lastFilePath = filename;
    }
    return filename;
}
