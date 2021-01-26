#ifndef COMTERM_H
#define COMTERM_H

#include <QMainWindow>
#include <QSet>
#include <QSerialPort>
#include "TabForm.h"

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

private:
    void updateFreePortList();
    QSerialPort* openPort(const QString& portName);
    void handleReadyRead();

private:
    using TabPortPair = QPair<TabForm*, QSerialPort*>;
    Ui::ComTerm *ui;
    QSet<TabPortPair> openPortsList;
};
#endif // COMTERM_H
