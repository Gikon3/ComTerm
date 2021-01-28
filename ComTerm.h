#ifndef COMTERM_H
#define COMTERM_H

#include <QMainWindow>
#include <QList>
#include "TabForm.h"
#include <QRadioButton>
#include <QTranslator>
#include <QDockWidget>
#include "CloseEventFilter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ComTerm; }
QT_END_NAMESPACE

class ComTerm : public QMainWindow
{
    Q_OBJECT

public:
    ComTerm(QWidget *parent = nullptr);
    ~ComTerm();

private slots:
    void scanButtonClicked();
    void connectButtonClicked();
    void tabClose(int index);
    void aboutWindowShow();
    void aboutQtWindowShow();
    void languageEnglishClicked();
    void languageRussiaClicked();
    void showDockWidget();

private:
    void updateFreePortList();
    QSerialPortInfo getPortParam(QString *toolTip);
    void initAsciiTable();

private:
    const QString version = "1.1.1";
    Ui::ComTerm *ui;
    const int heighTab = 200;
    using BaudRatePair = QPair<QRadioButton*, QSerialPort::BaudRate>;
    using DataBitsPair = QPair<QRadioButton*, QSerialPort::DataBits>;
    using ParityPair = QPair<QRadioButton*, QSerialPort::Parity>;
    using StopBitsPair = QPair<QRadioButton*, QSerialPort::StopBits>;
    using FlowControlPair = QPair<QRadioButton*, QSerialPort::FlowControl>;
    struct PortSetting {
        QList<BaudRatePair> baudRate;
        QList<DataBitsPair> dataBits;
        QList<ParityPair> parity;
        QList<StopBitsPair> stopBits;
        QList<FlowControlPair> flowControl;
        PortSetting(ComTerm* parent);
    };
    PortSetting *portSetting;
    QTranslator translator;
    CloseEventFilter *closeFilter;
};
#endif // COMTERM_H
