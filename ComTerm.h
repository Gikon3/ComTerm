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
    void tabClose(int index);

private:
    void updateFreePortList();

private:
    Ui::ComTerm *ui;
    const int heighTab = 160;
};
#endif // COMTERM_H
